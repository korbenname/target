// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jikl_fc01_system:msg/NavigationCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__TRAITS_HPP_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jikl_fc01_system/msg/detail/navigation_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace jikl_fc01_system
{

namespace msg
{

inline void to_flow_style_yaml(
  const NavigationCommand & msg,
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

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << ", ";
  }

  // member: position_valid
  {
    out << "position_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.position_valid, out);
    out << ", ";
  }

  // member: yaw_valid
  {
    out << "yaw_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_valid, out);
    out << ", ";
  }

  // member: sticks_valid
  {
    out << "sticks_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.sticks_valid, out);
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

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: sticks
  {
    if (msg.sticks.size() == 0) {
      out << "sticks: []";
    } else {
      out << "sticks: [";
      size_t pending_items = msg.sticks.size();
      for (auto item : msg.sticks) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigationCommand & msg,
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

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
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

  // member: yaw_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_valid, out);
    out << "\n";
  }

  // member: sticks_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sticks_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.sticks_valid, out);
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

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: sticks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.sticks.size() == 0) {
      out << "sticks: []\n";
    } else {
      out << "sticks:\n";
      for (auto item : msg.sticks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigationCommand & msg, bool use_flow_style = false)
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
  const jikl_fc01_system::msg::NavigationCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  jikl_fc01_system::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jikl_fc01_system::msg::to_yaml() instead")]]
inline std::string to_yaml(const jikl_fc01_system::msg::NavigationCommand & msg)
{
  return jikl_fc01_system::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jikl_fc01_system::msg::NavigationCommand>()
{
  return "jikl_fc01_system::msg::NavigationCommand";
}

template<>
inline const char * name<jikl_fc01_system::msg::NavigationCommand>()
{
  return "jikl_fc01_system/msg/NavigationCommand";
}

template<>
struct has_fixed_size<jikl_fc01_system::msg::NavigationCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jikl_fc01_system::msg::NavigationCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jikl_fc01_system::msg::NavigationCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__TRAITS_HPP_
