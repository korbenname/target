// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__TRAITS_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jikl_fc01_system/msg/detail/vision_health__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace jikl_fc01_system
{

namespace msg
{

inline void to_flow_style_yaml(
  const VisionHealth & msg,
  std::ostream & out)
{
  out << "{";
  // member: schema_version
  {
    out << "schema_version: ";
    rosidl_generator_traits::value_to_yaml(msg.schema_version, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: sequence
  {
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << ", ";
  }

  // member: source_id
  {
    out << "source_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_id, out);
    out << ", ";
  }

  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: body_frame_id
  {
    out << "body_frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.body_frame_id, out);
    out << ", ";
  }

  // member: reset_counter
  {
    out << "reset_counter: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_counter, out);
    out << ", ";
  }

  // member: reset_valid
  {
    out << "reset_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_valid, out);
    out << ", ";
  }

  // member: initialized
  {
    out << "initialized: ";
    rosidl_generator_traits::value_to_yaml(msg.initialized, out);
    out << ", ";
  }

  // member: tracking
  {
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << ", ";
  }

  // member: calibration_valid
  {
    out << "calibration_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_valid, out);
    out << ", ";
  }

  // member: frame_alignment_valid
  {
    out << "frame_alignment_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_alignment_valid, out);
    out << ", ";
  }

  // member: time_sync_valid
  {
    out << "time_sync_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.time_sync_valid, out);
    out << ", ";
  }

  // member: extrinsics_valid
  {
    out << "extrinsics_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.extrinsics_valid, out);
    out << ", ";
  }

  // member: metric_scale_valid
  {
    out << "metric_scale_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.metric_scale_valid, out);
    out << ", ";
  }

  // member: position_valid
  {
    out << "position_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.position_valid, out);
    out << ", ";
  }

  // member: velocity_valid
  {
    out << "velocity_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_valid, out);
    out << ", ";
  }

  // member: attitude_valid
  {
    out << "attitude_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.attitude_valid, out);
    out << ", ";
  }

  // member: angular_velocity_valid
  {
    out << "angular_velocity_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity_valid, out);
    out << ", ";
  }

  // member: angular_velocity_source
  {
    out << "angular_velocity_source: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity_source, out);
    out << ", ";
  }

  // member: quality_valid
  {
    out << "quality_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.quality_valid, out);
    out << ", ";
  }

  // member: quality
  {
    out << "quality: ";
    rosidl_generator_traits::value_to_yaml(msg.quality, out);
    out << ", ";
  }

  // member: extrinsics_id
  {
    out << "extrinsics_id: ";
    rosidl_generator_traits::value_to_yaml(msg.extrinsics_id, out);
    out << ", ";
  }

  // member: alignment_id
  {
    out << "alignment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.alignment_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VisionHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: schema_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "schema_version: ";
    rosidl_generator_traits::value_to_yaml(msg.schema_version, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << "\n";
  }

  // member: source_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_id, out);
    out << "\n";
  }

  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: body_frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "body_frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.body_frame_id, out);
    out << "\n";
  }

  // member: reset_counter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_counter: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_counter, out);
    out << "\n";
  }

  // member: reset_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_valid, out);
    out << "\n";
  }

  // member: initialized
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "initialized: ";
    rosidl_generator_traits::value_to_yaml(msg.initialized, out);
    out << "\n";
  }

  // member: tracking
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << "\n";
  }

  // member: calibration_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calibration_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_valid, out);
    out << "\n";
  }

  // member: frame_alignment_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_alignment_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_alignment_valid, out);
    out << "\n";
  }

  // member: time_sync_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_sync_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.time_sync_valid, out);
    out << "\n";
  }

  // member: extrinsics_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "extrinsics_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.extrinsics_valid, out);
    out << "\n";
  }

  // member: metric_scale_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "metric_scale_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.metric_scale_valid, out);
    out << "\n";
  }

  // member: position_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.position_valid, out);
    out << "\n";
  }

  // member: velocity_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_valid, out);
    out << "\n";
  }

  // member: attitude_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "attitude_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.attitude_valid, out);
    out << "\n";
  }

  // member: angular_velocity_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_velocity_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity_valid, out);
    out << "\n";
  }

  // member: angular_velocity_source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_velocity_source: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity_source, out);
    out << "\n";
  }

  // member: quality_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "quality_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.quality_valid, out);
    out << "\n";
  }

  // member: quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "quality: ";
    rosidl_generator_traits::value_to_yaml(msg.quality, out);
    out << "\n";
  }

  // member: extrinsics_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "extrinsics_id: ";
    rosidl_generator_traits::value_to_yaml(msg.extrinsics_id, out);
    out << "\n";
  }

  // member: alignment_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alignment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.alignment_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VisionHealth & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace jikl_fc01_system

namespace rosidl_generator_traits
{

[[deprecated("use jikl_fc01_system::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jikl_fc01_system::msg::VisionHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  jikl_fc01_system::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jikl_fc01_system::msg::to_yaml() instead")]]
inline std::string to_yaml(const jikl_fc01_system::msg::VisionHealth & msg)
{
  return jikl_fc01_system::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jikl_fc01_system::msg::VisionHealth>()
{
  return "jikl_fc01_system::msg::VisionHealth";
}

template<>
inline const char * name<jikl_fc01_system::msg::VisionHealth>()
{
  return "jikl_fc01_system/msg/VisionHealth";
}

template<>
struct has_fixed_size<jikl_fc01_system::msg::VisionHealth>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jikl_fc01_system::msg::VisionHealth>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jikl_fc01_system::msg::VisionHealth>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__TRAITS_HPP_
