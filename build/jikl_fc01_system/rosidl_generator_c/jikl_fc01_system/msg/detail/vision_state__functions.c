// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice
#include "jikl_fc01_system/msg/detail/vision_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `frame_id`
// Member `body_frame_id`
// Member `source_id`
// Member `angular_velocity_source`
#include "rosidl_runtime_c/string_functions.h"

bool
jikl_fc01_system__msg__VisionState__init(jikl_fc01_system__msg__VisionState * msg)
{
  if (!msg) {
    return false;
  }
  // schema_version
  msg->schema_version = 1;
  // sequence
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    jikl_fc01_system__msg__VisionState__fini(msg);
    return false;
  }
  // reset_counter
  // frame_id
  if (!rosidl_runtime_c__String__init(&msg->frame_id)) {
    jikl_fc01_system__msg__VisionState__fini(msg);
    return false;
  }
  // body_frame_id
  if (!rosidl_runtime_c__String__init(&msg->body_frame_id)) {
    jikl_fc01_system__msg__VisionState__fini(msg);
    return false;
  }
  // source_id
  if (!rosidl_runtime_c__String__init(&msg->source_id)) {
    jikl_fc01_system__msg__VisionState__fini(msg);
    return false;
  }
  // angular_velocity_source
  if (!rosidl_runtime_c__String__init(&msg->angular_velocity_source)) {
    jikl_fc01_system__msg__VisionState__fini(msg);
    return false;
  }
  // initialized
  // tracking
  // calibration_valid
  // valid_fields
  // position
  // velocity
  // attitude
  // angular_velocity
  // pose_covariance
  // twist_covariance
  // quality
  return true;
}

void
jikl_fc01_system__msg__VisionState__fini(jikl_fc01_system__msg__VisionState * msg)
{
  if (!msg) {
    return;
  }
  // schema_version
  // sequence
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // reset_counter
  // frame_id
  rosidl_runtime_c__String__fini(&msg->frame_id);
  // body_frame_id
  rosidl_runtime_c__String__fini(&msg->body_frame_id);
  // source_id
  rosidl_runtime_c__String__fini(&msg->source_id);
  // angular_velocity_source
  rosidl_runtime_c__String__fini(&msg->angular_velocity_source);
  // initialized
  // tracking
  // calibration_valid
  // valid_fields
  // position
  // velocity
  // attitude
  // angular_velocity
  // pose_covariance
  // twist_covariance
  // quality
}

bool
jikl_fc01_system__msg__VisionState__are_equal(const jikl_fc01_system__msg__VisionState * lhs, const jikl_fc01_system__msg__VisionState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // schema_version
  if (lhs->schema_version != rhs->schema_version) {
    return false;
  }
  // sequence
  if (lhs->sequence != rhs->sequence) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // reset_counter
  if (lhs->reset_counter != rhs->reset_counter) {
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->frame_id), &(rhs->frame_id)))
  {
    return false;
  }
  // body_frame_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->body_frame_id), &(rhs->body_frame_id)))
  {
    return false;
  }
  // source_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source_id), &(rhs->source_id)))
  {
    return false;
  }
  // angular_velocity_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->angular_velocity_source), &(rhs->angular_velocity_source)))
  {
    return false;
  }
  // initialized
  if (lhs->initialized != rhs->initialized) {
    return false;
  }
  // tracking
  if (lhs->tracking != rhs->tracking) {
    return false;
  }
  // calibration_valid
  if (lhs->calibration_valid != rhs->calibration_valid) {
    return false;
  }
  // valid_fields
  if (lhs->valid_fields != rhs->valid_fields) {
    return false;
  }
  // position
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->position[i] != rhs->position[i]) {
      return false;
    }
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->velocity[i] != rhs->velocity[i]) {
      return false;
    }
  }
  // attitude
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->attitude[i] != rhs->attitude[i]) {
      return false;
    }
  }
  // angular_velocity
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->angular_velocity[i] != rhs->angular_velocity[i]) {
      return false;
    }
  }
  // pose_covariance
  for (size_t i = 0; i < 36; ++i) {
    if (lhs->pose_covariance[i] != rhs->pose_covariance[i]) {
      return false;
    }
  }
  // twist_covariance
  for (size_t i = 0; i < 36; ++i) {
    if (lhs->twist_covariance[i] != rhs->twist_covariance[i]) {
      return false;
    }
  }
  // quality
  if (lhs->quality != rhs->quality) {
    return false;
  }
  return true;
}

