; Auto-generated. Do not edit!


(cl:in-package action_server_package-msg)


;//! \htmlinclude RectangleCoveragePathPlanningActionGoal.msg.html

(cl:defclass <RectangleCoveragePathPlanningActionGoal> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (goal_id
    :reader goal_id
    :initarg :goal_id
    :type actionlib_msgs-msg:GoalID
    :initform (cl:make-instance 'actionlib_msgs-msg:GoalID))
   (goal
    :reader goal
    :initarg :goal
    :type action_server_package-msg:RectangleCoveragePathPlanningGoal
    :initform (cl:make-instance 'action_server_package-msg:RectangleCoveragePathPlanningGoal)))
)

(cl:defclass RectangleCoveragePathPlanningActionGoal (<RectangleCoveragePathPlanningActionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RectangleCoveragePathPlanningActionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RectangleCoveragePathPlanningActionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-msg:<RectangleCoveragePathPlanningActionGoal> is deprecated: use action_server_package-msg:RectangleCoveragePathPlanningActionGoal instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <RectangleCoveragePathPlanningActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:header-val is deprecated.  Use action_server_package-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'goal_id-val :lambda-list '(m))
(cl:defmethod goal_id-val ((m <RectangleCoveragePathPlanningActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:goal_id-val is deprecated.  Use action_server_package-msg:goal_id instead.")
  (goal_id m))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <RectangleCoveragePathPlanningActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:goal-val is deprecated.  Use action_server_package-msg:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RectangleCoveragePathPlanningActionGoal>) ostream)
  "Serializes a message object of type '<RectangleCoveragePathPlanningActionGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_id) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RectangleCoveragePathPlanningActionGoal>) istream)
  "Deserializes a message object of type '<RectangleCoveragePathPlanningActionGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_id) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RectangleCoveragePathPlanningActionGoal>)))
  "Returns string type for a message object of type '<RectangleCoveragePathPlanningActionGoal>"
  "action_server_package/RectangleCoveragePathPlanningActionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RectangleCoveragePathPlanningActionGoal)))
  "Returns string type for a message object of type 'RectangleCoveragePathPlanningActionGoal"
  "action_server_package/RectangleCoveragePathPlanningActionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RectangleCoveragePathPlanningActionGoal>)))
  "Returns md5sum for a message object of type '<RectangleCoveragePathPlanningActionGoal>"
  "748fc6d1a932ff08cfa9fa03a99dba28")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RectangleCoveragePathPlanningActionGoal)))
  "Returns md5sum for a message object of type 'RectangleCoveragePathPlanningActionGoal"
  "748fc6d1a932ff08cfa9fa03a99dba28")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RectangleCoveragePathPlanningActionGoal>)))
  "Returns full string definition for message of type '<RectangleCoveragePathPlanningActionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%RectangleCoveragePathPlanningGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: action_server_package/RectangleCoveragePathPlanningGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 long_rectangle~%float32 width_rectangle~%float32 step~%float32 dist_lr~%float32 width_laser~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RectangleCoveragePathPlanningActionGoal)))
  "Returns full string definition for message of type 'RectangleCoveragePathPlanningActionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%RectangleCoveragePathPlanningGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: action_server_package/RectangleCoveragePathPlanningGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 long_rectangle~%float32 width_rectangle~%float32 step~%float32 dist_lr~%float32 width_laser~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RectangleCoveragePathPlanningActionGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_id))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RectangleCoveragePathPlanningActionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'RectangleCoveragePathPlanningActionGoal
    (cl:cons ':header (header msg))
    (cl:cons ':goal_id (goal_id msg))
    (cl:cons ':goal (goal msg))
))
