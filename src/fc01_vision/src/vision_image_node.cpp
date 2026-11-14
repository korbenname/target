// ROS-image-driven vision node. No dependency on jikl_fc01_system, so it can
// be built and used with the MuJoCo simulator (or any camera driver) before
// the VisionState message package is available.
//
// Outputs (all best effort, volatile):
//   jikl_fc01_system/VisionState ~/state            primary contract output
//   geometry_msgs/PointStamped   ~/target_relative  FRD position, NaN if invalid
//   std_msgs/Bool                ~/target_valid
//   sensor_msgs/Image            ~/debug_image      optional
#include <cmath>
#include <limits>
#include <memory>
#include <mutex>
#include <string>

#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <jikl_fc01_system/msg/vision_state.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/bool.hpp>

#include "fc01_vision/param_utils.hpp"
#include "fc01_vision/tuning_window.hpp"
#include "fc01_vision/vision_pipeline.hpp"
#include "fc01_vision/vision_state_adapter.hpp"

namespace fc01_vision {

class VisionImageNode : public rclcpp::Node {
 public:
  VisionImageNode() : rclcpp::Node("fc01_vision_image") {
    const int fallback_width =
        static_cast<int>(declare_parameter<int>("frame_width", 640));
    const int fallback_height =
        static_cast<int>(declare_parameter<int>("frame_height", 480));

    const DetectorConfig detector_config = declareDetectorConfig(*this);
    const EstimatorConfig estimator_config = declareEstimatorConfig(*this);
    const FilterConfig filter_config = declareFilterConfig(*this);
    intrinsics_ = declareIntrinsics(*this, fallback_width, fallback_height);

    use_camera_info_ = declare_parameter<bool>("use_camera_info", true);
    frame_id_ = declare_parameter<std::string>("frame_id", "body_frd");
    // Fixed camera mount pitch, positive = camera tilted up. The measured
    // optical-frame vector is rotated into body FRD before publishing.
    camera_pitch_rad_ =
        declare_parameter<double>("camera_pitch_deg", 0.0) *
        3.14159265358979323846 / 180.0;
    publish_debug_image_ =
        declare_parameter<bool>("publish_debug_image", false);
    // OpenCV highgui window: live preview + trackbars for the detector.
    const bool show_tuning_window =
        declare_parameter<bool>("show_tuning_window", false);
    const std::string tuning_window_name =
        declare_parameter<std::string>("tuning_window_name",
                                       "fc01 vision tuning");

    const std::string image_topic =
        declare_parameter<std::string>("image_topic", "/sim/camera/image_raw");
    const std::string info_topic = declare_parameter<std::string>(
        "camera_info_topic", "/sim/camera/camera_info");
    const std::string relative_topic = declare_parameter<std::string>(
        "relative_topic", "/fc01/vision/target_relative");
    const std::string valid_topic =
        declare_parameter<std::string>("valid_topic",
                                       "/fc01/vision/target_valid");
    const std::string state_topic =
        declare_parameter<std::string>("state_topic", "/fc01/vision/state");

    adapter_config_.source_id =
        declare_parameter<std::string>("source_id", "fc01_vision_image");
    adapter_config_.body_frame_id =
        declare_parameter<std::string>("body_frame_id", "body_frd");
    adapter_config_.invalid_position_std_m =
        declare_parameter<double>("invalid_position_std_m", 1000.0);
    adapter_config_.invalid_velocity_std_mps =
        declare_parameter<double>("invalid_velocity_std_mps", 1000.0);

    pipeline_ = std::make_unique<VisionPipeline>(
        detector_config, estimator_config, filter_config);

    if (show_tuning_window) {
      // The trackbars cover exactly the parameters the detector uses; the
      // preview is the same annotated frame as the debug image.
      if (!tuning_.create(tuning_window_name, *pipeline_)) {
        RCLCPP_WARN(get_logger(),
                    "show_tuning_window=true but no GUI is available; "
                    "continuing without the slider window");
      } else {
        show_tuning_ = true;
        RCLCPP_INFO(get_logger(),
                    "tuning window '%s' opened: HSV threshold, blob filters, "
                    "target diameter",
                    tuning_window_name.c_str());
      }
    }

    const auto sensor_qos = rclcpp::SensorDataQoS();
    image_sub_ = create_subscription<sensor_msgs::msg::Image>(
        image_topic, sensor_qos,
        [this](sensor_msgs::msg::Image::ConstSharedPtr message) {
          onImage(std::move(message));
        });

    if (use_camera_info_) {
      info_sub_ = create_subscription<sensor_msgs::msg::CameraInfo>(
          info_topic, sensor_qos,
          [this](sensor_msgs::msg::CameraInfo::ConstSharedPtr message) {
            onCameraInfo(std::move(message));
          });
    }

    rclcpp::QoS output_qos(rclcpp::KeepLast(5));
    output_qos.best_effort().durability_volatile();
    relative_pub_ =
        create_publisher<geometry_msgs::msg::PointStamped>(relative_topic,
                                                           output_qos);
    valid_pub_ =
        create_publisher<std_msgs::msg::Bool>(valid_topic, output_qos);
    state_pub_ = create_publisher<jikl_fc01_system::msg::VisionState>(
        state_topic, output_qos);

    if (publish_debug_image_) {
      // RELIABLE so every desktop viewer works: rqt_image_view subscribes with
      // a reliable profile, and a reliable publisher is also compatible with
      // best-effort subscribers. The main outputs stay BEST_EFFORT.
      rclcpp::QoS debug_qos(rclcpp::KeepLast(5));
      debug_qos.reliable().durability_volatile();
      debug_pub_ = create_publisher<sensor_msgs::msg::Image>(
          declare_parameter<std::string>("debug_image_topic",
                                         "/fc01/vision/debug_image"),
          debug_qos);
    }

    RCLCPP_INFO(get_logger(),
                "image input %s, output state=%s relative=%s valid=%s; "
                "target shape=%s diameter=%.3f m; camera pitch=%.1f deg",
                image_topic.c_str(), state_topic.c_str(),
                relative_topic.c_str(), valid_topic.c_str(),
                detector_config.shape.c_str(),
                estimator_config.target_diameter_m,
                camera_pitch_rad_ * 180.0 / 3.14159265358979323846);
    if (!intrinsics_.valid()) {
      RCLCPP_WARN(get_logger(),
                  "no valid intrinsics yet; waiting for CameraInfo on %s",
                  info_topic.c_str());
    }
  }

