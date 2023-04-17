; Auto-generated. Do not edit!


(cl:in-package inspection_realsense-msg)


;//! \htmlinclude Twist_inspection.msg.html

(cl:defclass <Twist_inspection> (roslisp-msg-protocol:ros-message)
  ((linear
    :reader linear
    :initarg :linear
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (angular
    :reader angular
    :initarg :angular
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (distance_left
    :reader distance_left
    :initarg :distance_left
    :type cl:float
    :initform 0.0))
)

(cl:defclass Twist_inspection (<Twist_inspection>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Twist_inspection>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Twist_inspection)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name inspection_realsense-msg:<Twist_inspection> is deprecated: use inspection_realsense-msg:Twist_inspection instead.")))

(cl:ensure-generic-function 'linear-val :lambda-list '(m))
(cl:defmethod linear-val ((m <Twist_inspection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:linear-val is deprecated.  Use inspection_realsense-msg:linear instead.")
  (linear m))

(cl:ensure-generic-function 'angular-val :lambda-list '(m))
(cl:defmethod angular-val ((m <Twist_inspection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:angular-val is deprecated.  Use inspection_realsense-msg:angular instead.")
  (angular m))

(cl:ensure-generic-function 'distance_left-val :lambda-list '(m))
(cl:defmethod distance_left-val ((m <Twist_inspection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:distance_left-val is deprecated.  Use inspection_realsense-msg:distance_left instead.")
  (distance_left m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Twist_inspection>) ostream)
  "Serializes a message object of type '<Twist_inspection>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'linear) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angular) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Twist_inspection>) istream)
  "Deserializes a message object of type '<Twist_inspection>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'linear) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angular) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance_left) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Twist_inspection>)))
  "Returns string type for a message object of type '<Twist_inspection>"
  "inspection_realsense/Twist_inspection")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Twist_inspection)))
  "Returns string type for a message object of type 'Twist_inspection"
  "inspection_realsense/Twist_inspection")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Twist_inspection>)))
  "Returns md5sum for a message object of type '<Twist_inspection>"
  "a6d97e5058c8a6d2a96e566db38def37")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Twist_inspection)))
  "Returns md5sum for a message object of type 'Twist_inspection"
  "a6d97e5058c8a6d2a96e566db38def37")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Twist_inspection>)))
  "Returns full string definition for message of type '<Twist_inspection>"
  (cl:format cl:nil "# This expresses velocity in free space broken into it's linear and angular parts. Also, the distance left to leave the sheet~%geometry_msgs/Vector3  linear~%geometry_msgs/Vector3  angular~%float32  distance_left~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Twist_inspection)))
  "Returns full string definition for message of type 'Twist_inspection"
  (cl:format cl:nil "# This expresses velocity in free space broken into it's linear and angular parts. Also, the distance left to leave the sheet~%geometry_msgs/Vector3  linear~%geometry_msgs/Vector3  angular~%float32  distance_left~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Twist_inspection>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'linear))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angular))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Twist_inspection>))
  "Converts a ROS message object to a list"
  (cl:list 'Twist_inspection
    (cl:cons ':linear (linear msg))
    (cl:cons ':angular (angular msg))
    (cl:cons ':distance_left (distance_left msg))
))
