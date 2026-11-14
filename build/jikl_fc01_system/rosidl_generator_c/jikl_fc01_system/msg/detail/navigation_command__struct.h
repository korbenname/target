// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jikl_fc01_system:msg/NavigationCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_H_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'DISABLED'.
enum
{
  jikl_fc01_system__msg__NavigationCommand__DISABLED = 0
};

/// Constant 'HOLD'.
enum
{
  jikl_fc01_system__msg__NavigationCommand__HOLD = 1
};

/// Constant 'CRUISE'.
enum
{
  jikl_fc01_system__msg__NavigationCommand__CRUISE = 2
};

/// Constant 'FOLLOW'.
enum
{
  jikl_fc01_system__msg__NavigationCommand__FOLLOW = 3
};

/// Constant 'LAND'.
enum
{
  jikl_fc01_system__msg__NavigationCommand__LAND = 4
};

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'source_id'
// Member 'frame_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/NavigationCommand in the package jikl_fc01_system.
/**
  * Motion request only. This message cannot authorize ARM, Offboard, or any lease.
 */
typedef struct jikl_fc01_system__msg__NavigationCommand
{
  uint16_t schema_version;
  uint64_t sequence;
  builtin_interfaces__msg__Time stamp;
  uint32_t reset_counter;
  rosidl_runtime_c__String source_id;
  rosidl_runtime_c__String frame_id;
  uint8_t mode;
  bool valid;
  bool position_valid;
  bool yaw_valid;
  bool sticks_valid;
  /// Absolute point in fc01_vision_ned, metres; Cruise only when position_valid.
  double position[3];
  /// Absolute NED yaw, radians, when yaw_valid.
  double yaw;
  /// roll/pitch/yaw/throttle in [-1,1], valid only for Follow with sticks_valid.
  double sticks[4];
} jikl_fc01_system__msg__NavigationCommand;

// Struct for a sequence of jikl_fc01_system__msg__NavigationCommand.
typedef struct jikl_fc01_system__msg__NavigationCommand__Sequence
{
  jikl_fc01_system__msg__NavigationCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jikl_fc01_system__msg__NavigationCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__NAVIGATION_COMMAND__STRUCT_H_
