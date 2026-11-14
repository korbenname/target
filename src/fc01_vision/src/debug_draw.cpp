#include "fc01_vision/debug_draw.hpp"

#include <cstdio>
#include <string>
#include <vector>

#include <opencv2/imgproc.hpp>

namespace fc01_vision {

cv::Mat drawDebugOverlay(const cv::Mat& bgr, const Detection& detection,
                         const TargetState& state, const cv::Mat& mask) {
  if (bgr.empty()) {
    return {};
  }

  cv::Mat image = bgr.clone();

  if (detection.found) {
    if (!detection.contour.empty()) {
      std::vector<std::vector<cv::Point>> contours{detection.contour};
      cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 255), 2);
    }

    cv::Point2f corners[4];
    detection.rotated.points(corners);
    // White: a green box is invisible on the green target.
    for (int i = 0; i < 4; ++i) {
      cv::line(image, corners[i], corners[(i + 1) % 4],
               cv::Scalar(255, 255, 255), 1);
    }

    cv::circle(image, detection.center, 4, cv::Scalar(0, 0, 255), -1);
    cv::line(image,
             cv::Point(static_cast<int>(detection.center.x),
                       static_cast<int>(detection.center.y)),
             cv::Point(image.cols / 2, image.rows / 2), cv::Scalar(255, 0, 0),
             1);
  }

  // Image centre / optical axis.
  cv::drawMarker(image, cv::Point(image.cols / 2, image.rows / 2),
                 cv::Scalar(255, 255, 255), cv::MARKER_CROSS, 16, 1);

  char line1[160];
  std::snprintf(line1, sizeof(line1), "found=%d valid=%d %s",
                detection.found ? 1 : 0, state.position_valid ? 1 : 0,
                state.reason.c_str());

  char line2[160];
  std::snprintf(line2, sizeof(line2), "range=%.2fm pix=(%.0f, %.0f)",
                state.distance, state.u, state.v);

  char line3[200];
  std::snprintf(line3, sizeof(line3), "FRD pos=(%.2f, %.2f, %.2f)m",
                state.x, state.y, state.z);

  char line4[200];
  std::snprintf(line4, sizeof(line4), "FRD vel=(%.2f, %.2f, %.2f)m/s",
                state.vx, state.vy, state.vz);

  const std::vector<std::string> lines = {line1, line2, line3, line4};
  for (std::size_t i = 0; i < lines.size(); ++i) {
    const int y = 20 + static_cast<int>(i) * 20;
    cv::putText(image, lines[i], cv::Point(8, y), cv::FONT_HERSHEY_SIMPLEX,
                0.5, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
    cv::putText(image, lines[i], cv::Point(8, y), cv::FONT_HERSHEY_SIMPLEX,
                0.5, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
  }

  if (!mask.empty()) {
    const int inset_w = image.cols / 4;
    const int inset_h = image.rows / 4;
    cv::Mat small;
    cv::resize(mask, small, cv::Size(inset_w, inset_h));
    cv::Mat color;
    cv::cvtColor(small, color, cv::COLOR_GRAY2BGR);
    const cv::Rect roi(image.cols - inset_w - 8, image.rows - inset_h - 8,
                       inset_w, inset_h);
    if (roi.x >= 0 && roi.y >= 0) {
      color.copyTo(image(roi));
      cv::rectangle(image, roi, cv::Scalar(128, 128, 128), 1);
    }
  }

  return image;
}

}  // namespace fc01_vision
