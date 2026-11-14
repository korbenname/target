# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jikl_fc01_system:msg/VisionHealth.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VisionHealth(type):
    """Metaclass of message 'VisionHealth'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('jikl_fc01_system')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'jikl_fc01_system.msg.VisionHealth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vision_health
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vision_health
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vision_health
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vision_health
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vision_health

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'SCHEMA_VERSION__DEFAULT': 1,
        }

    @property
    def SCHEMA_VERSION__DEFAULT(cls):
        """Return default value for message field 'schema_version'."""
        return 1


class VisionHealth(metaclass=Metaclass_VisionHealth):
    """Message class 'VisionHealth'."""

    __slots__ = [
        '_schema_version',
        '_stamp',
        '_sequence',
        '_source_id',
        '_frame_id',
        '_body_frame_id',
        '_reset_counter',
        '_reset_valid',
        '_initialized',
        '_tracking',
        '_calibration_valid',
        '_frame_alignment_valid',
        '_time_sync_valid',
        '_extrinsics_valid',
        '_metric_scale_valid',
        '_position_valid',
        '_velocity_valid',
        '_attitude_valid',
        '_angular_velocity_valid',
        '_angular_velocity_source',
        '_quality_valid',
        '_quality',
        '_extrinsics_id',
        '_alignment_id',
    ]

    _fields_and_field_types = {
        'schema_version': 'uint16',
        'stamp': 'builtin_interfaces/Time',
        'sequence': 'uint64',
        'source_id': 'string',
        'frame_id': 'string',
        'body_frame_id': 'string',
        'reset_counter': 'uint32',
        'reset_valid': 'boolean',
        'initialized': 'boolean',
        'tracking': 'boolean',
        'calibration_valid': 'boolean',
        'frame_alignment_valid': 'boolean',
        'time_sync_valid': 'boolean',
        'extrinsics_valid': 'boolean',
        'metric_scale_valid': 'boolean',
        'position_valid': 'boolean',
        'velocity_valid': 'boolean',
        'attitude_valid': 'boolean',
        'angular_velocity_valid': 'boolean',
        'angular_velocity_source': 'string',
        'quality_valid': 'boolean',
        'quality': 'double',
        'extrinsics_id': 'string',
        'alignment_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.schema_version = kwargs.get(
            'schema_version', VisionHealth.SCHEMA_VERSION__DEFAULT)
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.sequence = kwargs.get('sequence', int())
        self.source_id = kwargs.get('source_id', str())
        self.frame_id = kwargs.get('frame_id', str())
        self.body_frame_id = kwargs.get('body_frame_id', str())
        self.reset_counter = kwargs.get('reset_counter', int())
        self.reset_valid = kwargs.get('reset_valid', bool())
        self.initialized = kwargs.get('initialized', bool())
        self.tracking = kwargs.get('tracking', bool())
        self.calibration_valid = kwargs.get('calibration_valid', bool())
        self.frame_alignment_valid = kwargs.get('frame_alignment_valid', bool())
        self.time_sync_valid = kwargs.get('time_sync_valid', bool())
        self.extrinsics_valid = kwargs.get('extrinsics_valid', bool())
        self.metric_scale_valid = kwargs.get('metric_scale_valid', bool())
        self.position_valid = kwargs.get('position_valid', bool())
        self.velocity_valid = kwargs.get('velocity_valid', bool())
        self.attitude_valid = kwargs.get('attitude_valid', bool())
        self.angular_velocity_valid = kwargs.get('angular_velocity_valid', bool())
        self.angular_velocity_source = kwargs.get('angular_velocity_source', str())
        self.quality_valid = kwargs.get('quality_valid', bool())
        self.quality = kwargs.get('quality', float())
        self.extrinsics_id = kwargs.get('extrinsics_id', str())
        self.alignment_id = kwargs.get('alignment_id', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.schema_version != other.schema_version:
            return False
        if self.stamp != other.stamp:
            return False
        if self.sequence != other.sequence:
            return False
        if self.source_id != other.source_id:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.body_frame_id != other.body_frame_id:
            return False
        if self.reset_counter != other.reset_counter:
            return False
        if self.reset_valid != other.reset_valid:
            return False
        if self.initialized != other.initialized:
            return False
        if self.tracking != other.tracking:
            return False
        if self.calibration_valid != other.calibration_valid:
            return False
        if self.frame_alignment_valid != other.frame_alignment_valid:
            return False
        if self.time_sync_valid != other.time_sync_valid:
            return False
        if self.extrinsics_valid != other.extrinsics_valid:
            return False
        if self.metric_scale_valid != other.metric_scale_valid:
            return False
        if self.position_valid != other.position_valid:
            return False
        if self.velocity_valid != other.velocity_valid:
            return False
        if self.attitude_valid != other.attitude_valid:
            return False
        if self.angular_velocity_valid != other.angular_velocity_valid:
            return False
        if self.angular_velocity_source != other.angular_velocity_source:
            return False
        if self.quality_valid != other.quality_valid:
            return False
        if self.quality != other.quality:
            return False
        if self.extrinsics_id != other.extrinsics_id:
            return False
        if self.alignment_id != other.alignment_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def schema_version(self):
        """Message field 'schema_version'."""
        return self._schema_version

    @schema_version.setter
    def schema_version(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'schema_version' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'schema_version' field must be an unsigned integer in [0, 65535]"
        self._schema_version = value

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value

    @builtins.property
    def sequence(self):
        """Message field 'sequence'."""
        return self._sequence

    @sequence.setter
    def sequence(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sequence' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'sequence' field must be an unsigned integer in [0, 18446744073709551615]"
        self._sequence = value

    @builtins.property
    def source_id(self):
        """Message field 'source_id'."""
        return self._source_id

    @source_id.setter
    def source_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'source_id' field must be of type 'str'"
        self._source_id = value

    @builtins.property
    def frame_id(self):
        """Message field 'frame_id'."""
        return self._frame_id

    @frame_id.setter
    def frame_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'frame_id' field must be of type 'str'"
        self._frame_id = value

    @builtins.property
    def body_frame_id(self):
        """Message field 'body_frame_id'."""
        return self._body_frame_id

    @body_frame_id.setter
    def body_frame_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'body_frame_id' field must be of type 'str'"
        self._body_frame_id = value

    @builtins.property
    def reset_counter(self):
        """Message field 'reset_counter'."""
        return self._reset_counter

    @reset_counter.setter
    def reset_counter(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'reset_counter' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'reset_counter' field must be an unsigned integer in [0, 4294967295]"
        self._reset_counter = value

    @builtins.property
    def reset_valid(self):
        """Message field 'reset_valid'."""
        return self._reset_valid

    @reset_valid.setter
    def reset_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reset_valid' field must be of type 'bool'"
        self._reset_valid = value

    @builtins.property
    def initialized(self):
        """Message field 'initialized'."""
        return self._initialized

    @initialized.setter
    def initialized(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'initialized' field must be of type 'bool'"
        self._initialized = value

    @builtins.property
    def tracking(self):
        """Message field 'tracking'."""
        return self._tracking

    @tracking.setter
    def tracking(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'tracking' field must be of type 'bool'"
        self._tracking = value

    @builtins.property
    def calibration_valid(self):
        """Message field 'calibration_valid'."""
        return self._calibration_valid

    @calibration_valid.setter
    def calibration_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'calibration_valid' field must be of type 'bool'"
        self._calibration_valid = value

    @builtins.property
    def frame_alignment_valid(self):
        """Message field 'frame_alignment_valid'."""
        return self._frame_alignment_valid

    @frame_alignment_valid.setter
    def frame_alignment_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'frame_alignment_valid' field must be of type 'bool'"
        self._frame_alignment_valid = value

    @builtins.property
    def time_sync_valid(self):
        """Message field 'time_sync_valid'."""
        return self._time_sync_valid

    @time_sync_valid.setter
    def time_sync_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'time_sync_valid' field must be of type 'bool'"
        self._time_sync_valid = value

    @builtins.property
    def extrinsics_valid(self):
        """Message field 'extrinsics_valid'."""
        return self._extrinsics_valid

    @extrinsics_valid.setter
    def extrinsics_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'extrinsics_valid' field must be of type 'bool'"
        self._extrinsics_valid = value

    @builtins.property
    def metric_scale_valid(self):
        """Message field 'metric_scale_valid'."""
        return self._metric_scale_valid

    @metric_scale_valid.setter
    def metric_scale_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'metric_scale_valid' field must be of type 'bool'"
        self._metric_scale_valid = value

    @builtins.property
    def position_valid(self):
        """Message field 'position_valid'."""
        return self._position_valid

    @position_valid.setter
    def position_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'position_valid' field must be of type 'bool'"
        self._position_valid = value

    @builtins.property
    def velocity_valid(self):
        """Message field 'velocity_valid'."""
        return self._velocity_valid

    @velocity_valid.setter
    def velocity_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'velocity_valid' field must be of type 'bool'"
        self._velocity_valid = value

    @builtins.property
    def attitude_valid(self):
        """Message field 'attitude_valid'."""
        return self._attitude_valid

    @attitude_valid.setter
    def attitude_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'attitude_valid' field must be of type 'bool'"
        self._attitude_valid = value

    @builtins.property
    def angular_velocity_valid(self):
        """Message field 'angular_velocity_valid'."""
        return self._angular_velocity_valid

    @angular_velocity_valid.setter
    def angular_velocity_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'angular_velocity_valid' field must be of type 'bool'"
        self._angular_velocity_valid = value

    @builtins.property
    def angular_velocity_source(self):
        """Message field 'angular_velocity_source'."""
        return self._angular_velocity_source

    @angular_velocity_source.setter
    def angular_velocity_source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'angular_velocity_source' field must be of type 'str'"
        self._angular_velocity_source = value

    @builtins.property
    def quality_valid(self):
        """Message field 'quality_valid'."""
        return self._quality_valid

    @quality_valid.setter
    def quality_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'quality_valid' field must be of type 'bool'"
        self._quality_valid = value

    @builtins.property
    def quality(self):
        """Message field 'quality'."""
        return self._quality

    @quality.setter
    def quality(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'quality' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'quality' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._quality = value

    @builtins.property
    def extrinsics_id(self):
        """Message field 'extrinsics_id'."""
        return self._extrinsics_id

    @extrinsics_id.setter
    def extrinsics_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'extrinsics_id' field must be of type 'str'"
        self._extrinsics_id = value

    @builtins.property
    def alignment_id(self):
        """Message field 'alignment_id'."""
        return self._alignment_id

    @alignment_id.setter
    def alignment_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'alignment_id' field must be of type 'str'"
        self._alignment_id = value
