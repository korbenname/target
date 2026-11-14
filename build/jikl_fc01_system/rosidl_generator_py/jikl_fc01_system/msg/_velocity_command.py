# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jikl_fc01_system:msg/VelocityCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VelocityCommand(type):
    """Metaclass of message 'VelocityCommand'."""

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
                'jikl_fc01_system.msg.VelocityCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__velocity_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__velocity_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__velocity_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__velocity_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__velocity_command

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


class VelocityCommand(metaclass=Metaclass_VelocityCommand):
    """Message class 'VelocityCommand'."""

    __slots__ = [
        '_schema_version',
        '_sequence',
        '_stamp',
        '_reset_counter',
        '_source_id',
        '_frame_id',
        '_valid',
        '_vx',
        '_vy',
        '_vz',
        '_wz',
    ]

    _fields_and_field_types = {
        'schema_version': 'uint16',
        'sequence': 'uint64',
        'stamp': 'builtin_interfaces/Time',
        'reset_counter': 'uint32',
        'source_id': 'string',
        'frame_id': 'string',
        'valid': 'boolean',
        'vx': 'double',
        'vy': 'double',
        'vz': 'double',
        'wz': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.schema_version = kwargs.get(
            'schema_version', VelocityCommand.SCHEMA_VERSION__DEFAULT)
        self.sequence = kwargs.get('sequence', int())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.reset_counter = kwargs.get('reset_counter', int())
        self.source_id = kwargs.get('source_id', str())
        self.frame_id = kwargs.get('frame_id', str())
        self.valid = kwargs.get('valid', bool())
        self.vx = kwargs.get('vx', float())
        self.vy = kwargs.get('vy', float())
        self.vz = kwargs.get('vz', float())
        self.wz = kwargs.get('wz', float())

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
        if self.source_id != other.source_id:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.valid != other.valid:
            return False
        if self.vx != other.vx:
            return False
        if self.vy != other.vy:
            return False
        if self.vz != other.vz:
            return False
        if self.wz != other.wz:
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
    def valid(self):
        """Message field 'valid'."""
        return self._valid

    @valid.setter
    def valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'valid' field must be of type 'bool'"
        self._valid = value

    @builtins.property
    def vx(self):
        """Message field 'vx'."""
        return self._vx

    @vx.setter
    def vx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vx = value

    @builtins.property
    def vy(self):
        """Message field 'vy'."""
        return self._vy

    @vy.setter
    def vy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vy = value

    @builtins.property
    def vz(self):
        """Message field 'vz'."""
        return self._vz

    @vz.setter
    def vz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vz = value

    @builtins.property
    def wz(self):
        """Message field 'wz'."""
        return self._wz

    @wz.setter
    def wz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'wz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'wz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._wz = value
