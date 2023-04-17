# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from irobot_fcpp_simul/ComputeDefectsDecompActionResult.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import actionlib_msgs.msg
import genpy
import geometry_msgs.msg
import irobot_fcpp_simul.msg
import std_msgs.msg

class ComputeDefectsDecompActionResult(genpy.Message):
  _md5sum = "3691452370d6fc7b8f06e08f7239cd34"
  _type = "irobot_fcpp_simul/ComputeDefectsDecompActionResult"
  _has_header = True  # flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
ComputeDefectsDecompResult result

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: actionlib_msgs/GoalStatus
GoalID goal_id
uint8 status
uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server

#Allow for the user to associate a string with GoalStatus for debugging
string text


================================================================================
MSG: actionlib_msgs/GoalID
# The stamp should store the time at which this goal was requested.
# It is used by an action server when it tries to preempt all
# goals that were requested before a certain time
time stamp

# The id provides a way to associate feedback and
# result message with specific goal requests. The id
# specified must be unique.
string id


================================================================================
MSG: irobot_fcpp_simul/ComputeDefectsDecompResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define the result
defecto defecto

================================================================================
MSG: irobot_fcpp_simul/defecto
geometry_msgs/Polygon ros_poly
defecto_zona[] defecto_divpor_zonas

bool reparado

================================================================================
MSG: geometry_msgs/Polygon
#A specification of a polygon where the first and last points are assumed to be connected
Point32[] points

================================================================================
MSG: geometry_msgs/Point32
# This contains the position of a point in free space(with 32 bits of precision).
# It is recommeded to use Point wherever possible instead of Point32.  
# 
# This recommendation is to promote interoperability.  
#
# This message is designed to take up less space when sending
# lots of points at once, as in the case of a PointCloud.  

float32 x
float32 y
float32 z
================================================================================
MSG: irobot_fcpp_simul/defecto_zona
geometry_msgs/Polygon ros_poly
defecto_simple[] trap_vec

int32 direccion_rep
bool reparado
int32 zona