 private:
  void onCameraInfo(const sensor_msgs::msg::CameraInfo::ConstSharedPtr& msg) {
    if (msg->k[0] <= 0.0 || msg->k[4] <= 0.0) {
      return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    intrinsics_.fx = msg->k[0];
    intrinsics_.fy = msg->k[4];
    intrinsics_.cx = msg->k[2];
    intrinsics_.cy = msg->k[5];
    intrinsics_.width = static_cast<int>(msg->width);
    intrinsics_.height = static_cast<int>(msg->height);
    if (!have_info_) {
      have_info_ = true;
      RCLCPP_INFO(get_logger(),
                  "using CameraInfo intrinsics fx=%.2f fy=%.2f cx=%.2f "
                  "cy=%.2f (%dx%d)",
                  intrinsics_.fx, intrinsics_.fy, intrinsics_.cx,
                  intrinsics_.cy, intrinsics_.width, intrinsics_.height);
    }
  }

  void onImage(const sensor_msgs::msg::Image::ConstSharedPtr& msg) {
    cv_bridge::CvImagePtr cv_image;
    try {
      cv_image = cv_bridge::toCvCopy(msg, "bgr8");
    } catch (const cv_bridge::Exception& error) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000,
                           "cv_bridge conversion failed: %s", error.what());
      return;
    }

