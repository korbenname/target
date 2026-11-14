// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jikl_fc01_system/msg/detail/vision_state__rosidl_typesupport_introspection_c.h"
#include "jikl_fc01_system/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jikl_fc01_system/msg/detail/vision_state__functions.h"
#include "jikl_fc01_system/msg/detail/vision_state__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `frame_id`
// Member `body_frame_id`
// Member `source_id`
// Member `angular_velocity_source`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jikl_fc01_system__msg__VisionState__init(message_memory);
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_fini_function(void * message_memory)
{
  jikl_fc01_system__msg__VisionState__fini(message_memory);
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__velocity(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__velocity(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__velocity(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__velocity(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__velocity(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__attitude(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__attitude(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__attitude(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__attitude(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__attitude(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__attitude(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__attitude(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__angular_velocity(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__angular_velocity(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__angular_velocity(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__angular_velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__angular_velocity(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__angular_velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__angular_velocity(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__pose_covariance(
  const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__pose_covariance(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__pose_covariance(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__pose_covariance(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__pose_covariance(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__pose_covariance(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__pose_covariance(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__twist_covariance(
  const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__twist_covariance(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__twist_covariance(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__twist_covariance(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__twist_covariance(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__twist_covariance(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__twist_covariance(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_member_array[19] = {
  {
    "schema_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, schema_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sequence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, sequence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "reset_counter",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, reset_counter),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "body_frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, body_frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "source_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, source_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_velocity_source",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, angular_velocity_source),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "initialized",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, initialized),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tracking",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, tracking),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "calibration_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, calibration_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "valid_fields",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, valid_fields),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, position),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__position,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__position,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__position,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__position,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, velocity),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__velocity,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__velocity,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__velocity,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__velocity,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__velocity,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "attitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, attitude),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__attitude,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__attitude,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__attitude,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__attitude,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__attitude,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, angular_velocity),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__angular_velocity,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__angular_velocity,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__angular_velocity,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__angular_velocity,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__angular_velocity,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_covariance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, pose_covariance),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__pose_covariance,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__pose_covariance,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__pose_covariance,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__pose_covariance,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__pose_covariance,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "twist_covariance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, twist_covariance),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__size_function__VisionState__twist_covariance,  // size() function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_const_function__VisionState__twist_covariance,  // get_const(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__get_function__VisionState__twist_covariance,  // get(index) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__fetch_function__VisionState__twist_covariance,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__assign_function__VisionState__twist_covariance,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__VisionState, quality),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_members = {
  "jikl_fc01_system__msg",  // message namespace
  "VisionState",  // message name
  19,  // number of fields
  sizeof(jikl_fc01_system__msg__VisionState),
  jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_member_array,  // message members
  jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_init_function,  // function to initialize message memory (memory has to be allocated)
  jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_type_support_handle = {
  0,
  &jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jikl_fc01_system
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jikl_fc01_system, msg, VisionState)() {
  jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_type_support_handle.typesupport_identifier) {
    jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jikl_fc01_system__msg__VisionState__rosidl_typesupport_introspection_c__VisionState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
