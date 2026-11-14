// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jikl_fc01_system:msg/VelocityCommand.idl
// generated code does not contain a copyright notice
#include "jikl_fc01_system/msg/detail/velocity_command__functions.h"

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
#include "rosidl_runtime_c/string_functions.h"

bool
jikl_fc01_system__msg__VelocityCommand__init(jikl_fc01_system__msg__VelocityCommand * msg)
{
  if (!msg) {
    return false;
  }
  // schema_version
  msg->schema_version = 1;
  // sequence
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    jikl_fc01_system__msg__VelocityCommand__fini(msg);
    return false;
  }
  // reset_counter
  // source_id
  if (!rosidl_runtime_c__String__init(&msg->source_id)) {
    jikl_fc01_system__msg__VelocityCommand__fini(msg);
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__init(&msg->frame_id)) {
    jikl_fc01_system__msg__VelocityCommand__fini(msg);
    return false;
  }
  // valid
  // vx
  // vy
  // vz
  // wz
  return true;
}

void
jikl_fc01_system__msg__VelocityCommand__fini(jikl_fc01_system__msg__VelocityCommand * msg)
{
  if (!msg) {
    return;
  }
  // schema_version
  // sequence
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // reset_counter
  // source_id
  rosidl_runtime_c__String__fini(&msg->source_id);
  // frame_id
  rosidl_runtime_c__String__fini(&msg->frame_id);
  // valid
  // vx
  // vy
  // vz
  // wz
}

bool
jikl_fc01_system__msg__VelocityCommand__are_equal(const jikl_fc01_system__msg__VelocityCommand * lhs, const jikl_fc01_system__msg__VelocityCommand * rhs)
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
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // vx
  if (lhs->vx != rhs->vx) {
    return false;
  }
  // vy
  if (lhs->vy != rhs->vy) {
    return false;
  }
  // vz
  if (lhs->vz != rhs->vz) {
    return false;
  }
  // wz
  if (lhs->wz != rhs->wz) {
    return false;
  }
  return true;
}

bool
jikl_fc01_system__msg__VelocityCommand__copy(
  const jikl_fc01_system__msg__VelocityCommand * input,
  jikl_fc01_system__msg__VelocityCommand * output)
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
  // valid
  output->valid = input->valid;
  // vx
  output->vx = input->vx;
  // vy
  output->vy = input->vy;
  // vz
  output->vz = input->vz;
  // wz
  output->wz = input->wz;
  return true;
}

jikl_fc01_system__msg__VelocityCommand *
jikl_fc01_system__msg__VelocityCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VelocityCommand * msg = (jikl_fc01_system__msg__VelocityCommand *)allocator.allocate(sizeof(jikl_fc01_system__msg__VelocityCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jikl_fc01_system__msg__VelocityCommand));
  bool success = jikl_fc01_system__msg__VelocityCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jikl_fc01_system__msg__VelocityCommand__destroy(jikl_fc01_system__msg__VelocityCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jikl_fc01_system__msg__VelocityCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jikl_fc01_system__msg__VelocityCommand__Sequence__init(jikl_fc01_system__msg__VelocityCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VelocityCommand * data = NULL;

  if (size) {
    data = (jikl_fc01_system__msg__VelocityCommand *)allocator.zero_allocate(size, sizeof(jikl_fc01_system__msg__VelocityCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jikl_fc01_system__msg__VelocityCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jikl_fc01_system__msg__VelocityCommand__fini(&data[i - 1]);
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
jikl_fc01_system__msg__VelocityCommand__Sequence__fini(jikl_fc01_system__msg__VelocityCommand__Sequence * array)
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
      jikl_fc01_system__msg__VelocityCommand__fini(&array->data[i]);
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

jikl_fc01_system__msg__VelocityCommand__Sequence *
jikl_fc01_system__msg__VelocityCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jikl_fc01_system__msg__VelocityCommand__Sequence * array = (jikl_fc01_system__msg__VelocityCommand__Sequence *)allocator.allocate(sizeof(jikl_fc01_system__msg__VelocityCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jikl_fc01_system__msg__VelocityCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jikl_fc01_system__msg__VelocityCommand__Sequence__destroy(jikl_fc01_system__msg__VelocityCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jikl_fc01_system__msg__VelocityCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jikl_fc01_system__msg__VelocityCommand__Sequence__are_equal(const jikl_fc01_system__msg__VelocityCommand__Sequence * lhs, const jikl_fc01_system__msg__VelocityCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jikl_fc01_system__msg__VelocityCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jikl_fc01_system__msg__VelocityCommand__Sequence__copy(
  const jikl_fc01_system__msg__VelocityCommand__Sequence * input,
  jikl_fc01_system__msg__VelocityCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jikl_fc01_system__msg__VelocityCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jikl_fc01_system__msg__VelocityCommand * data =
      (jikl_fc01_system__msg__VelocityCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jikl_fc01_system__msg__VelocityCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jikl_fc01_system__msg__VelocityCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jikl_fc01_system__msg__VelocityCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