================================================================================
MSG: irobot_fcpp_simul/defecto_simple
geometry_msgs/Polygon ros_poly
int32 direccion_rep
bool reparado
"""
  __slots__ = ['header','status','result']
  _slot_types = ['std_msgs/Header','actionlib_msgs/GoalStatus','irobot_fcpp_simul/ComputeDefectsDecompResult']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,status,result

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ComputeDefectsDecompActionResult, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.status is None:
        self.status = actionlib_msgs.msg.GoalStatus()
      if self.result is None:
        self.result = irobot_fcpp_simul.msg.ComputeDefectsDecompResult()
    else:
      self.header = std_msgs.msg.Header()
      self.status = actionlib_msgs.msg.GoalStatus()
      self.result = irobot_fcpp_simul.msg.ComputeDefectsDecompResult()

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
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.status.goal_id.stamp.secs, _x.status.goal_id.stamp.nsecs))
      _x = self.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self.status.status
      buff.write(_get_struct_B().pack(_x))
      _x = self.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      length = len(self.result.defecto.ros_poly.points)
      buff.write(_struct_I.pack(length))
      for val1 in self.result.defecto.ros_poly.points:
        _x = val1
        buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
      length = len(self.result.defecto.defecto_divpor_zonas)
      buff.write(_struct_I.pack(length))
      for val1 in self.result.defecto.defecto_divpor_zonas:
        _v1 = val1.ros_poly
        length = len(_v1.points)
        buff.write(_struct_I.pack(length))
        for val3 in _v1.points:
          _x = val3
          buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
        length = len(val1.trap_vec)
        buff.write(_struct_I.pack(length))
        for val2 in val1.trap_vec:
          _v2 = val2.ros_poly
          length = len(_v2.points)
          buff.write(_struct_I.pack(length))
          for val4 in _v2.points:
            _x = val4
            buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
          _x = val2
          buff.write(_get_struct_iB().pack(_x.direccion_rep, _x.reparado))
        _x = val1
        buff.write(_get_struct_iBi().pack(_x.direccion_rep, _x.reparado, _x.zona))
      _x = self.result.defecto.reparado
      buff.write(_get_struct_B().pack(_x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.status is None:
        self.status = actionlib_msgs.msg.GoalStatus()
      if self.result is None:
        self.result = irobot_fcpp_simul.msg.ComputeDefectsDecompResult()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.status.goal_id.stamp.secs, _x.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.status.goal_id.id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.status.text = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.status.text = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.result.defecto.ros_poly.points = []
      for i in range(0, length):
        val1 = geometry_msgs.msg.Point32()
        _x = val1
        start = end
        end += 12
        (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
        self.result.defecto.ros_poly.points.append(val1)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.result.defecto.defecto_divpor_zonas = []
      for i in range(0, length):
        val1 = irobot_fcpp_simul.msg.defecto_zona()
        _v3 = val1.ros_poly
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        _v3.points = []
        for i in range(0, length):
          val3 = geometry_msgs.msg.Point32()
          _x = val3
          start = end
          end += 12
          (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
          _v3.points.append(val3)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.trap_vec = []
        for i in range(0, length):
          val2 = irobot_fcpp_simul.msg.defecto_simple()
          _v4 = val2.ros_poly
          start = end
          end += 4
          (length,) = _struct_I.unpack(str[start:end])
          _v4.points = []
          for i in range(0, length):
            val4 = geometry_msgs.msg.Point32()
            _x = val4
            start = end
            end += 12
            (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
            _v4.points.append(val4)
          _x = val2
          start = end
          end += 5
          (_x.direccion_rep, _x.reparado,) = _get_struct_iB().unpack(str[start:end])
          val2.reparado = bool(val2.reparado)
          val1.trap_vec.append(val2)
        _x = val1
        start = end
        end += 9
        (_x.direccion_rep, _x.reparado, _x.zona,) = _get_struct_iBi().unpack(str[start:end])
        val1.reparado = bool(val1.reparado)
        self.result.defecto.defecto_divpor_zonas.append(val1)
      start = end
      end += 1
      (self.result.defecto.reparado,) = _get_struct_B().unpack(str[start:end])
      self.result.defecto.reparado = bool(self.result.defecto.reparado)
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
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.status.goal_id.stamp.secs, _x.status.goal_id.stamp.nsecs))
      _x = self.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self.status.status
      buff.write(_get_struct_B().pack(_x))
      _x = self.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      length = len(self.result.defecto.ros_poly.points)
      buff.write(_struct_I.pack(length))
      for val1 in self.result.defecto.ros_poly.points:
        _x = val1
        buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
      length = len(self.result.defecto.defecto_divpor_zonas)
      buff.write(_struct_I.pack(length))
      for val1 in self.result.defecto.defecto_divpor_zonas:
        _v5 = val1.ros_poly
        length = len(_v5.points)
        buff.write(_struct_I.pack(length))
        for val3 in _v5.points:
          _x = val3
          buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
        length = len(val1.trap_vec)
        buff.write(_struct_I.pack(length))
        for val2 in val1.trap_vec:
          _v6 = val2.ros_poly
          length = len(_v6.points)
          buff.write(_struct_I.pack(length))
          for val4 in _v6.points:
            _x = val4
            buff.write(_get_struct_3f().pack(_x.x, _x.y, _x.z))
          _x = val2
          buff.write(_get_struct_iB().pack(_x.direccion_rep, _x.reparado))
        _x = val1
        buff.write(_get_struct_iBi().pack(_x.direccion_rep, _x.reparado, _x.zona))
      _x = self.result.defecto.reparado
      buff.write(_get_struct_B().pack(_x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.status is None:
        self.status = actionlib_msgs.msg.GoalStatus()
      if self.result is None:
        self.result = irobot_fcpp_simul.msg.ComputeDefectsDecompResult()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.status.goal_id.stamp.secs, _x.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.status.goal_id.id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.status.text = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.status.text = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.result.defecto.ros_poly.points = []
      for i in range(0, length):
        val1 = geometry_msgs.msg.Point32()
        _x = val1
        start = end
        end += 12
        (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
        self.result.defecto.ros_poly.points.append(val1)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.result.defecto.defecto_divpor_zonas = []
      for i in range(0, length):
        val1 = irobot_fcpp_simul.msg.defecto_zona()
        _v7 = val1.ros_poly
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        _v7.points = []
        for i in range(0, length):
          val3 = geometry_msgs.msg.Point32()
          _x = val3
          start = end
          end += 12
          (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
          _v7.points.append(val3)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.trap_vec = []
        for i in range(0, length):
          val2 = irobot_fcpp_simul.msg.defecto_simple()
          _v8 = val2.ros_poly
          start = end
          end += 4
          (length,) = _struct_I.unpack(str[start:end])
          _v8.points = []
          for i in range(0, length):
            val4 = geometry_msgs.msg.Point32()
            _x = val4
            start = end
            end += 12
            (_x.x, _x.y, _x.z,) = _get_struct_3f().unpack(str[start:end])
            _v8.points.append(val4)
          _x = val2
          start = end
          end += 5
          (_x.direccion_rep, _x.reparado,) = _get_struct_iB().unpack(str[start:end])
          val2.reparado = bool(val2.reparado)
          val1.trap_vec.append(val2)
        _x = val1
        start = end
        end += 9
        (_x.direccion_rep, _x.reparado, _x.zona,) = _get_struct_iBi().unpack(str[start:end])
        val1.reparado = bool(val1.reparado)
        self.result.defecto.defecto_divpor_zonas.append(val1)
      start = end
      end += 1
      (self.result.defecto.reparado,) = _get_struct_B().unpack(str[start:end])
      self.result.defecto.reparado = bool(self.result.defecto.reparado)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2I = None
def _get_struct_2I():
    global _struct_2I
    if _struct_2I is None:
        _struct_2I = struct.Struct("<2I")
    return _struct_2I
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_3f = None
def _get_struct_3f():
    global _struct_3f
    if _struct_3f is None:
        _struct_3f = struct.Struct("<3f")
    return _struct_3f
_struct_B = None
def _get_struct_B():
    global _struct_B
    if _struct_B is None:
        _struct_B = struct.Struct("<B")
    return _struct_B
_struct_iB = None
def _get_struct_iB():
    global _struct_iB
    if _struct_iB is None:
        _struct_iB = struct.Struct("<iB")
    return _struct_iB
_struct_iBi = None
def _get_struct_iBi():
    global _struct_iBi
    if _struct_iBi is None:
        _struct_iBi = struct.Struct("<iBi")
    return _struct_iBi
