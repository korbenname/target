// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jikl_fc01_system:msg/NavigationCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__BUILDER_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jikl_fc01_system/msg/detail/navigation_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jikl_fc01_system
{

namespace msg
{

namespace builder
{

class Init_NavigationCommand_sticks
{
public:
  explicit Init_NavigationCommand_sticks(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  ::jikl_fc01_system::msg::NavigationCommand sticks(::jikl_fc01_system::msg::NavigationCommand::_sticks_type arg)
  {
    msg_.sticks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_yaw
{
public:
  explicit Init_NavigationCommand_yaw(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_sticks yaw(::jikl_fc01_system::msg::NavigationCommand::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_NavigationCommand_sticks(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_position
{
public:
  explicit Init_NavigationCommand_position(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_yaw position(::jikl_fc01_system::msg::NavigationCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_NavigationCommand_yaw(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_sticks_valid
{
public:
  explicit Init_NavigationCommand_sticks_valid(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_position sticks_valid(::jikl_fc01_system::msg::NavigationCommand::_sticks_valid_type arg)
  {
    msg_.sticks_valid = std::move(arg);
    return Init_NavigationCommand_position(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_yaw_valid
{
public:
  explicit Init_NavigationCommand_yaw_valid(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_sticks_valid yaw_valid(::jikl_fc01_system::msg::NavigationCommand::_yaw_valid_type arg)
  {
    msg_.yaw_valid = std::move(arg);
    return Init_NavigationCommand_sticks_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_position_valid
{
public:
  explicit Init_NavigationCommand_position_valid(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_yaw_valid position_valid(::jikl_fc01_system::msg::NavigationCommand::_position_valid_type arg)
  {
    msg_.position_valid = std::move(arg);
    return Init_NavigationCommand_yaw_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_valid
{
public:
  explicit Init_NavigationCommand_valid(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_position_valid valid(::jikl_fc01_system::msg::NavigationCommand::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_NavigationCommand_position_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_mode
{
public:
  explicit Init_NavigationCommand_mode(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_valid mode(::jikl_fc01_system::msg::NavigationCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_NavigationCommand_valid(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_frame_id
{
public:
  explicit Init_NavigationCommand_frame_id(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_mode frame_id(::jikl_fc01_system::msg::NavigationCommand::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_NavigationCommand_mode(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_source_id
{
public:
  explicit Init_NavigationCommand_source_id(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_frame_id source_id(::jikl_fc01_system::msg::NavigationCommand::_source_id_type arg)
  {
    msg_.source_id = std::move(arg);
    return Init_NavigationCommand_frame_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_reset_counter
{
public:
  explicit Init_NavigationCommand_reset_counter(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_source_id reset_counter(::jikl_fc01_system::msg::NavigationCommand::_reset_counter_type arg)
  {
    msg_.reset_counter = std::move(arg);
    return Init_NavigationCommand_source_id(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_stamp
{
public:
  explicit Init_NavigationCommand_stamp(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_reset_counter stamp(::jikl_fc01_system::msg::NavigationCommand::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_NavigationCommand_reset_counter(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_sequence
{
public:
  explicit Init_NavigationCommand_sequence(::jikl_fc01_system::msg::NavigationCommand & msg)
  : msg_(msg)
  {}
  Init_NavigationCommand_stamp sequence(::jikl_fc01_system::msg::NavigationCommand::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_NavigationCommand_stamp(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

class Init_NavigationCommand_schema_version
{
public:
  Init_NavigationCommand_schema_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigationCommand_sequence schema_version(::jikl_fc01_system::msg::NavigationCommand::_schema_version_type arg)
  {
    msg_.schema_version = std::move(arg);
    return Init_NavigationCommand_sequence(msg_);
  }

private:
  ::jikl_fc01_system::msg::NavigationCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jikl_fc01_system::msg::NavigationCommand>()
{
  return jikl_fc01_system::msg::builder::Init_NavigationCommand_schema_version();
}

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__BUILDER_HPP_
