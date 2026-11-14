// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_H_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'source_id'
// Member 'frame_id'
// Member 'body_frame_id'
// Member 'angular_velocity_source'
// Member 'extrinsics_id'
// Member 'alignment_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VisionHealth in the package jikl_fc01_system.
/**
  * Explicit metadata for ONE raw Odometry measurement, joined by exact stamp.
  * All confirmations default false. A live topic does not imply tracking/quality.
 */
typedef struct jikl_fc01_system__msg__VisionHealth
{
  uint16_t schema_version;
  builtin_interfaces__msg__Time stamp;
  uint64_t sequence;
  rosidl_runtime_c__String source_id;
  /// Exact raw Odometry header.frame_id and child_frame_id.
  rosidl_runtime_c__String frame_id;
  rosidl_runtime_c__String body_frame_id;
  uint32_t reset_counter;
  bool reset_valid;
  bool initialized;
  bool tracking;
  bool calibration_valid;
  bool frame_alignment_valid;
  bool time_sync_valid;
  bool extrinsics_valid;
  bool metric_scale_valid;
  bool position_valid;
  bool velocity_valid;
  bool attitude_valid;
  bool angular_velocity_valid;
  rosidl_runtime_c__String angular_velocity_source;
  bool quality_valid;
  /// Internal normalized [0,1], only valid when quality_valid; vendor scale needs adapter.
  double quality;
  /// Bind to immutable, explicitly configured calibration/alignment identifiers.
  rosidl_runtime_c__String extrinsics_id;
  rosidl_runtime_c__String alignment_id;
} jikl_fc01_system__msg__VisionHealth;

// Struct for a sequence of jikl_fc01_system__msg__VisionHealth.
typedef struct jikl_fc01_system__msg__VisionHealth__Sequence
{
  jikl_fc01_system__msg__VisionHealth * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jikl_fc01_system__msg__VisionHealth__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_HEALTH__STRUCT_H_
