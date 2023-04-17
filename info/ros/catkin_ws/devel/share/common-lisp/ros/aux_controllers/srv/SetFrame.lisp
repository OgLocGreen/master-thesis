; Auto-generated. Do not edit!


(cl:in-package aux_controllers-srv)


;//! \htmlinclude SetFrame-request.msg.html

(cl:defclass <SetFrame-request> (roslisp-msg-protocol:ros-message)
  ((ini
    :reader ini
    :initarg :ini
    :type cl:boolean
    :initform cl:nil)
   (origin_x
    :reader origin_x
    :initarg :origin_x
    :type cl:float
    :initform 0.0)
   (origin_y
    :reader origin_y
    :initarg :origin_y
    :type cl:float
    :initform 0.0)
   (origin_z
    :reader origin_z
    :initarg :origin_z
    :type cl:float
    :initform 0.0)
   (rotation_roll
    :reader rotation_roll
    :initarg :rotation_roll
    :type cl:float
    :initform 0.0)
   (rotation_pitch
    :reader rotation_pitch
    :initarg :rotation_pitch
    :type cl:float
    :initform 0.0)
   (rotation_yaw
    :reader rotation_yaw
    :initarg :rotation_yaw
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetFrame-request (<SetFrame-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFrame-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFrame-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name aux_controllers-srv:<SetFrame-request> is deprecated: use aux_controllers-srv:SetFrame-request instead.")))

(cl:ensure-generic-function 'ini-val :lambda-list '(m))
(cl:defmethod ini-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:ini-val is deprecated.  Use aux_controllers-srv:ini instead.")
  (ini m))

(cl:ensure-generic-function 'origin_x-val :lambda-list '(m))
(cl:defmethod origin_x-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:origin_x-val is deprecated.  Use aux_controllers-srv:origin_x instead.")
  (origin_x m))

(cl:ensure-generic-function 'origin_y-val :lambda-list '(m))
(cl:defmethod origin_y-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:origin_y-val is deprecated.  Use aux_controllers-srv:origin_y instead.")
  (origin_y m))

(cl:ensure-generic-function 'origin_z-val :lambda-list '(m))
(cl:defmethod origin_z-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:origin_z-val is deprecated.  Use aux_controllers-srv:origin_z instead.")
  (origin_z m))

(cl:ensure-generic-function 'rotation_roll-val :lambda-list '(m))
(cl:defmethod rotation_roll-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:rotation_roll-val is deprecated.  Use aux_controllers-srv:rotation_roll instead.")
  (rotation_roll m))

(cl:ensure-generic-function 'rotation_pitch-val :lambda-list '(m))
(cl:defmethod rotation_pitch-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:rotation_pitch-val is deprecated.  Use aux_controllers-srv:rotation_pitch instead.")
  (rotation_pitch m))

(cl:ensure-generic-function 'rotation_yaw-val :lambda-list '(m))
(cl:defmethod rotation_yaw-val ((m <SetFrame-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:rotation_yaw-val is deprecated.  Use aux_controllers-srv:rotation_yaw instead.")
  (rotation_yaw m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFrame-request>) ostream)
  "Serializes a message object of type '<SetFrame-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ini) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'origin_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'origin_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'origin_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rotation_roll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rotation_pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rotation_yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFrame-request>) istream)
  "Deserializes a message object of type '<SetFrame-request>"
    (cl:setf (cl:slot-value msg 'ini) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'origin_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'origin_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'origin_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rotation_roll) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rotation_pitch) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rotation_yaw) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFrame-request>)))
  "Returns string type for a service object of type '<SetFrame-request>"
  "aux_controllers/SetFrameRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFrame-request)))
  "Returns string type for a service object of type 'SetFrame-request"
  "aux_controllers/SetFrameRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFrame-request>)))
  "Returns md5sum for a message object of type '<SetFrame-request>"
  "fc7b3836a679f38a5c6b9328b643f1e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFrame-request)))
  "Returns md5sum for a message object of type 'SetFrame-request"
  "fc7b3836a679f38a5c6b9328b643f1e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFrame-request>)))
  "Returns full string definition for message of type '<SetFrame-request>"
  (cl:format cl:nil "bool ini~%~%float32 origin_x~%float32 origin_y~%float32 origin_z~%~%float32 rotation_roll~%float32 rotation_pitch~%float32 rotation_yaw~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFrame-request)))
  "Returns full string definition for message of type 'SetFrame-request"
  (cl:format cl:nil "bool ini~%~%float32 origin_x~%float32 origin_y~%float32 origin_z~%~%float32 rotation_roll~%float32 rotation_pitch~%float32 rotation_yaw~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFrame-request>))
  (cl:+ 0
     1
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFrame-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFrame-request
    (cl:cons ':ini (ini msg))
    (cl:cons ':origin_x (origin_x msg))
    (cl:cons ':origin_y (origin_y msg))
    (cl:cons ':origin_z (origin_z msg))
    (cl:cons ':rotation_roll (rotation_roll msg))
    (cl:cons ':rotation_pitch (rotation_pitch msg))
    (cl:cons ':rotation_yaw (rotation_yaw msg))
))
;//! \htmlinclude SetFrame-response.msg.html

(cl:defclass <SetFrame-response> (roslisp-msg-protocol:ros-message)
  ((respond
    :reader respond
    :initarg :respond
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetFrame-response (<SetFrame-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFrame-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFrame-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name aux_controllers-srv:<SetFrame-response> is deprecated: use aux_controllers-srv:SetFrame-response instead.")))

(cl:ensure-generic-function 'respond-val :lambda-list '(m))
(cl:defmethod respond-val ((m <SetFrame-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aux_controllers-srv:respond-val is deprecated.  Use aux_controllers-srv:respond instead.")
  (respond m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFrame-response>) ostream)
  "Serializes a message object of type '<SetFrame-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'respond) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFrame-response>) istream)
  "Deserializes a message object of type '<SetFrame-response>"
    (cl:setf (cl:slot-value msg 'respond) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFrame-response>)))
  "Returns string type for a service object of type '<SetFrame-response>"
  "aux_controllers/SetFrameResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFrame-response)))
  "Returns string type for a service object of type 'SetFrame-response"
  "aux_controllers/SetFrameResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFrame-response>)))
  "Returns md5sum for a message object of type '<SetFrame-response>"
  "fc7b3836a679f38a5c6b9328b643f1e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFrame-response)))
  "Returns md5sum for a message object of type 'SetFrame-response"
  "fc7b3836a679f38a5c6b9328b643f1e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFrame-response>)))
  "Returns full string definition for message of type '<SetFrame-response>"
  (cl:format cl:nil "bool respond~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFrame-response)))
  "Returns full string definition for message of type 'SetFrame-response"
  (cl:format cl:nil "bool respond~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFrame-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFrame-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFrame-response
    (cl:cons ':respond (respond msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetFrame)))
  'SetFrame-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetFrame)))
  'SetFrame-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFrame)))
  "Returns string type for a service object of type '<SetFrame>"
  "aux_controllers/SetFrame")