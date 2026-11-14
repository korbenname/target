// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from jikl_fc01_system:msg/VisionState.idl
// generated code does not contain a copyright notice

#ifndef JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__FUNCTIONS_H_
#define JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "jikl_fc01_system/msg/rosidl_generator_c__visibility_control.h"

#include "jikl_fc01_system/msg/detail/vision_state__struct.h"

/// Initialize msg/VisionState message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * jikl_fc01_system__msg__VisionState
 * )) before or use
 * jikl_fc01_system__msg__VisionState__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__init(jikl_fc01_system__msg__VisionState * msg);

/// Finalize msg/VisionState message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
void
jikl_fc01_system__msg__VisionState__fini(jikl_fc01_system__msg__VisionState * msg);

/// Create msg/VisionState message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * jikl_fc01_system__msg__VisionState__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
jikl_fc01_system__msg__VisionState *
jikl_fc01_system__msg__VisionState__create();

/// Destroy msg/VisionState message.
/**
 * It calls
 * jikl_fc01_system__msg__VisionState__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
void
jikl_fc01_system__msg__VisionState__destroy(jikl_fc01_system__msg__VisionState * msg);

/// Check for msg/VisionState message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__are_equal(const jikl_fc01_system__msg__VisionState * lhs, const jikl_fc01_system__msg__VisionState * rhs);

/// Copy a msg/VisionState message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__copy(
  const jikl_fc01_system__msg__VisionState * input,
  jikl_fc01_system__msg__VisionState * output);

/// Initialize array of msg/VisionState messages.
/**
 * It allocates the memory for the number of elements and calls
 * jikl_fc01_system__msg__VisionState__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__Sequence__init(jikl_fc01_system__msg__VisionState__Sequence * array, size_t size);

/// Finalize array of msg/VisionState messages.
/**
 * It calls
 * jikl_fc01_system__msg__VisionState__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
void
jikl_fc01_system__msg__VisionState__Sequence__fini(jikl_fc01_system__msg__VisionState__Sequence * array);

/// Create array of msg/VisionState messages.
/**
 * It allocates the memory for the array and calls
 * jikl_fc01_system__msg__VisionState__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
jikl_fc01_system__msg__VisionState__Sequence *
jikl_fc01_system__msg__VisionState__Sequence__create(size_t size);

/// Destroy array of msg/VisionState messages.
/**
 * It calls
 * jikl_fc01_system__msg__VisionState__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
void
jikl_fc01_system__msg__VisionState__Sequence__destroy(jikl_fc01_system__msg__VisionState__Sequence * array);

/// Check for msg/VisionState message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__Sequence__are_equal(const jikl_fc01_system__msg__VisionState__Sequence * lhs, const jikl_fc01_system__msg__VisionState__Sequence * rhs);

/// Copy an array of msg/VisionState messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jikl_fc01_system
bool
jikl_fc01_system__msg__VisionState__Sequence__copy(
  const jikl_fc01_system__msg__VisionState__Sequence * input,
  jikl_fc01_system__msg__VisionState__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // JIKL_FC01_SYSTEM__MSG__DETAIL__VISION_STATE__FUNCTIONS_H_
