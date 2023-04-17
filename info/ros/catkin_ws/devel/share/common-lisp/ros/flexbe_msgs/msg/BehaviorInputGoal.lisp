; Auto-generated. Do not edit!


(cl:in-package flexbe_msgs-msg)


;//! \htmlinclude BehaviorInputGoal.msg.html

(cl:defclass <BehaviorInputGoal> (roslisp-msg-protocol:ros-message)
  ((request_type
    :reader request_type
    :initarg :request_type
    :type cl:fixnum
    :initform 0)
   (msg
    :reader msg
    :initarg :msg
    :type cl:string
    :initform ""))
)

(cl:defclass BehaviorInputGoal (<BehaviorInputGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BehaviorInputGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BehaviorInputGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name flexbe_msgs-msg:<BehaviorInputGoal> is deprecated: use flexbe_msgs-msg:BehaviorInputGoal instead.")))

(cl:ensure-generic-function 'request_type-val :lambda-list '(m))
(cl:defmethod request_type-val ((m <BehaviorInputGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader flexbe_msgs-msg:request_type-val is deprecated.  Use flexbe_msgs-msg:request_type instead.")
  (request_type m))

(cl:ensure-generic-function 'msg-val :lambda-list '(m))
(cl:defmethod msg-val ((m <BehaviorInputGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader flexbe_msgs-msg:msg-val is deprecated.  Use flexbe_msgs-msg:msg instead.")
  (msg m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<BehaviorInputGoal>)))
    "Constants for message type '<BehaviorInputGoal>"
  '((:POINT_LOCATION . 0)
    (:SELECTED_OBJECT_ID . 1)
    (:WAYPOINT_GOAL_POSE . 2)
    (:GHOST_JOINT_STATES . 3)
    (:FOOTSTEP_PLAN_HEADER . 4))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'BehaviorInputGoal)))
    "Constants for message type 'BehaviorInputGoal"
  '((:POINT_LOCATION . 0)
    (:SELECTED_OBJECT_ID . 1)
    (:WAYPOINT_GOAL_POSE . 2)
    (:GHOST_JOINT_STATES . 3)
    (:FOOTSTEP_PLAN_HEADER . 4))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BehaviorInputGoal>) ostream)
  "Serializes a message object of type '<BehaviorInputGoal>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'request_type)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'msg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BehaviorInputGoal>) istream)
  "Deserializes a message object of type '<BehaviorInputGoal>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'request_type)) (cl:read-byte istream))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BehaviorInputGoal>)))
  "Returns string type for a message object of type '<BehaviorInputGoal>"
  "flexbe_msgs/BehaviorInputGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BehaviorInputGoal)))
  "Returns string type for a message object of type 'BehaviorInputGoal"
  "flexbe_msgs/BehaviorInputGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BehaviorInputGoal>)))
  "Returns md5sum for a message object of type '<BehaviorInputGoal>"
  "7ce7fc3e0d93d66895817ecbe9d411f6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BehaviorInputGoal)))
  "Returns md5sum for a message object of type 'BehaviorInputGoal"
  "7ce7fc3e0d93d66895817ecbe9d411f6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BehaviorInputGoal>)))
  "Returns full string definition for message of type '<BehaviorInputGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Available request types~%~%uint8 POINT_LOCATION 	    = 0~%uint8 SELECTED_OBJECT_ID    = 1~%uint8 WAYPOINT_GOAL_POSE    = 2~%uint8 GHOST_JOINT_STATES    = 3~%uint8 FOOTSTEP_PLAN_HEADER  = 4~%~%~%# Choose one of the available request types above~%uint8 request_type~%~%# Request message displayed to the operator~%# Provide context information, i.e. for which purpose the data is required.~%# The operator will be told which type of data to provide indepently from this message.~%string msg~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BehaviorInputGoal)))
  "Returns full string definition for message of type 'BehaviorInputGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Available request types~%~%uint8 POINT_LOCATION 	    = 0~%uint8 SELECTED_OBJECT_ID    = 1~%uint8 WAYPOINT_GOAL_POSE    = 2~%uint8 GHOST_JOINT_STATES    = 3~%uint8 FOOTSTEP_PLAN_HEADER  = 4~%~%~%# Choose one of the available request types above~%uint8 request_type~%~%# Request message displayed to the operator~%# Provide context information, i.e. for which purpose the data is required.~%# The operator will be told which type of data to provide indepently from this message.~%string msg~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BehaviorInputGoal>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BehaviorInputGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'BehaviorInputGoal
    (cl:cons ':request_type (request_type msg))
    (cl:cons ':msg (msg msg))
))
