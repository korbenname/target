// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jikl_fc01_system:msg/VelocityCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__jikl_fc01_system__msg__VelocityCommand __attribute__((deprecated))
#else
# define DEPRECATED__jikl_fc01_system__msg__VelocityCommand __declspec(deprecated)
#endif

namespace jikl_fc01_system
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VelocityCommand_
{
  using Type = VelocityCommand_<ContainerAllocator>;

  explicit VelocityCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->schema_version = 1;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->schema_version = 0;
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->valid = false;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->wz = 0.0;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->valid = false;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->wz = 0.0;
    }
  }

  explicit VelocityCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    source_id(_alloc),
    frame_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->schema_version = 1;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->schema_version = 0;
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->valid = false;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->wz = 0.0;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->valid = false;
      this->vx = 0.0;
      this->vy = 0.0;
      this->vz = 0.0;
      this->wz = 0.0;
    }
  }

  // field types and members
  using _schema_version_type =
    uint16_t;
  _schema_version_type schema_version;
  using _sequence_type =
    uint64_t;
  _sequence_type sequence;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _reset_counter_type =
    uint32_t;
  _reset_counter_type reset_counter;
  using _source_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_id_type source_id;
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _valid_type =
    bool;
  _valid_type valid;
  using _vx_type =
    double;
  _vx_type vx;
  using _vy_type =
    double;
  _vy_type vy;
  using _vz_type =
    double;
  _vz_type vz;
  using _wz_type =
    double;
  _wz_type wz;

  // setters for named parameter idiom
  Type & set__schema_version(
    const uint16_t & _arg)
  {
    this->schema_version = _arg;
    return *this;
  }
  Type & set__sequence(
    const uint64_t & _arg)
  {
    this->sequence = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__reset_counter(
    const uint32_t & _arg)
  {
    this->reset_counter = _arg;
    return *this;
  }
  Type & set__source_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_id = _arg;
    return *this;
  }
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__vx(
    const double & _arg)
  {
    this->vx = _arg;
    return *this;
  }
  Type & set__vy(
    const double & _arg)
  {
    this->vy = _arg;
    return *this;
  }
  Type & set__vz(
    const double & _arg)
  {
    this->vz = _arg;
    return *this;
  }
  Type & set__wz(
    const double & _arg)
  {
    this->wz = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jikl_fc01_system__msg__VelocityCommand
    std::shared_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jikl_fc01_system__msg__VelocityCommand
    std::shared_ptr<jikl_fc01_system::msg::VelocityCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelocityCommand_ & other) const
  {
    if (this->schema_version != other.schema_version) {
      return false;
    }
    if (this->sequence != other.sequence) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->reset_counter != other.reset_counter) {
      return false;
    }
    if (this->source_id != other.source_id) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->valid != other.valid) {
      return false;
    }
    if (this->vx != other.vx) {
      return false;
    }
    if (this->vy != other.vy) {
      return false;
    }
    if (this->vz != other.vz) {
      return false;
    }
    if (this->wz != other.wz) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelocityCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelocityCommand_

// alias to use template instance with default allocator
using VelocityCommand =
  jikl_fc01_system::msg::VelocityCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_HPP_