    TargetState state;
    bool calibration_valid = false;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      const int64_t stamp_ns =
          rclcpp::Time(msg->header.stamp).nanoseconds();
      state = pipeline_->process(cv_image->image, intrinsics_, stamp_ns);
      calibration_valid = intrinsics_.valid();
    }

    // Camera mount pitch -> body FRD. The pipeline reports the target in
    // the camera optical frame mapped to FRD, which only equals body FRD
    // when the camera is level. Rotate about the body y (right) axis.
    if (state.position_valid && camera_pitch_rad_ != 0.0) {
      const double c = std::cos(camera_pitch_rad_);
      const double s = std::sin(camera_pitch_rad_);
      const double x = state.x;
      const double z = state.z;
      state.x = c * x + s * z;
      state.z = -s * x + c * z;
    }

    geometry_msgs::msg::PointStamped relative;
    relative.header = msg->header;
    relative.header.frame_id = frame_id_;
    if (state.position_valid) {
      relative.point.x = state.x;
      relative.point.y = state.y;
      relative.point.z = state.z;
    } else {
      const double nan = std::numeric_limits<double>::quiet_NaN();
      relative.point.x = nan;
      relative.point.y = nan;
      relative.point.z = nan;
    }
    relative_pub_->publish(relative);

    std_msgs::msg::Bool valid;
    valid.data = state.detected && state.position_valid;
    valid_pub_->publish(valid);

    // Primary contract output: target state in body FRD (frame_id).
    adapter_config_.calibration_valid = calibration_valid;
    jikl_fc01_system::msg::VisionState vision_state;
    fillVisionState(state, rclcpp::Time(msg->header.stamp), frame_id_,
                    adapter_config_, vision_state);
    state_pub_->publish(vision_state);

    if (show_tuning_) {
      cv::Mat debug;
      {
        std::lock_guard<std::mutex> lock(mutex_);
        const bool changed = tuning_.poll(*pipeline_);
        if (changed) {
          // Re-run on the same frame so the preview reacts immediately.
          state = pipeline_->process(cv_image->image, intrinsics_,
                                     rclcpp::Time(msg->header.stamp)
                                         .nanoseconds());
        }
        debug = pipeline_->drawDebug(cv_image->image);
      }
      tuning_.show(debug);
    }

    if (debug_pub_) {
      cv::Mat debug;
      {
        std::lock_guard<std::mutex> lock(mutex_);
        debug = pipeline_->drawDebug(cv_image->image);
      }
      debug_pub_->publish(
          *cv_bridge::CvImage(msg->header, "bgr8", debug).toImageMsg());
    }

    if (++frame_count_ % 60 == 0) {
      RCLCPP_INFO(get_logger(),
                  "frames=%llu detected=%d valid=%d range=%.2f "
                  "pos_frd=(%.2f, %.2f, %.2f) %s",
                  static_cast<unsigned long long>(frame_count_),
                  state.detected ? 1 : 0, state.position_valid ? 1 : 0,
                  state.distance, state.x, state.y, state.z,
                  state.reason.c_str());
    }
  }

  CameraIntrinsics intrinsics_;
  bool use_camera_info_{true};
  bool have_info_{false};
  bool publish_debug_image_{false};
  std::string frame_id_;
  double camera_pitch_rad_{0.0};
  std::mutex mutex_;

  std::unique_ptr<VisionPipeline> pipeline_;
  TuningWindow tuning_;
  bool show_tuning_{false};
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr relative_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr valid_pub_;
  rclcpp::Publisher<jikl_fc01_system::msg::VisionState>::SharedPtr state_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr debug_pub_;
  AdapterConfig adapter_config_;
  uint64_t frame_count_{0};
};

}  // namespace fc01_vision

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<fc01_vision::VisionImageNode>());
  rclcpp::shutdown();
  return 0;
}
