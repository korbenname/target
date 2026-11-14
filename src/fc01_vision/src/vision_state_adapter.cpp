#include "fc01_vision/vision_state_adapter.hpp"

#include <algorithm>

namespace fc01_vision {

void fillVisionState(const TargetState& state, const rclcpp::Time& stamp,
                     const std::string& frame_id,
                     const AdapterConfig& config,
                     jikl_fc01_system::msg::VisionState& message) {
  using VisionState = jikl_fc01_system::msg::VisionState;

  message.schema_version = 1;
  message.sequence = state.frame_seq;
  message.stamp = stamp;
  message.reset_counter = config.reset_counter;
  message.frame_id = frame_id;
  message.body_frame_id = config.body_frame_id;
  message.source_id = config.source_id;
  message.angular_velocity_source.clear();

  const bool valid = state.detected && state.position_valid;

  message.initialized = state.stamp_ns > 0;
  message.tracking = valid;
  message.calibration_valid = config.calibration_valid;

  uint16_t fields = 0;
  if (valid) {
    fields |= VisionState::POSITION | VisionState::VELOCITY;
  }

  // Body FRD: x forward, y right, z down [m] and [m/s].
  message.position = {state.x, state.y, state.z};
  message.velocity = {state.vx, state.vy, state.vz};

  // Not estimated by this pipeline; the validity bits stay clear.
  message.attitude = {1.0, 0.0, 0.0, 0.0};  // Hamilton w, x, y, z.
  message.angular_velocity = {0.0, 0.0, 0.0};

  // Row-major 6x6: linear xyz, then fixed-axis angular xyz.
  std::fill(message.pose_covariance.begin(), message.pose_covariance.end(),
            0.0);
  std::fill(message.twist_covariance.begin(), message.twist_covariance.end(),
            0.0);

  const double position_var[3] = {
      valid ? state.cov[0] : config.invalid_position_std_m *
                                config.invalid_position_std_m,
      valid ? state.cov[1] : config.invalid_position_std_m *
                                config.invalid_position_std_m,
      valid ? state.cov[2] : config.invalid_position_std_m *
                                config.invalid_position_std_m,
  };
  const double velocity_var[3] = {
      valid ? state.cov[3] : config.invalid_velocity_std_mps *
                                config.invalid_velocity_std_mps,
      valid ? state.cov[4] : config.invalid_velocity_std_mps *
                                config.invalid_velocity_std_mps,
      valid ? state.cov[5] : config.invalid_velocity_std_mps *
                                config.invalid_velocity_std_mps,
  };

  message.pose_covariance[0] = position_var[0];
  message.pose_covariance[7] = position_var[1];
  message.pose_covariance[14] = position_var[2];
  message.twist_covariance[0] = velocity_var[0];
  message.twist_covariance[7] = velocity_var[1];
  message.twist_covariance[14] = velocity_var[2];

  if (valid) {
    fields |= VisionState::POSE_COVARIANCE | VisionState::TWIST_COVARIANCE;
  }
  message.valid_fields = fields;

  // No calibrated internal quality metric; QUALITY stays clear.
  message.quality = 0.0;
}

}  // namespace fc01_vision
