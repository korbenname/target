#include "fc01_vision/target_estimator.hpp"

#include <algorithm>
#include <cmath>

#include <opencv2/calib3d.hpp>

namespace fc01_vision {

TargetEstimator::TargetEstimator(EstimatorConfig config)
    : config_(std::move(config)) {}

cv::Vec3d TargetEstimator::opticalToFrd(const cv::Vec3d& optical) {
  // optical: x right, y down, z forward
  // FRD:     x forward, y right, z down
  return cv::Vec3d(optical[2], optical[0], optical[1]);
}

Estimate TargetEstimator::finish(const cv::Vec3d& position_cam,
                                 const CameraIntrinsics& intrinsics,
                                 const std::string& reason) const {
  Estimate estimate;
  estimate.position_cam = position_cam;
  estimate.position_frd = opticalToFrd(position_cam);
  estimate.distance_m = cv::norm(position_cam);
  estimate.yaw_rad =
      std::atan2(estimate.position_frd[1], estimate.position_frd[0]);
  estimate.reason = reason;

  if (!intrinsics.valid()) {
    estimate.reason = "invalid camera intrinsics";
    return estimate;
  }
  if (estimate.distance_m < config_.min_range_m ||
      estimate.distance_m > config_.max_range_m) {
    estimate.reason = "range outside configured limits";
    return estimate;
  }

  estimate.position_valid = true;
  return estimate;
}

Estimate TargetEstimator::bearingOnly(
    const Detection& detection, const CameraIntrinsics& intrinsics,
    const std::string& reason) const {
  Estimate estimate;
  estimate.reason = reason;

  if (!intrinsics.valid()) {
    estimate.reason = "invalid camera intrinsics";
    return estimate;
  }

  cv::Vec3d ray(
      (detection.center.x - intrinsics.cx) / intrinsics.fx,
      (detection.center.y - intrinsics.cy) / intrinsics.fy, 1.0);
  const double n = cv::norm(ray);
  if (n > 1e-9) {
    ray /= n;
  }
  estimate.position_cam = ray;
  estimate.position_frd = opticalToFrd(ray);
  estimate.distance_m = 0.0;
  estimate.yaw_rad =
      std::atan2(estimate.position_frd[1], estimate.position_frd[0]);
  estimate.position_valid = false;
  return estimate;
}

Estimate TargetEstimator::estimateCircle(
    const Detection& detection, const CameraIntrinsics& intrinsics) const {
  if (config_.target_diameter_m <= 0.0) {
    return bearingOnly(detection, intrinsics,
                       "target_diameter_m not configured");
  }
  if (detection.radius_px <= 1.0) {
    return bearingOnly(detection, intrinsics, "degenerate circle radius");
  }

  const double fx = 0.5 * (intrinsics.fx + intrinsics.fy);
  const double diameter_px = 2.0 * detection.radius_px;
  const double z = fx * config_.target_diameter_m / diameter_px;
  const double x =
      (detection.center.x - intrinsics.cx) * z / intrinsics.fx;
  const double y =
      (detection.center.y - intrinsics.cy) * z / intrinsics.fy;

  return finish(cv::Vec3d(x, y, z), intrinsics, "circle diameter");
}

Estimate TargetEstimator::estimateRect(
    const Detection& detection, const CameraIntrinsics& intrinsics) const {
  const double width_m = config_.target_width_m;
  const double height_m = config_.target_height_m;

  if (width_m <= 0.0 || height_m <= 0.0) {
    return bearingOnly(detection, intrinsics,
                       "target_width_m/target_height_m not configured");
  }

  const double rect_w =
      std::max(1e-6, static_cast<double>(detection.rotated.size.width));
  const double rect_h =
      std::max(1e-6, static_cast<double>(detection.rotated.size.height));

  double object_w = width_m;
  double object_h = height_m;

  // A RotatedRect cannot distinguish a 90-degree rotation of the target.
  // Pick the width/height assignment that matches the observed aspect ratio.
  const double observed = rect_w / rect_h;
  const double score_direct = std::abs(std::log(observed / (width_m / height_m)));
  const double score_swapped = std::abs(std::log(observed / (height_m / width_m)));
  if (score_swapped < score_direct) {
    std::swap(object_w, object_h);
  }

  if (config_.use_pnp) {
    // Order returned by RotatedRect::points(): BL, TL, TR, BR (image coords,
    // y down). Object points use the same convention.
    cv::Point2f corners[4];
    detection.rotated.points(corners);

    const std::vector<cv::Point3f> object_points = {
        cv::Point3f(static_cast<float>(-object_w / 2.0),
                    static_cast<float>(object_h / 2.0), 0.f),
        cv::Point3f(static_cast<float>(-object_w / 2.0),
                    static_cast<float>(-object_h / 2.0), 0.f),
        cv::Point3f(static_cast<float>(object_w / 2.0),
                    static_cast<float>(-object_h / 2.0), 0.f),
        cv::Point3f(static_cast<float>(object_w / 2.0),
                    static_cast<float>(object_h / 2.0), 0.f),
    };
    const std::vector<cv::Point2f> image_points = {
        corners[0], corners[1], corners[2], corners[3]};

    const cv::Mat camera_matrix = intrinsics.matrix();
    const cv::Mat distortion = intrinsics.distortion();
    cv::Mat rvec;
    cv::Mat tvec;

    bool solved = false;
    try {
      solved = cv::solvePnP(object_points, image_points, camera_matrix,
                            distortion, rvec, tvec, false,
                            cv::SOLVEPNP_IPPE);
      if (!solved) {
        solved = cv::solvePnP(object_points, image_points, camera_matrix,
                              distortion, rvec, tvec, false,
                              cv::SOLVEPNP_ITERATIVE);
      }
    } catch (const cv::Exception&) {
      solved = false;
    }

    if (solved && tvec.at<double>(2) > 0.0) {
      std::vector<cv::Point2f> projected;
      cv::projectPoints(object_points, rvec, tvec, camera_matrix, distortion,
                        projected);
      double error = 0.0;
      for (std::size_t i = 0; i < projected.size(); ++i) {
        error += cv::norm(projected[i] - image_points[i]);
      }
      error /= static_cast<double>(projected.size());

      if (error <= config_.max_reprojection_error_px) {
        const cv::Vec3d position(tvec.at<double>(0), tvec.at<double>(1),
                                 tvec.at<double>(2));
        return finish(position, intrinsics, "planar PnP");
      }
    }
  }

  // Fallback: range from the known width and apparent width. Assumes the
  // target is roughly fronto-parallel.
  const double z = intrinsics.fx * object_w / rect_w;
  const double x = (detection.center.x - intrinsics.cx) * z / intrinsics.fx;
  const double y = (detection.center.y - intrinsics.cy) * z / intrinsics.fy;
  return finish(cv::Vec3d(x, y, z), intrinsics, "apparent width");
}

Estimate TargetEstimator::estimate(
    const Detection& detection, const CameraIntrinsics& intrinsics) const {
  if (!detection.found) {
    Estimate estimate;
    estimate.reason = "no detection";
    return estimate;
  }
  if (!intrinsics.valid()) {
    Estimate estimate;
    estimate.reason = "invalid camera intrinsics";
    return estimate;
  }

  if (detection.shape == TargetShape::kCircle) {
    return estimateCircle(detection, intrinsics);
  }
  return estimateRect(detection, intrinsics);
}

}  // namespace fc01_vision
