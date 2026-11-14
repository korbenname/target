// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice
#include "jikl_fc01_system/msg/detail/vision_health__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `source_id`
// Member `frame_id`
// Member `body_frame_id`
// Member `angular_velocity_source`
// Member `extrinsics_id`
// Member `alignment_id`
#include "rosidl_runtime_c/string_functions.h"

bool
jikl_fc01_system__msg__VisionHealth__init(jikl_fc01_system__msg__VisionHealth * msg)
{
  if (!msg) {
    return false;
  }
  // schema_version
  msg->schema_version = 1;
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // sequence
  // source_id
  if (!rosidl_runtime_c__String__init(&msg->source_id)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__init(&msg->frame_id)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // body_frame_id
  if (!rosidl_runtime_c__String__init(&msg->body_frame_id)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // reset_counter
  // reset_valid
  // initialized
  // tracking
  // calibration_valid
  // frame_alignment_valid
  // time_sync_valid
  // extrinsics_valid
  // metric_scale_valid
  // position_valid
  // velocity_valid
  // attitude_valid
  // angular_velocity_valid
  // angular_velocity_source
  if (!rosidl_runtime_c__String__init(&msg->angular_velocity_source)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // quality_valid
  // quality
  // extrinsics_id
  if (!rosidl_runtime_c__String__init(&msg->extrinsics_id)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  // alignment_id
  if (!rosidl_runtime_c__String__init(&msg->alignment_id)) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
    return false;
  }
  return true;
}

void
jikl_fc01_system__msg__VisionHealth__fini(jikl_fc01_system__msg__VisionHealth * msg)
{
  if (!msg) {
    return;
  }
  // schema_version
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // sequence
  // source_id
  rosidl_runtime_c__String__fini(&msg->source_id);
  // frame_id
  rosidl_runtime_c__String__fini(&msg->frame_id);
  // body_frame_id
  rosidl_runtime_c__String__fini(&msg->body_frame_id);
  // reset_counter
  // reset_valid
  // initialized
  // tracking
  // calibration_valid
  // frame_alignment_valid
  // time_sync_valid
  // extrinsics_valid
  // metric_scale_valid
  // position_valid
  // velocity_valid
  // attitude_valid
  // angular_velocity_valid
  // angular_velocity_source
  rosidl_runtime_c__String__fini(&msg->angular_velocity_source);
  // quality_valid
  // quality
  // extrinsics_id
  rosidl_runtime_c__String__fini(&msg->extrinsics_id);
  // alignment_id
  rosidl_runtime_c__String__fini(&msg->alignment_id);
}

bool
jikl_fc01_system__msg__VisionHealth__are_equal(const jikl_fc01_system__msg__VisionHealth * lhs, const jikl_fc01_system__msg__VisionHealth * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // schema_version
  if (lhs->schema_version != rhs->schema_version) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // sequence
  if (lhs->sequence != rhs->sequence) {
    return false;
  }
  // source_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source_id), &(rhs->source_id)))
  {
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
  // reset_counter
  if (lhs->reset_counter != rhs->reset_counter) {
    return false;
  }
  // reset_valid
  if (lhs->reset_valid != rhs->reset_valid) {
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
  // frame_alignment_valid
  if (lhs->frame_alignment_valid != rhs->frame_alignment_valid) {
    return false;
  }
  // time_sync_valid
  if (lhs->time_sync_valid != rhs->time_sync_valid) {
    return false;
  }
  // extrinsics_valid
  if (lhs->extrinsics_valid != rhs->extrinsics_valid) {
    return false;
  }
  // metric_scale_valid
  if (lhs->metric_scale_valid != rhs->metric_scale_valid) {
    return false;
  }
  // position_valid
  if (lhs->position_valid != rhs->position_valid) {
    return false;
  }
  // velocity_valid
  if (lhs->velocity_valid != rhs->velocity_valid) {
    return false;
  }
  // attitude_valid
  if (lhs->attitude_valid != rhs->attitude_valid) {
    return false;
  }
  // angular_velocity_valid
  if (lhs->angular_velocity_valid != rhs->angular_velocity_valid) {
    return false;
  }
  // angular_velocity_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->angular_velocity_source), &(rhs->angular_velocity_source)))
  {
    return false;
  }
  // quality_valid
  if (lhs->quality_valid != rhs->quality_valid) {
    return false;
  }
  // quality
  if (lhs->quality != rhs->quality) {
    return false;
  }
  // extrinsics_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->extrinsics_id), &(rhs->extrinsics_id)))
  {
    return false;
  }
  // alignment_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->alignment_id), &(rhs->alignment_id)))
  {
    return false;
  }
  return true;
}

bool
jikl_fc01_system__msg__VisionHealth__copy(
  const jikl_fc01_system__msg__VisionHealth * input,
  jikl_fc01_system__msg__VisionHealth * output)
{
  if (!input || !output) {
    return false;
  }
  // schema_version
  output->schema_version = input->schema_version;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // sequence
  output->sequence = input->sequence;
  // source_id
  if (!rosidl_runtime_c__String__copy(
      &(input->source_id), &(output->source_id)))
  {
    return false;
  }
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
  // reset_counter
  output->reset_counter = input->reset_counter;
  // reset_valid
  output->reset_valid = input->reset_valid;
  // initialized
  output->initialized = input->initialized;
  // tracking
  output->tracking = input->tracking;
  // calibration_valid
  output->calibration_valid = input->calibration_valid;
  // frame_alignment_valid
  output->frame_alignment_valid = input->frame_alignment_valid;
  // time_sync_valid
  output->time_sync_valid = input->time_sync_valid;
  // extrinsics_valid
  output->extrinsics_valid = input->extrinsics_valid;
  // metric_scale_valid
  output->metric_scale_valid = input->metric_scale_valid;
  // position_valid
  output->position_valid = input->position_valid;
  // velocity_valid
  output->velocity_valid = input->velocity_valid;
  // attitude_valid
  output->attitude_valid = input->attitude_valid;
  // angular_velocity_valid
  output->angular_velocity_valid = input->angular_velocity_valid;
  // angular_velocity_source
  if (!rosidl_runtime_c__String__copy(
      &(input->angular_velocity_source), &(output->angular_velocity_source)))
  {
    return false;
  }
  // quality_valid
  output->quality_valid = input->quality_valid;
  // quality
  output->quality = input->quality;
  // extrinsics_id
  if (!rosidl_runtime_c__String__copy(
      &(input->extrinsics_id), &(output->extrinsics_id)))
  {
    return false;
  }
  // alignment_id
  if (!rosidl_runtime_c__String__copy(
      &(input->alignment_id), &(output->alignment_id)))
  {
    return false;
  }
  return true;
}

jikl_fc01_system__msg__VisionHealth *
jikl_fc01_system__msg__VisionHealth__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionHealth * msg = (jikl_fc01_system__msg__VisionHealth *)allocator.allocate(sizeof(jikl_fc01_system__msg__VisionHealth), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jikl_fc01_system__msg__VisionHealth));
  bool success = jikl_fc01_system__msg__VisionHealth__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jikl_fc01_system__msg__VisionHealth__destroy(jikl_fc01_system__msg__VisionHealth * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jikl_fc01_system__msg__VisionHealth__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jikl_fc01_system__msg__VisionHealth__Sequence__init(jikl_fc01_system__msg__VisionHealth__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionHealth * data = NULL;

  if (size) {
    data = (jikl_fc01_system__msg__VisionHealth *)allocator.zero_allocate(size, sizeof(jikl_fc01_system__msg__VisionHealth), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jikl_fc01_system__msg__VisionHealth__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jikl_fc01_system__msg__VisionHealth__fini(&data[i - 1]);
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
jikl_fc01_system__msg__VisionHealth__Sequence__fini(jikl_fc01_system__msg__VisionHealth__Sequence * array)
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
      jikl_fc01_system__msg__VisionHealth__fini(&array->data[i]);
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

jikl_fc01_system__msg__VisionHealth__Sequence *
jikl_fc01_system__msg__VisionHealth__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VisionHealth__Sequence * array = (jikl_fc01_system__msg__VisionHealth__Sequence *)allocator.allocate(sizeof(jikl_fc01_system__msg__VisionHealth__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jikl_fc01_system__msg__VisionHealth__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jikl_fc01_system__msg__VisionHealth__Sequence__destroy(jikl_fc01_system__msg__VisionHealth__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jikl_fc01_system__msg__VisionHealth__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jikl_fc01_system__msg__VisionHealth__Sequence__are_equal(const jikl_fc01_system__msg__VisionHealth__Sequence * lhs, const jikl_fc01_system__msg__VisionHealth__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jikl_fc01_system__msg__VisionHealth__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jikl_fc01_system__msg__VisionHealth__Sequence__copy(
  const jikl_fc01_system__msg__VisionHealth__Sequence * input,
  jikl_fc01_system__msg__VisionHealth__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jikl_fc01_system__msg__VisionHealth);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jikl_fc01_system__msg__VisionHealth * data =
      (jikl_fc01_system__msg__VisionHealth *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jikl_fc01_system__msg__VisionHealth__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jikl_fc01_system__msg__VisionHealth__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jikl_fc01_system__msg__VisionHealth__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
