; Auto-generated. Do not edit!


(cl:in-package irobot_inspection_pckg-msg)


;//! \htmlinclude getPolygonsGoal.msg.html

(cl:defclass <getPolygonsGoal> (roslisp-msg-protocol:ros-message)
  ((path
    :reader path
    :initarg :path
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (sheet_size_x
    :reader sheet_size_x
    :initarg :sheet_size_x
    :type cl:float
    :initform 0.0)
   (sheet_size_y
    :reader sheet_size_y
    :initarg :sheet_size_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass getPolygonsGoal (<getPolygonsGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getPolygonsGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getPolygonsGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_inspection_pckg-msg:<getPolygonsGoal> is deprecated: use irobot_inspection_pckg-msg:getPolygonsGoal instead.")))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <getPolygonsGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:path-val is deprecated.  Use irobot_inspection_pckg-msg:path instead.")
  (path m))

(cl:ensure-generic-function 'sheet_size_x-val :lambda-list '(m))
(cl:defmethod sheet_size_x-val ((m <getPolygonsGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:sheet_size_x-val is deprecated.  Use irobot_inspection_pckg-msg:sheet_size_x instead.")
  (sheet_size_x m))

(cl:ensure-generic-function 'sheet_size_y-val :lambda-list '(m))
(cl:defmethod sheet_size_y-val ((m <getPolygonsGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:sheet_size_y-val is deprecated.  Use irobot_inspection_pckg-msg:sheet_size_y instead.")
  (sheet_size_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getPolygonsGoal>) ostream)
  "Serializes a message object of type '<getPolygonsGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'sheet_size_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'sheet_size_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getPolygonsGoal>) istream)
  "Deserializes a message object of type '<getPolygonsGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sheet_size_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sheet_size_y) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getPolygonsGoal>)))
  "Returns string type for a message object of type '<getPolygonsGoal>"
  "irobot_inspection_pckg/getPolygonsGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getPolygonsGoal)))
  "Returns string type for a message object of type 'getPolygonsGoal"
  "irobot_inspection_pckg/getPolygonsGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getPolygonsGoal>)))
  "Returns md5sum for a message object of type '<getPolygonsGoal>"
  "314705d7efc97b3af398047d40577a3c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getPolygonsGoal)))
  "Returns md5sum for a message object of type 'getPolygonsGoal"
  "314705d7efc97b3af398047d40577a3c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getPolygonsGoal>)))
  "Returns full string definition for message of type '<getPolygonsGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String path~%float64 sheet_size_x~%float64 sheet_size_y~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getPolygonsGoal)))
  "Returns full string definition for message of type 'getPolygonsGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String path~%float64 sheet_size_x~%float64 sheet_size_y~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getPolygonsGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getPolygonsGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'getPolygonsGoal
    (cl:cons ':path (path msg))
    (cl:cons ':sheet_size_x (sheet_size_x msg))
    (cl:cons ':sheet_size_y (sheet_size_y msg))
))