bool
jikl_fc01_system__msg__VisionState__copy(
  const jikl_fc01_system__msg__VisionState * input,
  jikl_fc01_system__msg__VisionState * output)
{
  if (!input || !output) {
    return false;
  }
  // schema_version
  output->schema_version = input->schema_version;
  // sequence
  output->sequence = input->sequence;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // reset_counter
  output->reset_counter = input->reset_counter;
  // frame_id
  if (!rosidl_runtime_c__String__copy(
      &(input->frame_id), &(output->frame_id)))
  {
    return false;
  }
  // body_frame_id
  if (!rosidl_runtime_c__String__copy(
      &(input->body_frame_id), &(output->body_frame_id)))
  {
    return false;
  }
  // source_id
  if (!rosidl_runtime_c__String__copy(
      &(input->source_id), &(output->source_id)))
  {
    return false;
  }
  // angular_velocity_source
  if (!rosidl_runtime_c__String__copy(
      &(input->angular_velocity_source), &(output->angular_velocity_source)))
  {
    return false;
  }
  // initialized
  output->initialized = input->initialized;
  // tracking
  output->tracking = input->tracking;
  // calibration_valid
  output->calibration_valid = input->calibration_valid;
  // valid_fields
  output->valid_fields = input->valid_fields;
  // position
  for (size_t i = 0; i < 3; ++i) {
    output->position[i] = input->position[i];
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    output->velocity[i] = input->velocity[i];
  }
  // attitude
  for (size_t i = 0; i < 4; ++i) {
    output->attitude[i] = input->attitude[i];
  }
  // angular_velocity
  for (size_t i = 0; i < 3; ++i) {
    output->angular_velocity[i] = input->angular_velocity[i];
  }
  // pose_covariance
  for (size_t i = 0; i < 36; ++i) {
    output->pose_covariance[i] = input->pose_covariance[i];
  }
  // twist_covariance
  for (size_t i = 0; i < 36; ++i) {
    output->twist_covariance[i] = input->twist_covariance[i];
  }
  // quality
  output->quality = input->quality;
  return true;
}

jikl_fc01_system__msg__VisionState *
jikl_fc01_system__msg__VisionState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionState * msg = (jikl_fc01_system__msg__VisionState *)allocator.allocate(sizeof(jikl_fc01_system__msg__VisionState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jikl_fc01_system__msg__VisionState));
  bool success = jikl_fc01_system__msg__VisionState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jikl_fc01_system__msg__VisionState__destroy(jikl_fc01_system__msg__VisionState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jikl_fc01_system__msg__VisionState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jikl_fc01_system__msg__VisionState__Sequence__init(jikl_fc01_system__msg__VisionState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionState * data = NULL;

  if (size) {
    data = (jikl_fc01_system__msg__VisionState *)allocator.zero_allocate(size, sizeof(jikl_fc01_system__msg__VisionState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jikl_fc01_system__msg__VisionState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jikl_fc01_system__msg__VisionState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
jikl_fc01_system__msg__VisionState__Sequence__fini(jikl_fc01_system__msg__VisionState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      jikl_fc01_system__msg__VisionState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

jikl_fc01_system__msg__VisionState__Sequence *
jikl_fc01_system__msg__VisionState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionState__Sequence * array = (jikl_fc01_system__msg__VisionState__Sequence *)allocator.allocate(sizeof(jikl_fc01_system__msg__VisionState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jikl_fc01_system__msg__VisionState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jikl_fc01_system__msg__VisionState__Sequence__destroy(jikl_fc01_system__msg__VisionState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jikl_fc01_system__msg__VisionState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jikl_fc01_system__msg__VisionState__Sequence__are_equal(const jikl_fc01_system__msg__VisionState__Sequence * lhs, const jikl_fc01_system__msg__VisionState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jikl_fc01_system__msg__VisionState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jikl_fc01_system__msg__VisionState__Sequence__copy(
  const jikl_fc01_system__msg__VisionState__Sequence * input,
  jikl_fc01_system__msg__VisionState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jikl_fc01_system__msg__VisionState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jikl_fc01_system__msg__VisionState * data =
      (jikl_fc01_system__msg__VisionState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jikl_fc01_system__msg__VisionState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jikl_fc01_system__msg__VisionState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jikl_fc01_system__msg__VisionState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
