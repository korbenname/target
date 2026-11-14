// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__BUILDER_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jikl_fc01_system/msg/detail/vision_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jikl_fc01_system
{

namespace msg
{

namespace builder
{

class Init_VisionState_quality
{
public:
  explicit Init_VisionState_quality(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  ::jikl_fc01_system::msg::VisionState quality(::jikl_fc01_system::msg::VisionState::_quality_type arg)
  {
    msg_.quality = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_twist_covariance
{
public:
  explicit Init_VisionState_twist_covariance(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_quality twist_covariance(::jikl_fc01_system::msg::VisionState::_twist_covariance_type arg)
  {
    msg_.twist_covariance = std::move(arg);
    return Init_VisionState_quality(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_pose_covariance
{
public:
  explicit Init_VisionState_pose_covariance(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_twist_covariance pose_covariance(::jikl_fc01_system::msg::VisionState::_pose_covariance_type arg)
  {
    msg_.pose_covariance = std::move(arg);
    return Init_VisionState_twist_covariance(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_angular_velocity
{
public:
  explicit Init_VisionState_angular_velocity(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_pose_covariance angular_velocity(::jikl_fc01_system::msg::VisionState::_angular_velocity_type arg)
  {
    msg_.angular_velocity = std::move(arg);
    return Init_VisionState_pose_covariance(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_attitude
{
public:
  explicit Init_VisionState_attitude(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_angular_velocity attitude(::jikl_fc01_system::msg::VisionState::_attitude_type arg)
  {
    msg_.attitude = std::move(arg);
    return Init_VisionState_angular_velocity(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_velocity
{
public:
  explicit Init_VisionState_velocity(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_attitude velocity(::jikl_fc01_system::msg::VisionState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_VisionState_attitude(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_position
{
public:
  explicit Init_VisionState_position(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_velocity position(::jikl_fc01_system::msg::VisionState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_VisionState_velocity(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_valid_fields
{
public:
  explicit Init_VisionState_valid_fields(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_position valid_fields(::jikl_fc01_system::msg::VisionState::_valid_fields_type arg)
  {
    msg_.valid_fields = std::move(arg);
    return Init_VisionState_position(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_calibration_valid
{
public:
  explicit Init_VisionState_calibration_valid(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_valid_fields calibration_valid(::jikl_fc01_system::msg::VisionState::_calibration_valid_type arg)
  {
    msg_.calibration_valid = std::move(arg);
    return Init_VisionState_valid_fields(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_tracking
{
public:
  explicit Init_VisionState_tracking(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_calibration_valid tracking(::jikl_fc01_system::msg::VisionState::_tracking_type arg)
  {
    msg_.tracking = std::move(arg);
    return Init_VisionState_calibration_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_initialized
{
public:
  explicit Init_VisionState_initialized(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_tracking initialized(::jikl_fc01_system::msg::VisionState::_initialized_type arg)
  {
    msg_.initialized = std::move(arg);
    return Init_VisionState_tracking(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_angular_velocity_source
{
public:
  explicit Init_VisionState_angular_velocity_source(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_initialized angular_velocity_source(::jikl_fc01_system::msg::VisionState::_angular_velocity_source_type arg)
  {
    msg_.angular_velocity_source = std::move(arg);
    return Init_VisionState_initialized(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_source_id
{
public:
  explicit Init_VisionState_source_id(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_angular_velocity_source source_id(::jikl_fc01_system::msg::VisionState::_source_id_type arg)
  {
    msg_.source_id = std::move(arg);
    return Init_VisionState_angular_velocity_source(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_body_frame_id
{
public:
  explicit Init_VisionState_body_frame_id(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_source_id body_frame_id(::jikl_fc01_system::msg::VisionState::_body_frame_id_type arg)
  {
    msg_.body_frame_id = std::move(arg);
    return Init_VisionState_source_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_frame_id
{
public:
  explicit Init_VisionState_frame_id(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_body_frame_id frame_id(::jikl_fc01_system::msg::VisionState::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_VisionState_body_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_reset_counter
{
public:
  explicit Init_VisionState_reset_counter(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_frame_id reset_counter(::jikl_fc01_system::msg::VisionState::_reset_counter_type arg)
  {
    msg_.reset_counter = std::move(arg);
    return Init_VisionState_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_stamp
{
public:
  explicit Init_VisionState_stamp(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_reset_counter stamp(::jikl_fc01_system::msg::VisionState::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_VisionState_reset_counter(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_sequence
{
public:
  explicit Init_VisionState_sequence(::jikl_fc01_system::msg::VisionState & msg)
  : msg_(msg)
  {}
  Init_VisionState_stamp sequence(::jikl_fc01_system::msg::VisionState::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_VisionState_stamp(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

class Init_VisionState_schema_version
{
public:
  Init_VisionState_schema_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VisionState_sequence schema_version(::jikl_fc01_system::msg::VisionState::_schema_version_type arg)
  {
    msg_.schema_version = std::move(arg);
    return Init_VisionState_sequence(msg_);
  }

private:
  ::jikl_fc01_system::msg::VisionState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jikl_fc01_system::msg::VisionState>()
{
  return jikl_fc01_system::msg::builder::Init_VisionState_schema_version();
}

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__BUILDER_HPP_
