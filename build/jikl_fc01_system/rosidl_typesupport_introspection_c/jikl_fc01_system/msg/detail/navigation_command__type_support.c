// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jikl_fc01_system:msg/NavigationCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jikl_fc01_system/msg/detail/navigation_command__rosidl_typesupport_introspection_c.h"
#include "jikl_fc01_system/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jikl_fc01_system/msg/detail/navigation_command__functions.h"
#include "jikl_fc01_system/msg/detail/navigation_command__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `source_id`
// Member `frame_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jikl_fc01_system__msg__NavigationCommand__init(message_memory);
}

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_fini_function(void * message_memory)
{
  jikl_fc01_system__msg__NavigationCommand__fini(message_memory);
}

size_t jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__size_function__NavigationCommand__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__fetch_function__NavigationCommand__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__assign_function__NavigationCommand__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__size_function__NavigationCommand__sticks(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__sticks(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__sticks(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__fetch_function__NavigationCommand__sticks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__sticks(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__assign_function__NavigationCommand__sticks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__sticks(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_member_array[14] = {
  {
    "schema_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, schema_version),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, sequence),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, stamp),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, reset_counter),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, source_id),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, position_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, yaw_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sticks_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, sticks_valid),  // bytes offset in struct
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
    offsetof(jikl_fc01_system__msg__NavigationCommand, position),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__size_function__NavigationCommand__position,  // size() function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__position,  // get_const(index) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__position,  // get(index) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__fetch_function__NavigationCommand__position,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__assign_function__NavigationCommand__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sticks",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(jikl_fc01_system__msg__NavigationCommand, sticks),  // bytes offset in struct
    NULL,  // default value
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__size_function__NavigationCommand__sticks,  // size() function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_const_function__NavigationCommand__sticks,  // get_const(index) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__get_function__NavigationCommand__sticks,  // get(index) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__fetch_function__NavigationCommand__sticks,  // fetch(index, &value) function pointer
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__assign_function__NavigationCommand__sticks,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_members = {
  "jikl_fc01_system__msg",  // message namespace
  "NavigationCommand",  // message name
  14,  // number of fields
  sizeof(jikl_fc01_system__msg__NavigationCommand),
  jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_member_array,  // message members
  jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_type_support_handle = {
  0,
  &jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jikl_fc01_system
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jikl_fc01_system, msg, NavigationCommand)() {
  jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_type_support_handle.typesupport_identifier) {
    jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jikl_fc01_system__msg__NavigationCommand__rosidl_typesupport_introspection_c__NavigationCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
