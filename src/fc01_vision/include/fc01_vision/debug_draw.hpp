#pragma once

#include <opencv2/core.hpp>

#include "fc01_vision/types.hpp"

namespace fc01_vision {

// Draws the detection, the estimated position and a small mask inset.
// The input image is not modified.
cv::Mat drawDebugOverlay(const cv::Mat& bgr, const Detection& detection,
                         const TargetState& state, const cv::Mat& mask = {});

}  // namespace fc01_vision
