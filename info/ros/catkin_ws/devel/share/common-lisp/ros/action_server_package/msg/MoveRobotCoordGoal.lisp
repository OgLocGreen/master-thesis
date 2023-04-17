; Auto-generated. Do not edit!


(cl:in-package action_server_package-msg)


;//! \htmlinclude MoveRobotCoordGoal.msg.html

(cl:defclass <MoveRobotCoordGoal> (roslisp-msg-protocol:ros-message)
  ((movement
    :reader movement
    :initarg :movement
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0)
   (frame
    :reader frame
    :initarg :frame
    :type cl:string
    :initform ""))
)

(cl:defclass MoveRobotCoordGoal (<MoveRobotCoordGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveRobotCoordGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveRobotCoordGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-msg:<MoveRobotCoordGoal> is deprecated: use action_server_package-msg:MoveRobotCoordGoal instead.")))

(cl:ensure-generic-function 'movement-val :lambda-list '(m))
(cl:defmethod movement-val ((m <MoveRobotCoordGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:movement-val is deprecated.  Use action_server_package-msg:movement instead.")
  (movement m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <MoveRobotCoordGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:vel-val is deprecated.  Use action_server_package-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'frame-val :lambda-list '(m))
(cl:defmethod frame-val ((m <MoveRobotCoordGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:frame-val is deprecated.  Use action_server_package-msg:frame instead.")
  (frame m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveRobotCoordGoal>) ostream)
  "Serializes a message object of type '<MoveRobotCoordGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'movement) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frame))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frame))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveRobotCoordGoal>) istream)
  "Deserializes a message object of type '<MoveRobotCoordGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'movement) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frame) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frame) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveRobotCoordGoal>)))
  "Returns string type for a message object of type '<MoveRobotCoordGoal>"
  "action_server_package/MoveRobotCoordGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveRobotCoordGoal)))
  "Returns string type for a message object of type 'MoveRobotCoordGoal"
  "action_server_package/MoveRobotCoordGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveRobotCoordGoal>)))
  "Returns md5sum for a message object of type '<MoveRobotCoordGoal>"
  "dfe3fddf458302904dac9744b43e6d8c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveRobotCoordGoal)))
  "Returns md5sum for a message object of type 'MoveRobotCoordGoal"
  "dfe3fddf458302904dac9744b43e6d8c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveRobotCoordGoal>)))
  "Returns full string definition for message of type '<MoveRobotCoordGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%geometry_msgs/Pose2D movement~%float32 vel~%string frame~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveRobotCoordGoal)))
  "Returns full string definition for message of type 'MoveRobotCoordGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%geometry_msgs/Pose2D movement~%float32 vel~%string frame~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveRobotCoordGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'movement))
     4
     4 (cl:length (cl:slot-value msg 'frame))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveRobotCoordGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveRobotCoordGoal
    (cl:cons ':movement (movement msg))
    (cl:cons ':vel (vel msg))
    (cl:cons ':frame (frame msg))
))
