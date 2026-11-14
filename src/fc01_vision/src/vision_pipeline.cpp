#include "fc01_vision/vision_pipeline.hpp"

#include <algorithm>
#include <cmath>

#include "fc01_vision/debug_draw.hpp"

namespace fc01_vision {
namespace {

constexpr double kVelocityDecayTau = 0.3;  // seconds

double elapsedSeconds(int64_t from_ns, int64_t to_ns) {
  return static_cast<double>(to_ns - from_ns) * 1e-9;
}

}  // namespace

VisionPipeline::VisionPipeline(DetectorConfig detector_config,
                               EstimatorConfig estimator_config,
                               FilterConfig filter_config)
    : detector_(std::move(detector_config)),
      estimator_(std::move(estimator_config)),
      filter_(filter_config) {}

void VisionPipeline::reset() {
  last_detection_ = Detection{};
  last_state_ = TargetState{};
  have_estimate_ = false;
  x_ = y_ = z_ = 0.0;
  vx_ = vy_ = vz_ = 0.0;
  last_update_stamp_ns_ = 0;
  last_valid_stamp_ns_ = 0;
  seq_ = 0;
}

TargetState VisionPipeline::makeLostState(int64_t stamp_ns) {
  TargetState state;
  state.stamp_ns = stamp_ns;
  state.frame_seq = ++seq_;
  state.detected = false;
  state.u = last_detection_.center.x;
  state.v = last_detection_.center.y;

  if (!have_estimate_) {
    state.reason = "target lost";
    last_state_ = state;
    return state;
  }

  double dt = elapsedSeconds(last_update_stamp_ns_, stamp_ns);
  dt = std::min(std::max(dt, 0.0), filter_.max_dt_s);

  // Coast on the last velocity, then decay it towards zero.
  x_ += vx_ * dt;
  y_ += vy_ * dt;
  z_ += vz_ * dt;
  const double decay = std::exp(-dt / kVelocityDecayTau);
  vx_ *= decay;
  vy_ *= decay;
  vz_ *= decay;
  last_update_stamp_ns_ = stamp_ns;

  const double since_valid = elapsedSeconds(last_valid_stamp_ns_, stamp_ns);
  state.x = x_;
  state.y = y_;
  state.z = z_;
  state.vx = vx_;
  state.vy = vy_;
  state.vz = vz_;
  state.distance = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  state.yaw = std::atan2(y_, x_);
  state.position_valid = since_valid <= filter_.stale_timeout_s;
  state.reason =
      state.position_valid ? "target lost (coasting)" : "target lost (stale)";

  // Uncertainty grows while coasting.
  const double sigma_pos =
      std::max(0.05, 0.05 * state.distance) + 0.5 * since_valid;
  const double sigma_vel = std::max(0.5, 0.2 * state.distance);
  state.cov[0] = sigma_pos * sigma_pos;
  state.cov[1] = sigma_pos * sigma_pos;
  state.cov[2] = sigma_pos * sigma_pos;
  state.cov[3] = sigma_vel * sigma_vel;
  state.cov[4] = sigma_vel * sigma_vel;
  state.cov[5] = sigma_vel * sigma_vel;

  last_state_ = state;
  return state;
}

void VisionPipeline::updateCovariance(TargetState& state,
                                      const Estimate& estimate, double dt,
                                      const CameraIntrinsics& intrinsics) const {
  const double range = std::max(0.05, estimate.distance_m);
  // 5% range error is a deliberately conservative assumption for a
  // monocular size-based estimate.
  const double sigma_range = std::max(0.03, 0.05 * range);
  const double fx = std::max(1.0, intrinsics.fx);
  const double sigma_lateral = std::max(0.02, range * 2.0 / fx);
  const double sigma_velocity =
      sigma_range / std::max(dt, 1.0 / 120.0);

  state.cov[0] = sigma_range * sigma_range;
  state.cov[1] = sigma_lateral * sigma_lateral;
  state.cov[2] = sigma_lateral * sigma_lateral;
  state.cov[3] = sigma_velocity * sigma_velocity;
  state.cov[4] = sigma_velocity * sigma_velocity;
  state.cov[5] = sigma_velocity * sigma_velocity;
}

TargetState VisionPipeline::process(const cv::Mat& bgr,
                                    const CameraIntrinsics& intrinsics,
                                    int64_t stamp_ns) {
  last_detection_ = detector_.detect(bgr);
  const Detection& detection = last_detection_;

  if (!detection.found) {
    return makeLostState(stamp_ns);
  }

  TargetState state;
  state.stamp_ns = stamp_ns;
  state.frame_seq = ++seq_;
  state.detected = true;
  state.u = detection.center.x;
  state.v = detection.center.y;

  const Estimate estimate = estimator_.estimate(detection, intrinsics);
  state.distance = estimate.distance_m;
  state.yaw = estimate.yaw_rad;
  state.reason = estimate.reason;

  if (!estimate.position_valid) {
    state.position_valid = false;
    if (have_estimate_) {
      state.x = x_;
      state.y = y_;
      state.z = z_;
      state.vx = vx_;
      state.vy = vy_;
      state.vz = vz_;
      state.cov[0] = last_state_.cov[0];
      state.cov[1] = last_state_.cov[1];
      state.cov[2] = last_state_.cov[2];
      state.cov[3] = last_state_.cov[3];
      state.cov[4] = last_state_.cov[4];
      state.cov[5] = last_state_.cov[5];
    }
    last_state_ = state;
    return state;
  }

  const cv::Vec3d& measurement = estimate.position_frd;
  double dt = 0.0;

  if (!have_estimate_) {
    x_ = measurement[0];
    y_ = measurement[1];
    z_ = measurement[2];
    vx_ = vy_ = vz_ = 0.0;
    have_estimate_ = true;
    last_update_stamp_ns_ = stamp_ns;
    dt = 1.0 / 30.0;
  } else {
    dt = elapsedSeconds(last_update_stamp_ns_, stamp_ns);
    if (dt <= 1e-4) {
      dt = 1.0 / 30.0;
    }
    dt = std::min(dt, filter_.max_dt_s);

    const double alpha = std::min(std::max(filter_.position_alpha, 0.0), 1.0);
    const double beta = std::max(filter_.velocity_beta, 0.0);

    const double px = x_ + vx_ * dt;
    const double py = y_ + vy_ * dt;
    const double pz = z_ + vz_ * dt;

    const double rx = measurement[0] - px;
    const double ry = measurement[1] - py;
    const double rz = measurement[2] - pz;

    x_ = px + alpha * rx;
    y_ = py + alpha * ry;
    z_ = pz + alpha * rz;

    vx_ += (beta / dt) * rx;
    vy_ += (beta / dt) * ry;
    vz_ += (beta / dt) * rz;

    last_update_stamp_ns_ = stamp_ns;
  }

  last_valid_stamp_ns_ = stamp_ns;

  state.position_valid = true;
  state.x = x_;
  state.y = y_;
  state.z = z_;
  state.vx = vx_;
  state.vy = vy_;
  state.vz = vz_;
  state.distance = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  state.yaw = std::atan2(y_, x_);
  updateCovariance(state, estimate, dt, intrinsics);

  last_state_ = state;
  return state;
}

cv::Mat VisionPipeline::drawDebug(const cv::Mat& bgr) const {
  return drawDebugOverlay(bgr, last_detection_, last_state_,
                          detector_.mask(bgr));
}

}  // namespace fc01_vision
