// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jikl_fc01_system:msg/NavigationCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_HPP_

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
# define DEPRECATED__jikl_fc01_system__msg__NavigationCommand __attribute__((deprecated))
#else
# define DEPRECATED__jikl_fc01_system__msg__NavigationCommand __declspec(deprecated)
#endif

namespace jikl_fc01_system
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NavigationCommand_
{
  using Type = NavigationCommand_<ContainerAllocator>;

  explicit NavigationCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
      this->mode = 0;
      this->valid = false;
      this->position_valid = false;
      this->yaw_valid = false;
      this->sticks_valid = false;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->yaw = 0.0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->sticks.begin(), this->sticks.end(), 0.0);
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->mode = 0;
      this->valid = false;
      this->position_valid = false;
      this->yaw_valid = false;
      this->sticks_valid = false;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->yaw = 0.0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->sticks.begin(), this->sticks.end(), 0.0);
    }
  }

  explicit NavigationCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    source_id(_alloc),
    frame_id(_alloc),
    position(_alloc),
    sticks(_alloc)
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
      this->mode = 0;
      this->valid = false;
      this->position_valid = false;
      this->yaw_valid = false;
      this->sticks_valid = false;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->yaw = 0.0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->sticks.begin(), this->sticks.end(), 0.0);
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->source_id = "";
      this->frame_id = "";
      this->mode = 0;
      this->valid = false;
      this->position_valid = false;
      this->yaw_valid = false;
      this->sticks_valid = false;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->yaw = 0.0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->sticks.begin(), this->sticks.end(), 0.0);
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
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _valid_type =
    bool;
  _valid_type valid;
  using _position_valid_type =
    bool;
  _position_valid_type position_valid;
  using _yaw_valid_type =
    bool;
  _yaw_valid_type yaw_valid;
  using _sticks_valid_type =
    bool;
  _sticks_valid_type sticks_valid;
  using _position_type =
    std::array<double, 3>;
  _position_type position;
  using _yaw_type =
    double;
  _yaw_type yaw;
  using _sticks_type =
    std::array<double, 4>;
  _sticks_type sticks;

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
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__position_valid(
    const bool & _arg)
  {
    this->position_valid = _arg;
    return *this;
  }
  Type & set__yaw_valid(
    const bool & _arg)
  {
    this->yaw_valid = _arg;
    return *this;
  }
  Type & set__sticks_valid(
    const bool & _arg)
  {
    this->sticks_valid = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__sticks(
    const std::array<double, 4> & _arg)
  {
    this->sticks = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t DISABLED =
    0u;
  static constexpr uint8_t HOLD =
    1u;
  static constexpr uint8_t CRUISE =
    2u;
  static constexpr uint8_t FOLLOW =
    3u;
  static constexpr uint8_t LAND =
    4u;

  // pointer types
  using RawPtr =
    jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jikl_fc01_system__msg__NavigationCommand
    std::shared_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jikl_fc01_system__msg__NavigationCommand
    std::shared_ptr<jikl_fc01_system::msg::NavigationCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NavigationCommand_ & other) const
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
    if (this->mode != other.mode) {
      return false;
    }
    if (this->valid != other.valid) {
      return false;
    }
    if (this->position_valid != other.position_valid) {
      return false;
    }
    if (this->yaw_valid != other.yaw_valid) {
      return false;
    }
    if (this->sticks_valid != other.sticks_valid) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->sticks != other.sticks) {
      return false;
    }
    return true;
  }
  bool operator!=(const NavigationCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NavigationCommand_

// alias to use template instance with default allocator
using NavigationCommand =
  jikl_fc01_system::msg::NavigationCommand_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationCommand_<ContainerAllocator>::DISABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationCommand_<ContainerAllocator>::HOLD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationCommand_<ContainerAllocator>::CRUISE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationCommand_<ContainerAllocator>::FOLLOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationCommand_<ContainerAllocator>::LAND;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_HPP_
