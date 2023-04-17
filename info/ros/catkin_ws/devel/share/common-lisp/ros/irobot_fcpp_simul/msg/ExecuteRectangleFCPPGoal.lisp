; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude ExecuteRectangleFCPPGoal.msg.html

(cl:defclass <ExecuteRectangleFCPPGoal> (roslisp-msg-protocol:ros-message)
  ((rectangle_id
    :reader rectangle_id
    :initarg :rectangle_id
    :type cl:integer
    :initform 0)
   (operation_type
    :reader operation_type
    :initarg :operation_type
    :type cl:integer
    :initform 0)
   (rectangle
    :reader rectangle
    :initarg :rectangle
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon)))
)

(cl:defclass ExecuteRectangleFCPPGoal (<ExecuteRectangleFCPPGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ExecuteRectangleFCPPGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ExecuteRectangleFCPPGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<ExecuteRectangleFCPPGoal> is deprecated: use irobot_fcpp_simul-msg:ExecuteRectangleFCPPGoal instead.")))

(cl:ensure-generic-function 'rectangle_id-val :lambda-list '(m))
(cl:defmethod rectangle_id-val ((m <ExecuteRectangleFCPPGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:rectangle_id-val is deprecated.  Use irobot_fcpp_simul-msg:rectangle_id instead.")
  (rectangle_id m))

(cl:ensure-generic-function 'operation_type-val :lambda-list '(m))
(cl:defmethod operation_type-val ((m <ExecuteRectangleFCPPGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:operation_type-val is deprecated.  Use irobot_fcpp_simul-msg:operation_type instead.")
  (operation_type m))

(cl:ensure-generic-function 'rectangle-val :lambda-list '(m))
(cl:defmethod rectangle-val ((m <ExecuteRectangleFCPPGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:rectangle-val is deprecated.  Use irobot_fcpp_simul-msg:rectangle instead.")
  (rectangle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ExecuteRectangleFCPPGoal>) ostream)
  "Serializes a message object of type '<ExecuteRectangleFCPPGoal>"
  (cl:let* ((signed (cl:slot-value msg 'rectangle_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'operation_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'rectangle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ExecuteRectangleFCPPGoal>) istream)
  "Deserializes a message object of type '<ExecuteRectangleFCPPGoal>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rectangle_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'operation_type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'rectangle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ExecuteRectangleFCPPGoal>)))
  "Returns string type for a message object of type '<ExecuteRectangleFCPPGoal>"
  "irobot_fcpp_simul/ExecuteRectangleFCPPGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExecuteRectangleFCPPGoal)))
  "Returns string type for a message object of type 'ExecuteRectangleFCPPGoal"
  "irobot_fcpp_simul/ExecuteRectangleFCPPGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ExecuteRectangleFCPPGoal>)))
  "Returns md5sum for a message object of type '<ExecuteRectangleFCPPGoal>"
  "93e42b79de0e56f88bd428b2bd59ee26")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ExecuteRectangleFCPPGoal)))
  "Returns md5sum for a message object of type 'ExecuteRectangleFCPPGoal"
  "93e42b79de0e56f88bd428b2bd59ee26")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ExecuteRectangleFCPPGoal>)))
  "Returns full string definition for message of type '<ExecuteRectangleFCPPGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%#int32 chapa_id~%int32 rectangle_id #0,90,180,270~%~%int32 operation_type~%~%geometry_msgs/Polygon rectangle~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ExecuteRectangleFCPPGoal)))
  "Returns full string definition for message of type 'ExecuteRectangleFCPPGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%#int32 chapa_id~%int32 rectangle_id #0,90,180,270~%~%int32 operation_type~%~%geometry_msgs/Polygon rectangle~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ExecuteRectangleFCPPGoal>))
  (cl:+ 0
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'rectangle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ExecuteRectangleFCPPGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'ExecuteRectangleFCPPGoal
    (cl:cons ':rectangle_id (rectangle_id msg))
    (cl:cons ':operation_type (operation_type msg))
    (cl:cons ':rectangle (rectangle msg))
))
