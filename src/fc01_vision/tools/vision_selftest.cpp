// Synthetic-image self test for vision_core. No ROS, no camera required.
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include <opencv2/imgproc.hpp>

#include "fc01_vision/color_detector.hpp"
#include "fc01_vision/target_estimator.hpp"
#include "fc01_vision/vision_pipeline.hpp"

namespace {

int g_failures = 0;

void check(bool condition, const std::string& message) {
  if (!condition) {
    ++g_failures;
    std::printf("[FAIL] %s\n", message.c_str());
  } else {
    std::printf("[ ok ] %s\n", message.c_str());
  }
}

void checkNear(double actual, double expected, double tolerance,
               const std::string& message) {
  const bool ok = std::abs(actual - expected) <= tolerance;
  char buffer[256];
  std::snprintf(buffer, sizeof(buffer), "%s (actual=%.4f expected=%.4f tol=%.4f)",
                message.c_str(), actual, expected, tolerance);
  check(ok, buffer);
}

fc01_vision::DetectorConfig redDetector() {
  fc01_vision::DetectorConfig config;
  config.blur_kernel = 5;
  config.morph_kernel = 5;
  config.min_area_ratio = 0.001;
  config.max_area_ratio = 0.5;
  config.shape = "auto";
  fc01_vision::HsvRange low;
  low.h_min = 0;
  low.h_max = 10;
  low.s_min = 120;
  low.s_max = 255;
  low.v_min = 80;
  low.v_max = 255;
  fc01_vision::HsvRange high = low;
  high.h_min = 170;
  high.h_max = 180;
  config.ranges = {low, high};
  return config;
}

fc01_vision::CameraIntrinsics testIntrinsics() {
  fc01_vision::CameraIntrinsics intrinsics;
  intrinsics.fx = 600.0;
  intrinsics.fy = 600.0;
  intrinsics.cx = 320.0;
  intrinsics.cy = 240.0;
  intrinsics.width = 640;
  intrinsics.height = 480;
  return intrinsics;
}

void testRectangleDetectionAndPnp() {
  cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
  cv::rectangle(image, cv::Point(360, 270), cv::Point(440, 330),
                cv::Scalar(0, 0, 255), cv::FILLED);

  fc01_vision::ColorDetector detector(redDetector());
  const fc01_vision::Detection detection = detector.detect(image);

  check(detection.found, "red rectangle is detected");
  if (!detection.found) {
    return;
  }
  checkNear(detection.center.x, 400.0, 3.0, "rectangle centre x");
  checkNear(detection.center.y, 300.0, 3.0, "rectangle centre y");
  checkNear(detection.bbox.width, 80.0, 6.0, "rectangle width");
  checkNear(detection.bbox.height, 60.0, 6.0, "rectangle height");

  fc01_vision::EstimatorConfig config;
  config.target_width_m = 0.20;
  config.target_height_m = 0.15;
  config.min_range_m = 0.1;
  config.max_range_m = 20.0;
  config.use_pnp = true;

  fc01_vision::TargetEstimator estimator(config);
  const fc01_vision::Estimate estimate =
      estimator.estimate(detection, testIntrinsics());

  check(estimate.position_valid, "PnP estimate is valid");
  checkNear(estimate.distance_m, 1.5, 0.08, "PnP range");
  checkNear(estimate.position_frd[0], 1.5, 0.08, "PnP FRD x (forward)");
  checkNear(estimate.position_frd[1], 0.20, 0.05, "PnP FRD y (right)");
  checkNear(estimate.position_frd[2], 0.15, 0.05, "PnP FRD z (down)");
}

void testCircleDetectionAndRange() {
  cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
  cv::circle(image, cv::Point(320, 240), 30, cv::Scalar(255, 0, 0),
             cv::FILLED);

  fc01_vision::DetectorConfig detector_config;
  detector_config.blur_kernel = 5;
  detector_config.morph_kernel = 5;
  detector_config.min_area_ratio = 0.001;
  detector_config.max_area_ratio = 0.5;
  detector_config.shape = "circle";
  fc01_vision::HsvRange blue;
  blue.h_min = 100;
  blue.h_max = 140;
  blue.s_min = 120;
  blue.s_max = 255;
  blue.v_min = 80;
  blue.v_max = 255;
  detector_config.ranges = {blue};

  fc01_vision::ColorDetector detector(detector_config);
  const fc01_vision::Detection detection = detector.detect(image);
  check(detection.found, "blue circle is detected");
  if (!detection.found) {
    return;
  }

  fc01_vision::EstimatorConfig estimator_config;
  estimator_config.target_diameter_m = 0.10;
  estimator_config.min_range_m = 0.1;
  estimator_config.max_range_m = 20.0;
  fc01_vision::TargetEstimator estimator(estimator_config);
  const fc01_vision::Estimate estimate =
      estimator.estimate(detection, testIntrinsics());

  check(estimate.position_valid, "circle range estimate is valid");
  checkNear(estimate.distance_m, 1.0, 0.1, "circle range");
  checkNear(estimate.position_frd[1], 0.0, 0.05, "circle FRD y");
  checkNear(estimate.position_frd[2], 0.0, 0.05, "circle FRD z");
}

void testBearingOnlyWithoutSize() {
  cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
  cv::rectangle(image, cv::Point(430, 270), cv::Point(510, 330),
                cv::Scalar(0, 0, 255), cv::FILLED);

  fc01_vision::ColorDetector detector(redDetector());
  const fc01_vision::Detection detection = detector.detect(image);
  if (!detection.found) {
    check(false, "bearing-only input detected");
    return;
  }

  fc01_vision::EstimatorConfig config;  // no physical size
  fc01_vision::TargetEstimator estimator(config);
  const fc01_vision::Estimate estimate =
      estimator.estimate(detection, testIntrinsics());

  check(!estimate.position_valid, "bearing-only is not a valid position");
  check(estimate.yaw_rad > 0.0, "bearing points to the right");
}

void testStaleness() {
  cv::Mat target = cv::Mat::zeros(480, 640, CV_8UC3);
  cv::rectangle(target, cv::Point(360, 270), cv::Point(440, 330),
                cv::Scalar(0, 0, 255), cv::FILLED);
  const cv::Mat empty = cv::Mat::zeros(480, 640, CV_8UC3);

  fc01_vision::EstimatorConfig estimator_config;
  estimator_config.target_width_m = 0.20;
  estimator_config.target_height_m = 0.15;
  fc01_vision::FilterConfig filter_config;
  filter_config.stale_timeout_s = 0.20;

  fc01_vision::VisionPipeline pipeline(redDetector(), estimator_config,
                                       filter_config);

  const int64_t t0 = 1000000000LL;
  const auto first = pipeline.process(target, testIntrinsics(), t0);
  check(first.position_valid, "first detection produces a valid position");

  const auto short_gap = pipeline.process(empty, testIntrinsics(),
                                          t0 + 50000000LL);  // +50 ms
  check(short_gap.position_valid, "short dropout stays valid (coasting)");

  const auto long_gap = pipeline.process(empty, testIntrinsics(),
                                         t0 + 400000000LL);  // +400 ms
  check(!long_gap.position_valid, "long dropout becomes invalid");
  check(!long_gap.detected, "long dropout is not detected");
}

}  // namespace

int main() {
  testRectangleDetectionAndPnp();
  testCircleDetectionAndRange();
  testBearingOnlyWithoutSize();
  testStaleness();

  if (g_failures == 0) {
    std::printf("\nAll vision_core self tests passed.\n");
    return 0;
  }
  std::printf("\n%d self test(s) failed.\n", g_failures);
  return 1;
}
