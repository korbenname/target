#include "fc01_vision/param_utils.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace fc01_vision {
namespace {
constexpr double kPi = 3.14159265358979323846;
}

bool parseHsvRange(const std::string& text, HsvRange& range) {
  std::vector<int> values;
  std::stringstream stream(text);
  std::string token;
  while (std::getline(stream, token, ',')) {
    try {
      values.push_back(std::stoi(token));
    } catch (const std::exception&) {
      return false;
    }
  }
  if (values.size() != 6) {
    return false;
  }
  range.h_min = values[0];
  range.h_max = values[1];
  range.s_min = values[2];
  range.s_max = values[3];
  range.v_min = values[4];
  range.v_max = values[5];
  return true;
}

DetectorConfig declareDetectorConfig(rclcpp::Node& node) {
  DetectorConfig config;

  const std::vector<std::string> default_ranges = {"0,10,80,255,50,255",
                                                   "170,180,80,255,50,255"};
  const std::vector<std::string> raw_ranges =
      node.declare_parameter<std::vector<std::string>>("hsv_ranges",
                                                       default_ranges);
  config.ranges.clear();
  for (const std::string& raw : raw_ranges) {
    HsvRange range;
    if (parseHsvRange(raw, range)) {
      config.ranges.push_back(range);
    } else {
      RCLCPP_WARN(node.get_logger(),
                  "ignoring malformed hsv_ranges entry: '%s'", raw.c_str());
    }
  }
  if (config.ranges.empty()) {
    throw std::runtime_error("no valid hsv_ranges configured");
  }

  config.blur_kernel =
      static_cast<int>(node.declare_parameter<int>("blur_kernel", 5));
  config.morph_kernel =
      static_cast<int>(node.declare_parameter<int>("morph_kernel", 5));
  config.min_area_ratio =
      node.declare_parameter<double>("min_area_ratio", 0.002);
  config.max_area_ratio =
      node.declare_parameter<double>("max_area_ratio", 0.5);
  config.min_width_px =
      static_cast<int>(node.declare_parameter<int>("min_width_px", 6));
  config.min_height_px =
      static_cast<int>(node.declare_parameter<int>("min_height_px", 6));
  config.shape = node.declare_parameter<std::string>("target_shape", "auto");
  config.circle_min_circularity =
      node.declare_parameter<double>("circle_min_circularity", 0.85);
  config.reject_border_touch =
      node.declare_parameter<bool>("reject_border_touch", true);
  config.border_margin_px =
      static_cast<int>(node.declare_parameter<int>("border_margin_px", 2));
  return config;
}

EstimatorConfig declareEstimatorConfig(rclcpp::Node& node) {
  EstimatorConfig config;
  config.target_width_m =
      node.declare_parameter<double>("target_width_m", 0.0);
  config.target_height_m =
      node.declare_parameter<double>("target_height_m", 0.0);
  config.target_diameter_m =
      node.declare_parameter<double>("target_diameter_m", 0.0);
  config.min_range_m = node.declare_parameter<double>("min_range_m", 0.1);
  config.max_range_m = node.declare_parameter<double>("max_range_m", 20.0);
  config.max_reprojection_error_px =
      node.declare_parameter<double>("max_reprojection_error_px", 8.0);
  config.use_pnp = node.declare_parameter<bool>("use_pnp", true);
  return config;
}

FilterConfig declareFilterConfig(rclcpp::Node& node) {
  FilterConfig config;
  config.position_alpha =
      node.declare_parameter<double>("position_alpha", 0.5);
  config.velocity_beta = node.declare_parameter<double>("velocity_beta", 0.1);
  config.stale_timeout_s =
      node.declare_parameter<double>("stale_timeout_s", 0.5);
  config.max_dt_s = node.declare_parameter<double>("max_dt_s", 0.2);
  return config;
}

CameraIntrinsics declareIntrinsics(rclcpp::Node& node, int width,
                                   int height) {
  CameraIntrinsics intrinsics;
  intrinsics.width = width;
  intrinsics.height = height;
  intrinsics.fx = node.declare_parameter<double>("camera_fx", 0.0);
  intrinsics.fy = node.declare_parameter<double>("camera_fy", 0.0);
  intrinsics.cx = node.declare_parameter<double>("camera_cx", 0.0);
  intrinsics.cy = node.declare_parameter<double>("camera_cy", 0.0);

  if (intrinsics.fx <= 0.0) {
    const double hfov_deg =
        node.declare_parameter<double>("camera_hfov_deg", 60.0);
    intrinsics.fx =
        0.5 * static_cast<double>(width) / std::tan(hfov_deg * kPi / 360.0);
    RCLCPP_WARN(node.get_logger(),
                "camera_fx not set; using %.2f from camera_hfov_deg=%.1f. "
                "Run a proper camera calibration before flight.",
                intrinsics.fx, hfov_deg);
  }
  if (intrinsics.fy <= 0.0) {
    intrinsics.fy = intrinsics.fx;
  }
  if (intrinsics.cx <= 0.0) {
    intrinsics.cx = 0.5 * static_cast<double>(width);
  }
  if (intrinsics.cy <= 0.0) {
    intrinsics.cy = 0.5 * static_cast<double>(height);
  }
  return intrinsics;
}

}  // namespace fc01_vision
