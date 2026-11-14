// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_HPP_

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
# define DEPRECATED__jikl_fc01_system__msg__VisionHealth __attribute__((deprecated))
#else
# define DEPRECATED__jikl_fc01_system__msg__VisionHealth __declspec(deprecated)
#endif

namespace jikl_fc01_system
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VisionHealth_
{
  using Type = VisionHealth_<ContainerAllocator>;

  explicit VisionHealth_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->schema_version = 1;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->schema_version = 0;
      this->sequence = 0ull;
      this->source_id = "";
      this->frame_id = "";
      this->body_frame_id = "";
      this->reset_counter = 0ul;
      this->reset_valid = false;
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->frame_alignment_valid = false;
      this->time_sync_valid = false;
      this->extrinsics_valid = false;
      this->metric_scale_valid = false;
      this->position_valid = false;
      this->velocity_valid = false;
      this->attitude_valid = false;
      this->angular_velocity_valid = false;
      this->angular_velocity_source = "";
      this->quality_valid = false;
      this->quality = 0.0;
      this->extrinsics_id = "";
      this->alignment_id = "";
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->source_id = "";
      this->frame_id = "";
      this->body_frame_id = "";
      this->reset_counter = 0ul;
      this->reset_valid = false;
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->frame_alignment_valid = false;
      this->time_sync_valid = false;
      this->extrinsics_valid = false;
      this->metric_scale_valid = false;
      this->position_valid = false;
      this->velocity_valid = false;
      this->attitude_valid = false;
      this->angular_velocity_valid = false;
      this->angular_velocity_source = "";
      this->quality_valid = false;
      this->quality = 0.0;
      this->extrinsics_id = "";
      this->alignment_id = "";
    }
  }

  explicit VisionHealth_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    source_id(_alloc),
    frame_id(_alloc),
    body_frame_id(_alloc),
    angular_velocity_source(_alloc),
    extrinsics_id(_alloc),
    alignment_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->schema_version = 1;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->schema_version = 0;
      this->sequence = 0ull;
      this->source_id = "";
      this->frame_id = "";
      this->body_frame_id = "";
      this->reset_counter = 0ul;
      this->reset_valid = false;
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->frame_alignment_valid = false;
      this->time_sync_valid = false;
      this->extrinsics_valid = false;
      this->metric_scale_valid = false;
      this->position_valid = false;
      this->velocity_valid = false;
      this->attitude_valid = false;
      this->angular_velocity_valid = false;
      this->angular_velocity_source = "";
      this->quality_valid = false;
      this->quality = 0.0;
      this->extrinsics_id = "";
      this->alignment_id = "";
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->source_id = "";
      this->frame_id = "";
      this->body_frame_id = "";
      this->reset_counter = 0ul;
      this->reset_valid = false;
      this->initialized = false;
      this->tracking = false;
      this->calibration_valid = false;
      this->frame_alignment_valid = false;
      this->time_sync_valid = false;
      this->extrinsics_valid = false;
      this->metric_scale_valid = false;
      this->position_valid = false;
      this->velocity_valid = false;
      this->attitude_valid = false;
      this->angular_velocity_valid = false;
      this->angular_velocity_source = "";
      this->quality_valid = false;
      this->quality = 0.0;
      this->extrinsics_id = "";
      this->alignment_id = "";
    }
  }

  // field types and members
  using _schema_version_type =
    uint16_t;
  _schema_version_type schema_version;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _sequence_type =
    uint64_t;
  _sequence_type sequence;
  using _source_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_id_type source_id;
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _body_frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _body_frame_id_type body_frame_id;
  using _reset_counter_type =
    uint32_t;
  _reset_counter_type reset_counter;
  using _reset_valid_type =
    bool;
  _reset_valid_type reset_valid;
  using _initialized_type =
    bool;
  _initialized_type initialized;
  using _tracking_type =
    bool;
  _tracking_type tracking;
  using _calibration_valid_type =
    bool;
  _calibration_valid_type calibration_valid;
  using _frame_alignment_valid_type =
    bool;
  _frame_alignment_valid_type frame_alignment_valid;
  using _time_sync_valid_type =
    bool;
  _time_sync_valid_type time_sync_valid;
  using _extrinsics_valid_type =
    bool;
  _extrinsics_valid_type extrinsics_valid;
  using _metric_scale_valid_type =
    bool;
  _metric_scale_valid_type metric_scale_valid;
  using _position_valid_type =
    bool;
  _position_valid_type position_valid;
  using _velocity_valid_type =
    bool;
  _velocity_valid_type velocity_valid;
  using _attitude_valid_type =
    bool;
  _attitude_valid_type attitude_valid;
  using _angular_velocity_valid_type =
    bool;
  _angular_velocity_valid_type angular_velocity_valid;
  using _angular_velocity_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _angular_velocity_source_type angular_velocity_source;
  using _quality_valid_type =
    bool;
  _quality_valid_type quality_valid;
  using _quality_type =
    double;
  _quality_type quality;
  using _extrinsics_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _extrinsics_id_type extrinsics_id;
  using _alignment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _alignment_id_type alignment_id;

  // setters for named parameter idiom
  Type & set__schema_version(
    const uint16_t & _arg)
  {
    this->schema_version = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__sequence(
    const uint64_t & _arg)
  {
    this->sequence = _arg;
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
  Type & set__body_frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->body_frame_id = _arg;
    return *this;
  }
  Type & set__reset_counter(
    const uint32_t & _arg)
  {
    this->reset_counter = _arg;
    return *this;
  }
  Type & set__reset_valid(
    const bool & _arg)
  {
    this->reset_valid = _arg;
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
  Type & set__frame_alignment_valid(
    const bool & _arg)
  {
    this->frame_alignment_valid = _arg;
    return *this;
  }
  Type & set__time_sync_valid(
    const bool & _arg)
  {
    this->time_sync_valid = _arg;
    return *this;
  }
  Type & set__extrinsics_valid(
    const bool & _arg)
  {
    this->extrinsics_valid = _arg;
    return *this;
  }
  Type & set__metric_scale_valid(
    const bool & _arg)
  {
    this->metric_scale_valid = _arg;
    return *this;
  }
  Type & set__position_valid(
    const bool & _arg)
  {
    this->position_valid = _arg;
    return *this;
  }
  Type & set__velocity_valid(
    const bool & _arg)
  {
    this->velocity_valid = _arg;
    return *this;
  }
  Type & set__attitude_valid(
    const bool & _arg)
  {
    this->attitude_valid = _arg;
    return *this;
  }
  Type & set__angular_velocity_valid(
    const bool & _arg)
  {
    this->angular_velocity_valid = _arg;
    return *this;
  }
  Type & set__angular_velocity_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->angular_velocity_source = _arg;
    return *this;
  }
  Type & set__quality_valid(
    const bool & _arg)
  {
    this->quality_valid = _arg;
    return *this;
  }
  Type & set__quality(
    const double & _arg)
  {
    this->quality = _arg;
    return *this;
  }
  Type & set__extrinsics_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->extrinsics_id = _arg;
    return *this;
  }
  Type & set__alignment_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->alignment_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> *;
  using ConstRawPtr =
    const jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jikl_fc01_system__msg__VisionHealth
    std::shared_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jikl_fc01_system__msg__VisionHealth
    std::shared_ptr<jikl_fc01_system::msg::VisionHealth_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VisionHealth_ & other) const
  {
    if (this->schema_version != other.schema_version) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->sequence != other.sequence) {
      return false;
    }
    if (this->source_id != other.source_id) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->body_frame_id != other.body_frame_id) {
      return false;
    }
    if (this->reset_counter != other.reset_counter) {
      return false;
    }
    if (this->reset_valid != other.reset_valid) {
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
    if (this->frame_alignment_valid != other.frame_alignment_valid) {
      return false;
    }
    if (this->time_sync_valid != other.time_sync_valid) {
      return false;
    }
    if (this->extrinsics_valid != other.extrinsics_valid) {
      return false;
    }
    if (this->metric_scale_valid != other.metric_scale_valid) {
      return false;
    }
    if (this->position_valid != other.position_valid) {
      return false;
    }
    if (this->velocity_valid != other.velocity_valid) {
      return false;
    }
    if (this->attitude_valid != other.attitude_valid) {
      return false;
    }
    if (this->angular_velocity_valid != other.angular_velocity_valid) {
      return false;
    }
    if (this->angular_velocity_source != other.angular_velocity_source) {
      return false;
    }
    if (this->quality_valid != other.quality_valid) {
      return false;
    }
    if (this->quality != other.quality) {
      return false;
    }
    if (this->extrinsics_id != other.extrinsics_id) {
      return false;
    }
    if (this->alignment_id != other.alignment_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const VisionHealth_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VisionHealth_

// alias to use template instance with default allocator
using VisionHealth =
  jikl_fc01_system::msg::VisionHealth_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jikl_fc01_system

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_HPP_
