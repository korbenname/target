// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from jikl_fc01_system:msg/VisionHealth.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "jikl_fc01_system/msg/detail/vision_health__struct.h"
#include "jikl_fc01_system/msg/detail/vision_health__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool jikl_fc01_system__msg__vision_health__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("jikl_fc01_system.msg._vision_health.VisionHealth", full_classname_dest, 48) == 0);
  }
  jikl_fc01_system__msg__VisionHealth * ros_message = _ros_message;
  {  // schema_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "schema_version");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->schema_version = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // stamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "stamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->stamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // sequence
    PyObject * field = PyObject_GetAttrString(_pymsg, "sequence");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sequence = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // source_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "source_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->source_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // frame_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->frame_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // body_frame_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "body_frame_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->body_frame_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // reset_counter
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_counter");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->reset_counter = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // reset_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->reset_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // initialized
    PyObject * field = PyObject_GetAttrString(_pymsg, "initialized");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->initialized = (Py_True == field);
    Py_DECREF(field);
  }
  {  // tracking
    PyObject * field = PyObject_GetAttrString(_pymsg, "tracking");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->tracking = (Py_True == field);
    Py_DECREF(field);
  }
  {  // calibration_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "calibration_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->calibration_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // frame_alignment_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_alignment_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->frame_alignment_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // time_sync_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "time_sync_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->time_sync_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // extrinsics_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "extrinsics_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->extrinsics_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // metric_scale_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "metric_scale_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->metric_scale_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // position_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "position_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->position_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // velocity_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "velocity_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->velocity_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // attitude_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "attitude_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->attitude_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // angular_velocity_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "angular_velocity_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->angular_velocity_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // angular_velocity_source
    PyObject * field = PyObject_GetAttrString(_pymsg, "angular_velocity_source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->angular_velocity_source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // quality_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "quality_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->quality_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // quality
    PyObject * field = PyObject_GetAttrString(_pymsg, "quality");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->quality = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // extrinsics_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "extrinsics_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->extrinsics_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // alignment_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "alignment_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->alignment_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * jikl_fc01_system__msg__vision_health__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of VisionHealth */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("jikl_fc01_system.msg._vision_health");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "VisionHealth");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  jikl_fc01_system__msg__VisionHealth * ros_message = (jikl_fc01_system__msg__VisionHealth *)raw_ros_message;
  {  // schema_version
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->schema_version);
    {
      int rc = PyObject_SetAttrString(_pymessage, "schema_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->stamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "stamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sequence
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->sequence);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sequence", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // source_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->source_id.data,
      strlen(ros_message->source_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "source_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->frame_id.data,
      strlen(ros_message->frame_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // body_frame_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->body_frame_id.data,
      strlen(ros_message->body_frame_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "body_frame_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_counter
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->reset_counter);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_counter", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->reset_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // initialized
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->initialized ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "initialized", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tracking
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->tracking ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "tracking", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calibration_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->calibration_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calibration_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_alignment_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->frame_alignment_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_alignment_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // time_sync_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->time_sync_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "time_sync_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // extrinsics_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->extrinsics_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "extrinsics_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // metric_scale_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->metric_scale_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "metric_scale_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // position_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->position_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "position_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velocity_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->velocity_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "velocity_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // attitude_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->attitude_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "attitude_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // angular_velocity_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->angular_velocity_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "angular_velocity_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // angular_velocity_source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->angular_velocity_source.data,
      strlen(ros_message->angular_velocity_source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "angular_velocity_source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // quality_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->quality_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "quality_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // quality
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->quality);
    {
      int rc = PyObject_SetAttrString(_pymessage, "quality", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // extrinsics_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->extrinsics_id.data,
      strlen(ros_message->extrinsics_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "extrinsics_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // alignment_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->alignment_id.data,
      strlen(ros_message->alignment_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "alignment_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
