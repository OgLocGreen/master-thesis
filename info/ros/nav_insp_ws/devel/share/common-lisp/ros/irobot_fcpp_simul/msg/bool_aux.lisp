; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude bool_aux.msg.html

(cl:defclass <bool_aux> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (data
    :reader data
    :initarg :data
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass bool_aux (<bool_aux>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <bool_aux>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'bool_aux)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<bool_aux> is deprecated: use irobot_fcpp_simul-msg:bool_aux instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <bool_aux>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:header-val is deprecated.  Use irobot_fcpp_simul-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <bool_aux>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:data-val is deprecated.  Use irobot_fcpp_simul-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <bool_aux>) ostream)
  "Serializes a message object of type '<bool_aux>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'data) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <bool_aux>) istream)
  "Deserializes a message object of type '<bool_aux>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'data) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<bool_aux>)))
  "Returns string type for a message object of type '<bool_aux>"
  "irobot_fcpp_simul/bool_aux")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'bool_aux)))
  "Returns string type for a message object of type 'bool_aux"
  "irobot_fcpp_simul/bool_aux")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<bool_aux>)))
  "Returns md5sum for a message object of type '<bool_aux>"
  "542e22b190dc8e6eb476d50dda88feb7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'bool_aux)))
  "Returns md5sum for a message object of type 'bool_aux"
  "542e22b190dc8e6eb476d50dda88feb7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<bool_aux>)))
  "Returns full string definition for message of type '<bool_aux>"
  (cl:format cl:nil "Header header~%bool data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'bool_aux)))
  "Returns full string definition for message of type 'bool_aux"
  (cl:format cl:nil "Header header~%bool data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <bool_aux>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <bool_aux>))
  "Converts a ROS message object to a list"
  (cl:list 'bool_aux
    (cl:cons ':header (header msg))
    (cl:cons ':data (data msg))
))
