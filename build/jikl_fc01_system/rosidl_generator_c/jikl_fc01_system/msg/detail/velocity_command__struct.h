// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jikl_fc01_system:msg/VelocityCommand.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_H_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VelocityCommand in the package jikl_fc01_system.
/**
  * 上位机（视觉/制导程序）发给飞控的速度指令。
  * 用于让飞机按期望速度飞行并撞向目标。
 */
typedef struct jikl_fc01_system__msg__VelocityCommand
{
  uint16_t schema_version;
  uint64_t sequence;
  /// 指令计算时刻，使用双方约定好的 ROS/系统时钟。
  builtin_interfaces__msg__Time stamp;
  uint32_t reset_counter;
  rosidl_runtime_c__String source_id;
  /// vx/vy/vz 所在坐标系。默认 "body_frd"（机体系：x 前、y 右、z 下）。
  rosidl_runtime_c__String frame_id;
  /// false 表示本帧无效，接收端应保持上一状态或忽略。
  bool valid;
  /// 期望速度，单位 m/s。默认机体系 FRD：
  ///   vx > 0 向前，vx < 0 向后
  ///   vy > 0 向右，vy < 0 向左
  ///   vz > 0 向下，vz < 0 向上
  double vx;
  double vy;
  double vz;
  /// 期望偏航角速度，单位 rad/s，坐标系与 vx/vy/vz 相同（默认 body_frd：
  /// 绕机体 z 轴、向下为正，即俯视顺时针）。作为偏航速率前馈使用；
  /// 0 表示不提供速率前馈，接收端仍按航向角目标跟踪。
  double wz;
} jikl_fc01_system__msg__VelocityCommand;

// Struct for a sequence of jikl_fc01_system__msg__VelocityCommand.
typedef struct jikl_fc01_system__msg__VelocityCommand__Sequence
{
  jikl_fc01_system__msg__VelocityCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jikl_fc01_system__msg__VelocityCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VELOCITY_COMMAND__STRUCT_H_
