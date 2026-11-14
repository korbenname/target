// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__TRAITS_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jikl_fc01_system/msg/detail/vision_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace jikl_fc01_system
{

namespace msg
{

inline void to_flow_style_yaml(
  const VisionState & msg,
  std::ostream & out)
{
  out << "{";
  // member: schema_version
  {
    out << "schema_version: ";
    rosidl_generator_traits::value_to_yaml(msg.schema_version, out);
    out << ", ";
  }

  // member: sequence
  {
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: reset_counter
  {
    out << "reset_counter: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_counter, out);
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

  // member: source_id
  {
    out << "source_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_id, out);
    out << ", ";
  }

  // member: angular_velocity_source
  {
    out << "angular_velocity_source: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity_source, out);
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

  // member: valid_fields
  {
    out << "valid_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.valid_fields, out);
    out << ", ";
  }

  // member: position
  {
    if (msg.position.size() == 0) {
      out << "position: []";
    } else {
      out << "position: [";
      size_t pending_items = msg.position.size();
      for (auto item : msg.position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocity
  {
    if (msg.velocity.size() == 0) {
      out << "velocity: []";
    } else {
      out << "velocity: [";
      size_t pending_items = msg.velocity.size();
      for (auto item : msg.velocity) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: attitude
  {
    if (msg.attitude.size() == 0) {
      out << "attitude: []";
    } else {
      out << "attitude: [";
      size_t pending_items = msg.attitude.size();
      for (auto item : msg.attitude) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: angular_velocity
  {
    if (msg.angular_velocity.size() == 0) {
      out << "angular_velocity: []";
    } else {
      out << "angular_velocity: [";
      size_t pending_items = msg.angular_velocity.size();
      for (auto item : msg.angular_velocity) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pose_covariance
  {
    if (msg.pose_covariance.size() == 0) {
      out << "pose_covariance: []";
    } else {
      out << "pose_covariance: [";
      size_t pending_items = msg.pose_covariance.size();
      for (auto item : msg.pose_covariance) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: twist_covariance
  {
    if (msg.twist_covariance.size() == 0) {
      out << "twist_covariance: []";
    } else {
      out << "twist_covariance: [";
      size_t pending_items = msg.twist_covariance.size();
      for (auto item : msg.twist_covariance) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: quality
  {
    out << "quality: ";
    rosidl_generator_traits::value_to_yaml(msg.quality, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VisionState & msg,
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

  // member: sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
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

  // member: reset_counter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_counter: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_counter, out);
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

  // member: source_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_id, out);
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

  // member: valid_fields
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.valid_fields, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocity.size() == 0) {
      out << "velocity: []\n";
    } else {
      out << "velocity:\n";
      for (auto item : msg.velocity) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: attitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.attitude.size() == 0) {
      out << "attitude: []\n";
    } else {
      out << "attitude:\n";
      for (auto item : msg.attitude) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: angular_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.angular_velocity.size() == 0) {
      out << "angular_velocity: []\n";
    } else {
      out << "angular_velocity:\n";
      for (auto item : msg.angular_velocity) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: pose_covariance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose_covariance.size() == 0) {
      out << "pose_covariance: []\n";
    } else {
      out << "pose_covariance:\n";
      for (auto item : msg.pose_covariance) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: twist_covariance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.twist_covariance.size() == 0) {
      out << "twist_covariance: []\n";
    } else {
      out << "twist_covariance:\n";
      for (auto item : msg.twist_covariance) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VisionState & msg, bool use_flow_style = false)
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
  const jikl_fc01_system::msg::VisionState & msg,
  std::ostream & out, size_t indentation = 0)
{
  jikl_fc01_system::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jikl_fc01_system::msg::to_yaml() instead")]]
inline std::string to_yaml(const jikl_fc01_system::msg::VisionState & msg)
{
  return jikl_fc01_system::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jikl_fc01_system::msg::VisionState>()
{
  return "jikl_fc01_system::msg::VisionState";
}

template<>
inline const char * name<jikl_fc01_system::msg::VisionState>()
{
  return "jikl_fc01_system/msg/VisionState";
}

template<>
struct has_fixed_size<jikl_fc01_system::msg::VisionState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jikl_fc01_system::msg::VisionState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jikl_fc01_system::msg::VisionState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__TRAITS_HPP_
