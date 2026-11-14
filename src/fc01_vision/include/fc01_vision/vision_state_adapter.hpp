#pragma once

#include <cstdint>
#include <string>

#include <jikl_fc01_system/msg/vision_state.hpp>
#include <rclcpp/time.hpp>

#include "fc01_vision/types.hpp"

namespace fc01_vision {

struct AdapterConfig {
  std::string source_id{"fc01_vision"};
  std::string body_frame_id{"body_frd"};
  bool calibration_valid{true};
  uint32_t reset_counter{0};
  double invalid_position_std_m{1000.0};
  double invalid_velocity_std_mps{1000.0};
};

// The ONLY place that knows the VisionState field layout.
//
// What this vision pipeline can actually estimate:
//   POSITION / VELOCITY  target relative to the camera/body, body FRD axes.
//   POSE_COVARIANCE      linear (position) block from the alpha-beta filter.
//   TWIST_COVARIANCE     linear (velocity) block.
// What it cannot estimate, and therefore leaves with the validity bit clear:
//   ATTITUDE             written as identity [w=1, x=0, y=0, z=0].
//   ANGULAR_VELOCITY     written as zero.
//   QUALITY              written as zero.
//
// frame_id is the frame the position/velocity are expressed in (default
// "body_frd"). The contract's attitude field is a body-FRD -> NED rotation;
// this node publishes no attitude, so consumers must respect ATTITUDE.
void fillVisionState(const TargetState& state, const rclcpp::Time& stamp,
                     const std::string& frame_id,
                     const AdapterConfig& config,
                     jikl_fc01_system::msg::VisionState& message);

}  // namespace fc01_vision
