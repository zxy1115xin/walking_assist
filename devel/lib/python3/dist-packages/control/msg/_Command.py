# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from control/Command.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Command(genpy.Message):
  _md5sum = "a6a1adef66b901eb18da73880940852a"
  _type = "control/Command"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """int32 mode  #mode 1 力位控制 mode 2  速度模式 mode 3 位置模式
float32 force
float32 kp    #刚度 N/mm 或 PID的比例
float32 ki    
float32 kd   
int32 flag    #标志触地
float32 Tsta    #助力开始时刻
float32 Trise    #助力结束时刻
float32 Tfall    #助力开始时刻
float32 Fmax    #助力结束时刻
"""
  __slots__ = ['mode','force','kp','ki','kd','flag','Tsta','Trise','Tfall','Fmax']
  _slot_types = ['int32','float32','float32','float32','float32','int32','float32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       mode,force,kp,ki,kd,flag,Tsta,Trise,Tfall,Fmax

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Command, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.mode is None:
        self.mode = 0
      if self.force is None:
        self.force = 0.
      if self.kp is None:
        self.kp = 0.
      if self.ki is None:
        self.ki = 0.
      if self.kd is None:
        self.kd = 0.
      if self.flag is None:
        self.flag = 0
      if self.Tsta is None:
        self.Tsta = 0.
      if self.Trise is None:
        self.Trise = 0.
      if self.Tfall is None:
        self.Tfall = 0.
      if self.Fmax is None:
        self.Fmax = 0.
    else:
      self.mode = 0
      self.force = 0.
      self.kp = 0.
      self.ki = 0.
      self.kd = 0.
      self.flag = 0
      self.Tsta = 0.
      self.Trise = 0.
      self.Tfall = 0.
      self.Fmax = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_i4fi4f().pack(_x.mode, _x.force, _x.kp, _x.ki, _x.kd, _x.flag, _x.Tsta, _x.Trise, _x.Tfall, _x.Fmax))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.mode, _x.force, _x.kp, _x.ki, _x.kd, _x.flag, _x.Tsta, _x.Trise, _x.Tfall, _x.Fmax,) = _get_struct_i4fi4f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_i4fi4f().pack(_x.mode, _x.force, _x.kp, _x.ki, _x.kd, _x.flag, _x.Tsta, _x.Trise, _x.Tfall, _x.Fmax))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.mode, _x.force, _x.kp, _x.ki, _x.kd, _x.flag, _x.Tsta, _x.Trise, _x.Tfall, _x.Fmax,) = _get_struct_i4fi4f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_i4fi4f = None
def _get_struct_i4fi4f():
    global _struct_i4fi4f
    if _struct_i4fi4f is None:
        _struct_i4fi4f = struct.Struct("<i4fi4f")
    return _struct_i4fi4f
