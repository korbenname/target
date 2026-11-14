// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__BUILDER_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jikl_fc01_system/msg/detail/vision_health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jikl_fc01_system
{

namespace msg
{

namespace builder
{

class Init_VisionHealth_alignment_id
{
public:
  explicit Init_VisionHealth_alignment_id(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  ::jikl_fc01_system::msg::VisionHealth alignment_id(::jikl_fc01_system::msg::VisionHealth::_alignment_id_type arg)
  {
    msg_.alignment_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_extrinsics_id
{
public:
  explicit Init_VisionHealth_extrinsics_id(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_alignment_id extrinsics_id(::jikl_fc01_system::msg::VisionHealth::_extrinsics_id_type arg)
  {
    msg_.extrinsics_id = std::move(arg);
    return Init_VisionHealth_alignment_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_quality
{
public:
  explicit Init_VisionHealth_quality(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_extrinsics_id quality(::jikl_fc01_system::msg::VisionHealth::_quality_type arg)
  {
    msg_.quality = std::move(arg);
    return Init_VisionHealth_extrinsics_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_quality_valid
{
public:
  explicit Init_VisionHealth_quality_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_quality quality_valid(::jikl_fc01_system::msg::VisionHealth::_quality_valid_type arg)
  {
    msg_.quality_valid = std::move(arg);
    return Init_VisionHealth_quality(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_angular_velocity_source
{
public:
  explicit Init_VisionHealth_angular_velocity_source(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_quality_valid angular_velocity_source(::jikl_fc01_system::msg::VisionHealth::_angular_velocity_source_type arg)
  {
    msg_.angular_velocity_source = std::move(arg);
    return Init_VisionHealth_quality_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_angular_velocity_valid
{
public:
  explicit Init_VisionHealth_angular_velocity_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_angular_velocity_source angular_velocity_valid(::jikl_fc01_system::msg::VisionHealth::_angular_velocity_valid_type arg)
  {
    msg_.angular_velocity_valid = std::move(arg);
    return Init_VisionHealth_angular_velocity_source(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_attitude_valid
{
public:
  explicit Init_VisionHealth_attitude_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_angular_velocity_valid attitude_valid(::jikl_fc01_system::msg::VisionHealth::_attitude_valid_type arg)
  {
    msg_.attitude_valid = std::move(arg);
    return Init_VisionHealth_angular_velocity_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_velocity_valid
{
public:
  explicit Init_VisionHealth_velocity_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_attitude_valid velocity_valid(::jikl_fc01_system::msg::VisionHealth::_velocity_valid_type arg)
  {
    msg_.velocity_valid = std::move(arg);
    return Init_VisionHealth_attitude_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_position_valid
{
public:
  explicit Init_VisionHealth_position_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_velocity_valid position_valid(::jikl_fc01_system::msg::VisionHealth::_position_valid_type arg)
  {
    msg_.position_valid = std::move(arg);
    return Init_VisionHealth_velocity_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_metric_scale_valid
{
public:
  explicit Init_VisionHealth_metric_scale_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_position_valid metric_scale_valid(::jikl_fc01_system::msg::VisionHealth::_metric_scale_valid_type arg)
  {
    msg_.metric_scale_valid = std::move(arg);
    return Init_VisionHealth_position_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_extrinsics_valid
{
public:
  explicit Init_VisionHealth_extrinsics_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_metric_scale_valid extrinsics_valid(::jikl_fc01_system::msg::VisionHealth::_extrinsics_valid_type arg)
  {
    msg_.extrinsics_valid = std::move(arg);
    return Init_VisionHealth_metric_scale_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_time_sync_valid
{
public:
  explicit Init_VisionHealth_time_sync_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_extrinsics_valid time_sync_valid(::jikl_fc01_system::msg::VisionHealth::_time_sync_valid_type arg)
  {
    msg_.time_sync_valid = std::move(arg);
    return Init_VisionHealth_extrinsics_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_frame_alignment_valid
{
public:
  explicit Init_VisionHealth_frame_alignment_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_time_sync_valid frame_alignment_valid(::jikl_fc01_system::msg::VisionHealth::_frame_alignment_valid_type arg)
  {
    msg_.frame_alignment_valid = std::move(arg);
    return Init_VisionHealth_time_sync_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_calibration_valid
{
public:
  explicit Init_VisionHealth_calibration_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_frame_alignment_valid calibration_valid(::jikl_fc01_system::msg::VisionHealth::_calibration_valid_type arg)
  {
    msg_.calibration_valid = std::move(arg);
    return Init_VisionHealth_frame_alignment_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_tracking
{
public:
  explicit Init_VisionHealth_tracking(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_calibration_valid tracking(::jikl_fc01_system::msg::VisionHealth::_tracking_type arg)
  {
    msg_.tracking = std::move(arg);
    return Init_VisionHealth_calibration_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_initialized
{
public:
  explicit Init_VisionHealth_initialized(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_tracking initialized(::jikl_fc01_system::msg::VisionHealth::_initialized_type arg)
  {
    msg_.initialized = std::move(arg);
    return Init_VisionHealth_tracking(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_reset_valid
{
public:
  explicit Init_VisionHealth_reset_valid(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_initialized reset_valid(::jikl_fc01_system::msg::VisionHealth::_reset_valid_type arg)
  {
    msg_.reset_valid = std::move(arg);
    return Init_VisionHealth_initialized(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_reset_counter
{
public:
  explicit Init_VisionHealth_reset_counter(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_reset_valid reset_counter(::jikl_fc01_system::msg::VisionHealth::_reset_counter_type arg)
  {
    msg_.reset_counter = std::move(arg);
    return Init_VisionHealth_reset_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_body_frame_id
{
public:
  explicit Init_VisionHealth_body_frame_id(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_reset_counter body_frame_id(::jikl_fc01_system::msg::VisionHealth::_body_frame_id_type arg)
  {
    msg_.body_frame_id = std::move(arg);
    return Init_VisionHealth_reset_counter(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_frame_id
{
public:
  explicit Init_VisionHealth_frame_id(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_body_frame_id frame_id(::jikl_fc01_system::msg::VisionHealth::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_VisionHealth_body_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_source_id
{
public:
  explicit Init_VisionHealth_source_id(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_frame_id source_id(::jikl_fc01_system::msg::VisionHealth::_source_id_type arg)
  {
    msg_.source_id = std::move(arg);
    return Init_VisionHealth_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_sequence
{
public:
  explicit Init_VisionHealth_sequence(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_source_id sequence(::jikl_fc01_system::msg::VisionHealth::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_VisionHealth_source_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_stamp
{
public:
  explicit Init_VisionHealth_stamp(::jikl_fc01_system::msg::VisionHealth & msg)
  : msg_(msg)
  {}
  Init_VisionHealth_sequence stamp(::jikl_fc01_system::msg::VisionHealth::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_VisionHealth_sequence(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

class Init_VisionHealth_schema_version
{
public:
  Init_VisionHealth_schema_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VisionHealth_stamp schema_version(::jikl_fc01_system::msg::VisionHealth::_schema_version_type arg)
  {
    msg_.schema_version = std::move(arg);
    return Init_VisionHealth_stamp(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionHealth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jikl_fc01_system::msg::VisionHealth>()
{
  return jikl_fc01_system::msg::builder::Init_VisionHealth_schema_version();
}

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__BUILDER_HPP_
