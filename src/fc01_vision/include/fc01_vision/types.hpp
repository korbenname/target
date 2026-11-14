#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <opencv2/core.hpp>

namespace fc01_vision {

// ---------------------------------------------------------------------------
// Camera
// ---------------------------------------------------------------------------
struct CameraConfig {
  int device_index{0};
  int width{640};
  int height{480};
  int fps{30};
  bool use_mjpg{true};
  bool flip_horizontal{false};
  int buffer_size{1};
};

struct CameraIntrinsics {
  double fx{0.0};
  double fy{0.0};
  double cx{0.0};
  double cy{0.0};
  int width{0};
  int height{0};

  bool valid() const { return fx > 0.0 && fy > 0.0; }

  cv::Mat matrix() const {
    return (cv::Mat_<double>(3, 3) << fx, 0.0, cx, 0.0, fy, cy, 0.0, 0.0, 1.0);
  }
  cv::Mat distortion() const { return cv::Mat::zeros(5, 1, CV_64F); }
};

// ---------------------------------------------------------------------------
// Detection
// ---------------------------------------------------------------------------
struct HsvRange {
  int h_min{0};
  int h_max{180};
  int s_min{0};
  int s_max{255};
  int v_min{0};
  int v_max{255};
};

struct DetectorConfig {
  std::vector<HsvRange> ranges;
  int blur_kernel{5};
  int morph_kernel{5};
  double min_area_ratio{0.002};
  double max_area_ratio{0.5};
  int min_width_px{6};
  int min_height_px{6};
  // "auto" | "rect" | "circle"
  std::string shape{"auto"};
  double circle_min_circularity{0.85};
  // Reject blobs that touch the image border. A clipped target gives a
  // biased centroid and a too-small apparent size, which shows up as a
  // wildly over-estimated range (e.g. 12 m at 2 m).
  bool reject_border_touch{true};
  int border_margin_px{2};
};

enum class TargetShape { kUnknown, kRect, kCircle };

struct Detection {
  bool found{false};
  cv::Rect bbox;
  cv::Point2f center{0.f, 0.f};
  cv::RotatedRect rotated;
  TargetShape shape{TargetShape::kUnknown};
  double area_px{0.0};
  double circularity{0.0};
  double radius_px{0.0};
  double angle_deg{0.0};
  std::vector<cv::Point> contour;
};

// ---------------------------------------------------------------------------
// Geometry / estimation
// ---------------------------------------------------------------------------
struct EstimatorConfig {
  // Physical size of the target. Set only the ones that apply.
  double target_width_m{0.0};
  double target_height_m{0.0};
  double target_diameter_m{0.0};
  double min_range_m{0.1};
  double max_range_m{20.0};
  double max_reprojection_error_px{8.0};
  bool use_pnp{true};
};

// All positions use metres.
//   position_cam : optical frame, x right, y down, z forward
//   position_frd : body FRD frame, x forward, y right, z down
struct Estimate {
  bool position_valid{false};
  cv::Vec3d position_cam{0.0, 0.0, 0.0};
  cv::Vec3d position_frd{0.0, 0.0, 0.0};
  double distance_m{0.0};
  double yaw_rad{0.0};  // bearing in FRD, positive to the right
  std::string reason;
};

struct FilterConfig {
  double position_alpha{0.5};
  double velocity_beta{0.1};
  double stale_timeout_s{0.5};
  double max_dt_s{0.2};
};

// ---------------------------------------------------------------------------
// Output
// ---------------------------------------------------------------------------
struct TargetState {
  bool detected{false};
  bool position_valid{false};

  double x{0.0};   // FRD forward  [m]
  double y{0.0};   // FRD right    [m]
  double z{0.0};   // FRD down     [m]
  double vx{0.0};
  double vy{0.0};
  double vz{0.0};
  double yaw{0.0};       // bearing, positive right [rad]
  double distance{0.0};  // range [m]
  double u{0.0};         // target centre, pixel
  double v{0.0};

  // Diagonal of the 6x6 covariance: x, y, z, vx, vy, vz.
  double cov[6]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  uint64_t frame_seq{0};
  int64_t stamp_ns{0};  // capture time, system clock [ns]
  std::string reason;
};

}  // namespace fc01_vision
