#include "fc01_vision/color_detector.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

#include <opencv2/imgproc.hpp>

namespace fc01_vision {
namespace {

int oddKernel(int value) {
  if (value < 3) {
    return 0;
  }
  return value % 2 == 0 ? value + 1 : value;
}

}  // namespace

ColorDetector::ColorDetector(DetectorConfig config) : config_(std::move(config)) {}

cv::Mat ColorDetector::mask(const cv::Mat& bgr) const {
  if (bgr.empty()) {
    return {};
  }

  cv::Mat input = bgr;
  cv::Mat blurred;
  const int blur = oddKernel(config_.blur_kernel);
  if (blur > 0) {
    cv::GaussianBlur(bgr, blurred, cv::Size(blur, blur), 0.0);
    input = blurred;
  }

  cv::Mat hsv;
  cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);

  cv::Mat combined = cv::Mat::zeros(hsv.size(), CV_8UC1);
  for (const HsvRange& range : config_.ranges) {
    cv::Mat current;
    cv::inRange(hsv,
                cv::Scalar(range.h_min, range.s_min, range.v_min),
                cv::Scalar(range.h_max, range.s_max, range.v_max),
                current);
    cv::bitwise_or(combined, current, combined);
  }

  const int morph = oddKernel(config_.morph_kernel);
  if (morph > 0) {
    const cv::Mat kernel = cv::getStructuringElement(
        cv::MORPH_ELLIPSE, cv::Size(morph, morph));
    cv::morphologyEx(combined, combined, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(combined, combined, cv::MORPH_CLOSE, kernel);
  }
  return combined;
}

TargetShape ColorDetector::classify(const std::vector<cv::Point>& contour,
                                     double area,
                                     const cv::RotatedRect& rotated) const {
  if (config_.shape == "rect") {
    return TargetShape::kRect;
  }
  if (config_.shape == "circle") {
    return TargetShape::kCircle;
  }

  const double perimeter = cv::arcLength(contour, true);
  const double circularity =
      perimeter > 1e-6 ? 4.0 * CV_PI * area / (perimeter * perimeter) : 0.0;

  const double w = std::max(1.0, static_cast<double>(rotated.size.width));
  const double h = std::max(1.0, static_cast<double>(rotated.size.height));
  const double aspect = std::min(w, h) / std::max(w, h);

  const bool looks_round =
      circularity >= config_.circle_min_circularity && aspect >= 0.75;
  return looks_round ? TargetShape::kCircle : TargetShape::kRect;
}

Detection ColorDetector::detect(const cv::Mat& bgr) const {
  Detection detection;
  if (bgr.empty()) {
    return detection;
  }

  const cv::Mat binary = mask(bgr);
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(binary, contours, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  const double image_area = static_cast<double>(bgr.cols) * bgr.rows;
  const double min_area = config_.min_area_ratio * image_area;
  const double max_area = config_.max_area_ratio * image_area;

  double best_area = -1.0;
  std::vector<cv::Point> best_contour;
  cv::RotatedRect best_rect;

  for (const auto& contour : contours) {
    const double area = cv::contourArea(contour);
    if (area < min_area || area > max_area) {
      continue;
    }

    const cv::RotatedRect rotated = cv::minAreaRect(contour);
    if (rotated.size.width < config_.min_width_px ||
        rotated.size.height < config_.min_height_px) {
      continue;
    }

    // A target clipped by the image border has a biased centroid and an
    // apparent size that is too small, which the range estimator turns into
    // a grossly over-estimated distance. Ignore it; the next frames either
    // recover the full blob or report no detection.
    const cv::Rect bbox = cv::boundingRect(contour);
    const int margin = config_.border_margin_px;
    if (config_.reject_border_touch &&
        (bbox.x <= margin || bbox.y <= margin ||
         bbox.x + bbox.width >= bgr.cols - margin ||
         bbox.y + bbox.height >= bgr.rows - margin)) {
      continue;
    }

    if (area > best_area) {
      best_area = area;
      best_contour = contour;
      best_rect = rotated;
    }
  }

  if (best_area < 0.0) {
    return detection;
  }

  detection.found = true;
  detection.bbox = cv::boundingRect(best_contour);
  detection.rotated = best_rect;
  detection.area_px = best_area;
  detection.contour = best_contour;
  detection.shape = classify(best_contour, best_area, best_rect);
  detection.angle_deg = best_rect.angle;

  const double perimeter = cv::arcLength(best_contour, true);
  detection.circularity = perimeter > 1e-6
                              ? 4.0 * CV_PI * best_area /
                                    (perimeter * perimeter)
                              : 0.0;

  // Centroid is more stable than the rotated-rect centre on partial blobs.
  const cv::Moments moments = cv::moments(best_contour);
  if (std::abs(moments.m00) > 1e-6) {
    detection.center = cv::Point2f(
        static_cast<float>(moments.m10 / moments.m00),
        static_cast<float>(moments.m01 / moments.m00));
  } else {
    detection.center = best_rect.center;
  }

  if (detection.shape == TargetShape::kCircle) {
    cv::Point2f circle_center;
    float radius = 0.f;
    cv::minEnclosingCircle(best_contour, circle_center, radius);
    detection.center = circle_center;
    detection.radius_px = radius;
  }

  return detection;
}

}  // namespace fc01_vision
