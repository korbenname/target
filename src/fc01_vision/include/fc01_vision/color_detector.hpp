#pragma once

#include <opencv2/core.hpp>

#include "fc01_vision/types.hpp"

namespace fc01_vision {

// HSV threshold + contour detection. Returns the largest valid blob.
class ColorDetector {
 public:
  explicit ColorDetector(DetectorConfig config);

  Detection detect(const cv::Mat& bgr) const;

  // Exposed for tuning / debug preview.
  cv::Mat mask(const cv::Mat& bgr) const;

  const DetectorConfig& config() const { return config_; }

 private:
  TargetShape classify(const std::vector<cv::Point>& contour, double area,
                       const cv::RotatedRect& rotated) const;

  DetectorConfig config_;
};

}  // namespace fc01_vision
