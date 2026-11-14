// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_HPP_

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
# define DEPRECATED__jikl_fc01_system__msg__VisionState __attribute__((deprecated))
#else
# define DEPRECATED__jikl_fc01_system__msg__VisionState __declspec(deprecated)
#endif

namespace jikl_fc01_system
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VisionState_
{
  using Type = VisionState_<ContainerAllocator>;

  explicit VisionState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
      this->frame_id = "";
      this->body_frame_id = "";
      this->source_id = "";
      this->angular_velocity_source = "";
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->valid_fields = 0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->attitude.begin(), this->attitude.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->angular_velocity.begin(), this->angular_velocity.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->pose_covariance.begin(), this->pose_covariance.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->twist_covariance.begin(), this->twist_covariance.end(), 0.0);
      this->quality = 0.0;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->frame_id = "";
      this->body_frame_id = "";
      this->source_id = "";
      this->angular_velocity_source = "";
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->valid_fields = 0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->attitude.begin(), this->attitude.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->angular_velocity.begin(), this->angular_velocity.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->pose_covariance.begin(), this->pose_covariance.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->twist_covariance.begin(), this->twist_covariance.end(), 0.0);
      this->quality = 0.0;
    }
  }

  explicit VisionState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    frame_id(_alloc),
    body_frame_id(_alloc),
    source_id(_alloc),
    angular_velocity_source(_alloc),
    position(_alloc),
    velocity(_alloc),
    attitude(_alloc),
    angular_velocity(_alloc),
    pose_covariance(_alloc),
    twist_covariance(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->schema_version = 1;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->schema_version = 0;
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->frame_id = "";
      this->body_frame_id = "";
      this->source_id = "";
      this->angular_velocity_source = "";
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->valid_fields = 0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->attitude.begin(), this->attitude.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->angular_velocity.begin(), this->angular_velocity.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->pose_covariance.begin(), this->pose_covariance.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->twist_covariance.begin(), this->twist_covariance.end(), 0.0);
      this->quality = 0.0;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->reset_counter = 0ul;
      this->frame_id = "";
      this->body_frame_id = "";
      this->source_id = "";
      this->angular_velocity_source = "";
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->valid_fields = 0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->attitude.begin(), this->attitude.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->angular_velocity.begin(), this->angular_velocity.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->pose_covariance.begin(), this->pose_covariance.end(), 0.0);
      std::fill<typename std::array<double, 36>::iterator, double>(this->twist_covariance.begin(), this->twist_covariance.end(), 0.0);
      this->quality = 0.0;
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
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _body_frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _body_frame_id_type body_frame_id;
  using _source_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_id_type source_id;
  using _angular_velocity_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _angular_velocity_source_type angular_velocity_source;
  using _initialized_type =
    bool;
  _initialized_type initialized;
  using _tracking_type =
    bool;
  _tracking_type tracking;
  using _calibration_valid_type =
    bool;
  _calibration_valid_type calibration_valid;
  using _valid_fields_type =
    uint16_t;
  _valid_fields_type valid_fields;
  using _position_type =
    std::array<double, 3>;
  _position_type position;
  using _velocity_type =
    std::array<double, 3>;
  _velocity_type velocity;
  using _attitude_type =
    std::array<double, 4>;
  _attitude_type attitude;
  using _angular_velocity_type =
    std::array<double, 3>;
  _angular_velocity_type angular_velocity;
  using _pose_covariance_type =
    std::array<double, 36>;
  _pose_covariance_type pose_covariance;
  using _twist_covariance_type =
    std::array<double, 36>;
  _twist_covariance_type twist_covariance;
  using _quality_type =
    double;
  _quality_type quality;

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
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__body_frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->body_frame_id = _arg;
    return *this;
  }
  Type & set__source_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_id = _arg;
    return *this;
  }
  Type & set__angular_velocity_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->angular_velocity_source = _arg;
    return *this;
  }
  Type & set__initialized(
    const bool & _arg)
  {
    this->initialized = _arg;
    return *this;
  }
  Type & set__tracking(
    const bool & _arg)
  {
    this->tracking = _arg;
    return *this;
  }
  Type & set__calibration_valid(
    const bool & _arg)
  {
    this->calibration_valid = _arg;
    return *this;
  }
  Type & set__valid_fields(
    const uint16_t & _arg)
  {
    this->valid_fields = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const std::array<double, 3> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__attitude(
    const std::array<double, 4> & _arg)
  {
    this->attitude = _arg;
    return *this;
  }
  Type & set__angular_velocity(
    const std::array<double, 3> & _arg)
  {
    this->angular_velocity = _arg;
    return *this;
  }
  Type & set__pose_covariance(
    const std::array<double, 36> & _arg)
  {
    this->pose_covariance = _arg;
    return *this;
  }
  Type & set__twist_covariance(
    const std::array<double, 36> & _arg)
  {
    this->twist_covariance = _arg;
    return *this;
  }
  Type & set__quality(
    const double & _arg)
  {
    this->quality = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t POSITION =
    1u;
  static constexpr uint16_t VELOCITY =
    2u;
  static constexpr uint16_t ATTITUDE =
    4u;
  static constexpr uint16_t ANGULAR_VELOCITY =
    8u;
  static constexpr uint16_t POSE_COVARIANCE =
    16u;
  static constexpr uint16_t TWIST_COVARIANCE =
    32u;
  static constexpr uint16_t QUALITY =
    64u;

  // pointer types
  using RawPtr =
    jikl_fc01_system::msg::VisionState_<ContainerAllocator> *;
  using ConstRawPtr =
    const jikl_fc01_system::msg::VisionState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VisionState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VisionState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jikl_fc01_system__msg__VisionState
    std::shared_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jikl_fc01_system__msg__VisionState
    std::shared_ptr<jikl_fc01_system::msg::VisionState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VisionState_ & other) const
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
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->body_frame_id != other.body_frame_id) {
      return false;
    }
    if (this->source_id != other.source_id) {
      return false;
    }
    if (this->angular_velocity_source != other.angular_velocity_source) {
      return false;
    }
    if (this->initialized != other.initialized) {
      return false;
    }
    if (this->tracking != other.tracking) {
      return false;
    }
    if (this->calibration_valid != other.calibration_valid) {
      return false;
    }
    if (this->valid_fields != other.valid_fields) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->attitude != other.attitude) {
      return false;
    }
    if (this->angular_velocity != other.angular_velocity) {
      return false;
    }
    if (this->pose_covariance != other.pose_covariance) {
      return false;
    }
    if (this->twist_covariance != other.twist_covariance) {
      return false;
    }
    if (this->quality != other.quality) {
      return false;
    }
    return true;
  }
  bool operator!=(const VisionState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VisionState_

// alias to use template instance with default allocator
using VisionState =
  jikl_fc01_system::msg::VisionState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::POSITION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::VELOCITY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::ATTITUDE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::ANGULAR_VELOCITY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::POSE_COVARIANCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::TWIST_COVARIANCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VisionState_<ContainerAllocator>::QUALITY;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_HPP_
