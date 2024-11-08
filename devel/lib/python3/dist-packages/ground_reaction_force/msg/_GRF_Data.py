# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from ground_reaction_force/GRF_Data.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class GRF_Data(genpy.Message):
  _md5sum = "7f6bc012a85df06ce5797caa5e247628"
  _type = "ground_reaction_force/GRF_Data"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float32 midtop_mid
float32 all_force
float32 bot_Med
float32 bot_lat
bool stance_flg"""
  __slots__ = ['midtop_mid','all_force','bot_Med','bot_lat','stance_flg']
  _slot_types = ['float32','float32','float32','float32','bool']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       midtop_mid,all_force,bot_Med,bot_lat,stance_flg

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GRF_Data, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.midtop_mid is None:
        self.midtop_mid = 0.
      if self.all_force is None:
        self.all_force = 0.
      if self.bot_Med is None:
        self.bot_Med = 0.
      if self.bot_lat is None:
        self.bot_lat = 0.
      if self.stance_flg is None:
        self.stance_flg = False
    else:
      self.midtop_mid = 0.
      self.all_force = 0.
      self.bot_Med = 0.
      self.bot_lat = 0.
      self.stance_flg = False

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
      buff.write(_get_struct_4fB().pack(_x.midtop_mid, _x.all_force, _x.bot_Med, _x.bot_lat, _x.stance_flg))
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
      end += 17
      (_x.midtop_mid, _x.all_force, _x.bot_Med, _x.bot_lat, _x.stance_flg,) = _get_struct_4fB().unpack(str[start:end])
      self.stance_flg = bool(self.stance_flg)
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
      buff.write(_get_struct_4fB().pack(_x.midtop_mid, _x.all_force, _x.bot_Med, _x.bot_lat, _x.stance_flg))
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
      end += 17
      (_x.midtop_mid, _x.all_force, _x.bot_Med, _x.bot_lat, _x.stance_flg,) = _get_struct_4fB().unpack(str[start:end])
      self.stance_flg = bool(self.stance_flg)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_4fB = None
def _get_struct_4fB():
    global _struct_4fB
    if _struct_4fB is None:
        _struct_4fB = struct.Struct("<4fB")
    return _struct_4fB
