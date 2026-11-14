#pragma once

#include <cstdint>

#include <opencv2/core.hpp>

#include "fc01_vision/color_detector.hpp"
#include "fc01_vision/target_estimator.hpp"
#include "fc01_vision/types.hpp"

namespace fc01_vision {

// Detection -> 3-D estimate -> alpha-beta filtered target state.
// Not thread-safe: one consumer thread owns the pipeline.
class VisionPipeline {
 public:
  VisionPipeline(DetectorConfig detector_config,
                 EstimatorConfig estimator_config, FilterConfig filter_config);

  TargetState process(const cv::Mat& bgr,
                      const CameraIntrinsics& intrinsics, int64_t stamp_ns);

  void reset();

  const Detection& lastDetection() const { return last_detection_; }
  const TargetState& lastState() const { return last_state_; }

  cv::Mat drawDebug(const cv::Mat& bgr) const;

  // Live tuning (OpenCV trackbars). Replacing a config recreates the
  // detector/estimator; the filter state is kept.
  const DetectorConfig& detectorConfig() const { return detector_.config(); }
  const EstimatorConfig& estimatorConfig() const { return estimator_.config(); }
  const FilterConfig& filterConfig() const { return filter_; }
  void setDetectorConfig(const DetectorConfig& config) {
    detector_ = ColorDetector(config);
  }
  void setEstimatorConfig(const EstimatorConfig& config) {
    estimator_ = TargetEstimator(config);
  }
  void setFilterConfig(const FilterConfig& config) { filter_ = config; }

 private:
  TargetState makeLostState(int64_t stamp_ns);
  void updateCovariance(TargetState& state, const Estimate& estimate,
                        double dt, const CameraIntrinsics& intrinsics) const;

  ColorDetector detector_;
  TargetEstimator estimator_;
  FilterConfig filter_;

  Detection last_detection_;
  TargetState last_state_;

  bool have_estimate_{false};
  double x_{0.0};
  double y_{0.0};
  double z_{0.0};
  double vx_{0.0};
  double vy_{0.0};
  double vz_{0.0};
  int64_t last_update_stamp_ns_{0};
  int64_t last_valid_stamp_ns_{0};
  uint64_t seq_{0};
};

}  // namespace fc01_vision
