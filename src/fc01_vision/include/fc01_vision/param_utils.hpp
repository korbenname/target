#pragma once

#include <string>

#include <rclcpp/rclcpp.hpp>

#include "fc01_vision/types.hpp"

namespace fc01_vision {

// Shared ROS parameter loaders. Each function declares its parameters on the
// given node, so a node must call each loader at most once.
bool parseHsvRange(const std::string& text, HsvRange& range);

DetectorConfig declareDetectorConfig(rclcpp::Node& node);
EstimatorConfig declareEstimatorConfig(rclcpp::Node& node);
FilterConfig declareFilterConfig(rclcpp::Node& node);

// Declares camera_fx/fy/cx/cy and camera_hfov_deg. When fx is 0 it is derived
// from the horizontal FOV and width.
CameraIntrinsics declareIntrinsics(rclcpp::Node& node, int width, int height);

}  // namespace fc01_vision
