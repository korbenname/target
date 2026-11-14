# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jikl_fc01_system:msg/VisionState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'position'
# Member 'velocity'
# Member 'attitude'
# Member 'angular_velocity'
# Member 'pose_covariance'
# Member 'twist_covariance'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VisionState(type):
    """Metaclass of message 'VisionState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'POSITION': 1,
        'VELOCITY': 2,
        'ATTITUDE': 4,
        'ANGULAR_VELOCITY': 8,
        'POSE_COVARIANCE': 16,
        'TWIST_COVARIANCE': 32,
        'QUALITY': 64,
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
                'jikl_fc01_system.msg.VisionState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vision_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vision_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vision_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vision_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vision_state

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'POSITION': cls.__constants['POSITION'],
            'VELOCITY': cls.__constants['VELOCITY'],
            'ATTITUDE': cls.__constants['ATTITUDE'],
            'ANGULAR_VELOCITY': cls.__constants['ANGULAR_VELOCITY'],
            'POSE_COVARIANCE': cls.__constants['POSE_COVARIANCE'],
            'TWIST_COVARIANCE': cls.__constants['TWIST_COVARIANCE'],
            'QUALITY': cls.__constants['QUALITY'],
            'SCHEMA_VERSION__DEFAULT': 1,
        }

    @property
    def POSITION(self):
        """Message constant 'POSITION'."""
        return Metaclass_VisionState.__constants['POSITION']

    @property
    def VELOCITY(self):
        """Message constant 'VELOCITY'."""
        return Metaclass_VisionState.__constants['VELOCITY']

    @property
    def ATTITUDE(self):
        """Message constant 'ATTITUDE'."""
        return Metaclass_VisionState.__constants['ATTITUDE']

    @property
    def ANGULAR_VELOCITY(self):
        """Message constant 'ANGULAR_VELOCITY'."""
        return Metaclass_VisionState.__constants['ANGULAR_VELOCITY']

    @property
    def POSE_COVARIANCE(self):
        """Message constant 'POSE_COVARIANCE'."""
        return Metaclass_VisionState.__constants['POSE_COVARIANCE']

    @property
    def TWIST_COVARIANCE(self):
        """Message constant 'TWIST_COVARIANCE'."""
        return Metaclass_VisionState.__constants['TWIST_COVARIANCE']

    @property
    def QUALITY(self):
        """Message constant 'QUALITY'."""
        return Metaclass_VisionState.__constants['QUALITY']

    @property
    def SCHEMA_VERSION__DEFAULT(cls):
        """Return default value for message field 'schema_version'."""
        return 1


class VisionState(metaclass=Metaclass_VisionState):
    """
    Message class 'VisionState'.

    Constants:
      POSITION
      VELOCITY
      ATTITUDE
      ANGULAR_VELOCITY
      POSE_COVARIANCE
      TWIST_COVARIANCE
      QUALITY
    """

    __slots__ = [
        '_schema_version',
        '_sequence',
        '_stamp',
        '_reset_counter',
        '_frame_id',
        '_body_frame_id',
        '_source_id',
        '_angular_velocity_source',
        '_initialized',
        '_tracking',
        '_calibration_valid',
        '_valid_fields',
        '_position',
        '_velocity',
        '_attitude',
        '_angular_velocity',
        '_pose_covariance',
        '_twist_covariance',
        '_quality',
    ]

    _fields_and_field_types = {
        'schema_version': 'uint16',
        'sequence': 'uint64',
        'stamp': 'builtin_interfaces/Time',
        'reset_counter': 'uint32',
        'frame_id': 'string',
        'body_frame_id': 'string',
        'source_id': 'string',
        'angular_velocity_source': 'string',
        'initialized': 'boolean',
        'tracking': 'boolean',
        'calibration_valid': 'boolean',
        'valid_fields': 'uint16',
        'position': 'double[3]',
        'velocity': 'double[3]',
        'attitude': 'double[4]',
        'angular_velocity': 'double[3]',
        'pose_covariance': 'double[36]',
        'twist_covariance': 'double[36]',
        'quality': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 36),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 36),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.schema_version = kwargs.get(
            'schema_version', VisionState.SCHEMA_VERSION__DEFAULT)
        self.sequence = kwargs.get('sequence', int())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.reset_counter = kwargs.get('reset_counter', int())
        self.frame_id = kwargs.get('frame_id', str())
        self.body_frame_id = kwargs.get('body_frame_id', str())
        self.source_id = kwargs.get('source_id', str())
        self.angular_velocity_source = kwargs.get('angular_velocity_source', str())
        self.initialized = kwargs.get('initialized', bool())
        self.tracking = kwargs.get('tracking', bool())
        self.calibration_valid = kwargs.get('calibration_valid', bool())
        self.valid_fields = kwargs.get('valid_fields', int())
        if 'position' not in kwargs:
            self.position = numpy.zeros(3, dtype=numpy.float64)
        else:
            self.position = kwargs.get('position')
        if 'velocity' not in kwargs:
            self.velocity = numpy.zeros(3, dtype=numpy.float64)
        else:
            self.velocity = kwargs.get('velocity')
        if 'attitude' not in kwargs:
            self.attitude = numpy.zeros(4, dtype=numpy.float64)
        else:
            self.attitude = kwargs.get('attitude')
        if 'angular_velocity' not in kwargs:
            self.angular_velocity = numpy.zeros(3, dtype=numpy.float64)
        else:
            self.angular_velocity = kwargs.get('angular_velocity')
        if 'pose_covariance' not in kwargs:
            self.pose_covariance = numpy.zeros(36, dtype=numpy.float64)
        else:
            self.pose_covariance = kwargs.get('pose_covariance')
        if 'twist_covariance' not in kwargs:
            self.twist_covariance = numpy.zeros(36, dtype=numpy.float64)
        else:
            self.twist_covariance = kwargs.get('twist_covariance')
        self.quality = kwargs.get('quality', float())

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
        if self.sequence != other.sequence:
            return False
        if self.stamp != other.stamp:
            return False
        if self.reset_counter != other.reset_counter:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.body_frame_id != other.body_frame_id:
            return False
        if self.source_id != other.source_id:
            return False
        if self.angular_velocity_source != other.angular_velocity_source:
            return False
        if self.initialized != other.initialized:
            return False
        if self.tracking != other.tracking:
            return False
        if self.calibration_valid != other.calibration_valid:
            return False
        if self.valid_fields != other.valid_fields:
            return False
        if any(self.position != other.position):
            return False
        if any(self.velocity != other.velocity):
            return False
        if any(self.attitude != other.attitude):
            return False
        if any(self.angular_velocity != other.angular_velocity):
            return False
        if any(self.pose_covariance != other.pose_covariance):
            return False
        if any(self.twist_covariance != other.twist_covariance):
            return False
        if self.quality != other.quality:
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
    def valid_fields(self):
        """Message field 'valid_fields'."""
        return self._valid_fields

    @valid_fields.setter
    def valid_fields(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'valid_fields' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'valid_fields' field must be an unsigned integer in [0, 65535]"
        self._valid_fields = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'position' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 3, \
                "The 'position' numpy.ndarray() must have a size of 3"
            self._position = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'position' field must be a set or sequence with length 3 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._position = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def velocity(self):
        """Message field 'velocity'."""
        return self._velocity

    @velocity.setter
    def velocity(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'velocity' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 3, \
                "The 'velocity' numpy.ndarray() must have a size of 3"
            self._velocity = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'velocity' field must be a set or sequence with length 3 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._velocity = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def attitude(self):
        """Message field 'attitude'."""
        return self._attitude

    @attitude.setter
    def attitude(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'attitude' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 4, \
                "The 'attitude' numpy.ndarray() must have a size of 4"
            self._attitude = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'attitude' field must be a set or sequence with length 4 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._attitude = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def angular_velocity(self):
        """Message field 'angular_velocity'."""
        return self._angular_velocity

    @angular_velocity.setter
    def angular_velocity(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'angular_velocity' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 3, \
                "The 'angular_velocity' numpy.ndarray() must have a size of 3"
            self._angular_velocity = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'angular_velocity' field must be a set or sequence with length 3 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._angular_velocity = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def pose_covariance(self):
        """Message field 'pose_covariance'."""
        return self._pose_covariance

    @pose_covariance.setter
    def pose_covariance(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'pose_covariance' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 36, \
                "The 'pose_covariance' numpy.ndarray() must have a size of 36"
            self._pose_covariance = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 36 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'pose_covariance' field must be a set or sequence with length 36 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._pose_covariance = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def twist_covariance(self):
        """Message field 'twist_covariance'."""
        return self._twist_covariance

    @twist_covariance.setter
    def twist_covariance(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'twist_covariance' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 36, \
                "The 'twist_covariance' numpy.ndarray() must have a size of 36"
            self._twist_covariance = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 36 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'twist_covariance' field must be a set or sequence with length 36 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._twist_covariance = numpy.array(value, dtype=numpy.float64)

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
