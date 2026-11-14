// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_H_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'POSITION'.
enum
{
  jikl_fc01_system__msg__VisionState__POSITION = 1
};

/// Constant 'VELOCITY'.
enum
{
  jikl_fc01_system__msg__VisionState__VELOCITY = 2
};

/// Constant 'ATTITUDE'.
enum
{
  jikl_fc01_system__msg__VisionState__ATTITUDE = 4
};

/// Constant 'ANGULAR_VELOCITY'.
enum
{
  jikl_fc01_system__msg__VisionState__ANGULAR_VELOCITY = 8
};

/// Constant 'POSE_COVARIANCE'.
enum
{
  jikl_fc01_system__msg__VisionState__POSE_COVARIANCE = 16
};

/// Constant 'TWIST_COVARIANCE'.
enum
{
  jikl_fc01_system__msg__VisionState__TWIST_COVARIANCE = 32
};

/// Constant 'QUALITY'.
enum
{
  jikl_fc01_system__msg__VisionState__QUALITY = 64
};

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'frame_id'
// Member 'body_frame_id'
// Member 'source_id'
// Member 'angular_velocity_source'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VisionState in the package jikl_fc01_system.
/**
  * Temporary FC01 internal contract V1; this is not a vendor camera interface.
 */
typedef struct jikl_fc01_system__msg__VisionState
{
  uint16_t schema_version;
  uint64_t sequence;
  /// Measurement time in the explicitly agreed ROS/system domain; not callback time.
  builtin_interfaces__msg__Time stamp;
  uint32_t reset_counter;
  rosidl_runtime_c__String frame_id;
  rosidl_runtime_c__String body_frame_id;
  rosidl_runtime_c__String source_id;
  rosidl_runtime_c__String angular_velocity_source;
  bool initialized;
  bool tracking;
  bool calibration_valid;
  /// Default mask 0 means every default numeric payload is UNKNOWN.
  uint16_t valid_fields;
  double position[3];
  double velocity[3];
  /// Hamilton w,x,y,z, rotating body FRD into fc01_vision_ned. Not ROS xyzw.
  double attitude[4];
  /// Body FRD, rad/s. Valid only with ANGULAR_VELOCITY and nonempty source.
  double angular_velocity[3];
  /// Row-major 6x6, linear xyz then fixed-axis angular xyz. Separate validity bits.
  double pose_covariance[36];
  double twist_covariance[36];
  /// Explicit normalized [0,1] internal quality; unknown unless QUALITY is set.
  double quality;
} jikl_fc01_system__msg__VisionState;

// Struct for a sequence of jikl_fc01_system__msg__VisionState.
typedef struct jikl_fc01_system__msg__VisionState__Sequence
{
  jikl_fc01_system__msg__VisionState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jikl_fc01_system__msg__VisionState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__STRUCT_H_
