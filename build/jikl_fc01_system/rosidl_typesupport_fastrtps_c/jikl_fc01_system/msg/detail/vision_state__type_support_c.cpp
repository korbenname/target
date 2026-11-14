// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice
#include "jikl_fc01_system/msg/detail/vision_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "jikl_fc01_system/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "jikl_fc01_system/msg/detail/vision_state__struct.h"
#include "jikl_fc01_system/msg/detail/vision_state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "builtin_interfaces/msg/detail/time__functions.h"  // stamp
#include "rosidl_runtime_c/string.h"  // angular_velocity_source, body_frame_id, frame_id, source_id
#include "rosidl_runtime_c/string_functions.h"  // angular_velocity_source, body_frame_id, frame_id, source_id

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_jikl_fc01_system
size_t get_serialized_size_builtin_interfaces__msg__Time(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_jikl_fc01_system
size_t max_serialized_size_builtin_interfaces__msg__Time(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_jikl_fc01_system
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time)();


using _VisionState__ros_msg_type = jikl_fc01_system__msg__VisionState;

static bool _VisionState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _VisionState__ros_msg_type * ros_message = static_cast<const _VisionState__ros_msg_type *>(untyped_ros_message);
  // Field name: schema_version
  {
    cdr << ros_message->schema_version;
  }

  // Field name: sequence
  {
    cdr << ros_message->sequence;
  }

  // Field name: stamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->stamp, cdr))
    {
      return false;
    }
  }

  // Field name: reset_counter
  {
    cdr << ros_message->reset_counter;
  }

  // Field name: frame_id
  {
    const rosidl_runtime_c__String * str = &ros_message->frame_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: body_frame_id
  {
    const rosidl_runtime_c__String * str = &ros_message->body_frame_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: source_id
  {
    const rosidl_runtime_c__String * str = &ros_message->source_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: angular_velocity_source
  {
    const rosidl_runtime_c__String * str = &ros_message->angular_velocity_source;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: initialized
  {
    cdr << (ros_message->initialized ? true : false);
  }

  // Field name: tracking
  {
    cdr << (ros_message->tracking ? true : false);
  }

  // Field name: calibration_valid
  {
    cdr << (ros_message->calibration_valid ? true : false);
  }

  // Field name: valid_fields
  {
    cdr << ros_message->valid_fields;
  }

  // Field name: position
  {
    size_t size = 3;
    auto array_ptr = ros_message->position;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->velocity;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: attitude
  {
    size_t size = 4;
    auto array_ptr = ros_message->attitude;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: angular_velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->angular_velocity;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: pose_covariance
  {
    size_t size = 36;
    auto array_ptr = ros_message->pose_covariance;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: twist_covariance
  {
    size_t size = 36;
    auto array_ptr = ros_message->twist_covariance;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: quality
  {
    cdr << ros_message->quality;
  }

  return true;
}

static bool _VisionState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _VisionState__ros_msg_type * ros_message = static_cast<_VisionState__ros_msg_type *>(untyped_ros_message);
  // Field name: schema_version
  {
    cdr >> ros_message->schema_version;
  }

  // Field name: sequence
  {
    cdr >> ros_message->sequence;
  }

  // Field name: stamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->stamp))
    {
      return false;
    }
  }

  // Field name: reset_counter
  {
    cdr >> ros_message->reset_counter;
  }

  // Field name: frame_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->frame_id.data) {
      rosidl_runtime_c__String__init(&ros_message->frame_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->frame_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'frame_id'\n");
      return false;
    }
  }

  // Field name: body_frame_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->body_frame_id.data) {
      rosidl_runtime_c__String__init(&ros_message->body_frame_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->body_frame_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'body_frame_id'\n");
      return false;
    }
  }

  // Field name: source_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->source_id.data) {
      rosidl_runtime_c__String__init(&ros_message->source_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->source_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'source_id'\n");
      return false;
    }
  }

  // Field name: angular_velocity_source
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->angular_velocity_source.data) {
      rosidl_runtime_c__String__init(&ros_message->angular_velocity_source);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->angular_velocity_source,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'angular_velocity_source'\n");
      return false;
    }
  }

  // Field name: initialized
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->initialized = tmp ? true : false;
  }

  // Field name: tracking
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->tracking = tmp ? true : false;
  }

  // Field name: calibration_valid
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->calibration_valid = tmp ? true : false;
  }

  // Field name: valid_fields
  {
    cdr >> ros_message->valid_fields;
  }

  // Field name: position
  {
    size_t size = 3;
    auto array_ptr = ros_message->position;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->velocity;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: attitude
  {
    size_t size = 4;
    auto array_ptr = ros_message->attitude;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: angular_velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->angular_velocity;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: pose_covariance
  {
    size_t size = 36;
    auto array_ptr = ros_message->pose_covariance;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: twist_covariance
  {
    size_t size = 36;
    auto array_ptr = ros_message->twist_covariance;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: quality
  {
    cdr >> ros_message->quality;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jikl_fc01_system
size_t get_serialized_size_jikl_fc01_system__msg__VisionState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _VisionState__ros_msg_type * ros_message = static_cast<const _VisionState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name schema_version
  {
    size_t item_size = sizeof(ros_message->schema_version);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sequence
  {
    size_t item_size = sizeof(ros_message->sequence);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name stamp

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->stamp), current_alignment);
  // field.name reset_counter
  {
    size_t item_size = sizeof(ros_message->reset_counter);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name frame_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->frame_id.size + 1);
  // field.name body_frame_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->body_frame_id.size + 1);
  // field.name source_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->source_id.size + 1);
  // field.name angular_velocity_source
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->angular_velocity_source.size + 1);
  // field.name initialized
  {
    size_t item_size = sizeof(ros_message->initialized);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tracking
  {
    size_t item_size = sizeof(ros_message->tracking);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name calibration_valid
  {
    size_t item_size = sizeof(ros_message->calibration_valid);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name valid_fields
  {
    size_t item_size = sizeof(ros_message->valid_fields);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name position
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->position;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name velocity
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->velocity;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name attitude
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->attitude;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name angular_velocity
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->angular_velocity;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pose_covariance
  {
    size_t array_size = 36;
    auto array_ptr = ros_message->pose_covariance;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name twist_covariance
  {
    size_t array_size = 36;
    auto array_ptr = ros_message->twist_covariance;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name quality
  {
    size_t item_size = sizeof(ros_message->quality);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _VisionState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jikl_fc01_system__msg__VisionState(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jikl_fc01_system
size_t max_serialized_size_jikl_fc01_system__msg__VisionState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: schema_version
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: sequence
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: stamp
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_builtin_interfaces__msg__Time(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: reset_counter
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: frame_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: body_frame_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: source_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: angular_velocity_source
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: initialized
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: tracking
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: calibration_valid
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: valid_fields
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: position
  {
    size_t array_size = 3;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: velocity
  {
    size_t array_size = 3;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: attitude
  {
    size_t array_size = 4;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: angular_velocity
  {
    size_t array_size = 3;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: pose_covariance
  {
    size_t array_size = 36;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: twist_covariance
  {
    size_t array_size = 36;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: quality
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = jikl_fc01_system__msg__VisionState;
    is_plain =
      (
      offsetof(DataType, quality) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _VisionState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jikl_fc01_system__msg__VisionState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_VisionState = {
  "jikl_fc01_system::msg",
  "VisionState",
  _VisionState__cdr_serialize,
  _VisionState__cdr_deserialize,
  _VisionState__get_serialized_size,
  _VisionState__max_serialized_size
};

static rosidl_message_type_support_t _VisionState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_VisionState,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jikl_fc01_system, msg, VisionState)() {
  return &_VisionState__type_support;
}

#if defined(__cplusplus)
}
#endif
