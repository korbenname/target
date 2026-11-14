// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jikl_fc01_system:msg/VelocityCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__BUILDER_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jikl_fc01_system/msg/detail/velocity_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jikl_fc01_system
{

namespace msg
{

namespace builder
{

class Init_VelocityCommand_wz
{
public:
  explicit Init_VelocityCommand_wz(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  ::jikl_fc01_system::msg::VelocityCommand wz(::jikl_fc01_system::msg::VelocityCommand::_wz_type arg)
  {
    msg_.wz = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_vz
{
public:
  explicit Init_VelocityCommand_vz(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_wz vz(::jikl_fc01_system::msg::VelocityCommand::_vz_type arg)
  {
    msg_.vz = std::move(arg);
    return Init_VelocityCommand_wz(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_vy
{
public:
  explicit Init_VelocityCommand_vy(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_vz vy(::jikl_fc01_system::msg::VelocityCommand::_vy_type arg)
  {
    msg_.vy = std::move(arg);
    return Init_VelocityCommand_vz(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_vx
{
public:
  explicit Init_VelocityCommand_vx(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_vy vx(::jikl_fc01_system::msg::VelocityCommand::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_VelocityCommand_vy(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_valid
{
public:
  explicit Init_VelocityCommand_valid(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_vx valid(::jikl_fc01_system::msg::VelocityCommand::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_VelocityCommand_vx(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_frame_id
{
public:
  explicit Init_VelocityCommand_frame_id(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_valid frame_id(::jikl_fc01_system::msg::VelocityCommand::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_VelocityCommand_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_source_id
{
public:
  explicit Init_VelocityCommand_source_id(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_frame_id source_id(::jikl_fc01_system::msg::VelocityCommand::_source_id_type arg)
  {
    msg_.source_id = std::move(arg);
    return Init_VelocityCommand_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_reset_counter
{
public:
  explicit Init_VelocityCommand_reset_counter(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_source_id reset_counter(::jikl_fc01_system::msg::VelocityCommand::_reset_counter_type arg)
  {
    msg_.reset_counter = std::move(arg);
    return Init_VelocityCommand_source_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_stamp
{
public:
  explicit Init_VelocityCommand_stamp(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_reset_counter stamp(::jikl_fc01_system::msg::VelocityCommand::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_VelocityCommand_reset_counter(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_sequence
{
public:
  explicit Init_VelocityCommand_sequence(::jikl_fc01_system::msg::VelocityCommand & msg)
  : msg_(msg)
  {}
  Init_VelocityCommand_stamp sequence(::jikl_fc01_system::msg::VelocityCommand::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_VelocityCommand_stamp(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

class Init_VelocityCommand_schema_version
{
public:
  Init_VelocityCommand_schema_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VelocityCommand_sequence schema_version(::jikl_fc01_system::msg::VelocityCommand::_schema_version_type arg)
  {
    msg_.schema_version = std::move(arg);
    return Init_VelocityCommand_sequence(msg_);
  }

private:
  ::jikl_fc01_system::msg::VelocityCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jikl_fc01_system::msg::VelocityCommand>()
{
  return jikl_fc01_system::msg::builder::Init_VelocityCommand_schema_version();
}

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__BUILDER_HPP_
