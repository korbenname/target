#pragma once

#include "fc01_vision/types.hpp"

namespace fc01_vision {

// Converts a 2-D detection into a 3-D relative position.
//
// Rectangles: planar PnP (IPPE) using the known physical width/height.
// Circles    : range from apparent diameter and the known physical diameter.
// Without a physical size only the bearing is returned (position invalid).
class TargetEstimator {
 public:
  explicit TargetEstimator(EstimatorConfig config);

  Estimate estimate(const Detection& detection,
                    const CameraIntrinsics& intrinsics) const;

  // Optical (x right, y down, z forward) -> body FRD (x forward, y right,
  // z down).
  static cv::Vec3d opticalToFrd(const cv::Vec3d& optical);

  const EstimatorConfig& config() const { return config_; }

 private:
  Estimate estimateRect(const Detection& detection,
                        const CameraIntrinsics& intrinsics) const;
  Estimate estimateCircle(const Detection& detection,
                          const CameraIntrinsics& intrinsics) const;
  Estimate bearingOnly(const Detection& detection,
                       const CameraIntrinsics& intrinsics,
                       const std::string& reason) const;
  Estimate finish(const cv::Vec3d& position_cam,
                  const CameraIntrinsics& intrinsics,
                  const std::string& reason) const;

  EstimatorConfig config_;
};

}  // namespace fc01_vision
