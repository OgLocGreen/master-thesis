;; Auto-generated. Do not edit!


(when (boundp 'action_server_package::BaseRotationAction)
  (if (not (find-package "ACTION_SERVER_PACKAGE"))
    (make-package "ACTION_SERVER_PACKAGE"))
  (shadow 'BaseRotationAction (find-package "ACTION_SERVER_PACKAGE")))
(unless (find-package "ACTION_SERVER_PACKAGE::BASEROTATIONACTION")
  (make-package "ACTION_SERVER_PACKAGE::BASEROTATIONACTION"))

(in-package "ROS")
;;//! \htmlinclude BaseRotationAction.msg.html


(defclass action_server_package::BaseRotationAction
  :super ros::object
  :slots (_action_goal _action_result _action_feedback ))

(defmethod action_server_package::BaseRotationAction
  (:init
   (&key
    ((:action_goal __action_goal) (instance action_server_package::BaseRotationActionGoal :init))
    ((:action_result __action_result) (instance action_server_package::BaseRotationActionResult :init))
    ((:action_feedback __action_feedback) (instance action_server_package::BaseRotationActionFeedback :init))
    )
   (send-super :init)
   (setq _action_goal __action_goal)
   (setq _action_result __action_result)
   (setq _action_feedback __action_feedback)
   self)
  (:action_goal
   (&rest __action_goal)
   (if (keywordp (car __action_goal))
       (send* _action_goal __action_goal)
     (progn
       (if __action_goal (setq _action_goal (car __action_goal)))
       _action_goal)))
  (:action_result
   (&rest __action_result)
   (if (keywordp (car __action_result))
       (send* _action_result __action_result)
     (progn
       (if __action_result (setq _action_result (car __action_result)))
       _action_result)))
  (:action_feedback
   (&rest __action_feedback)
   (if (keywordp (car __action_feedback))
       (send* _action_feedback __action_feedback)
     (progn
       (if __action_feedback (setq _action_feedback (car __action_feedback)))
       _action_feedback)))
  (:serialization-length
   ()
   (+
    ;; action_server_package/BaseRotationActionGoal _action_goal
    (send _action_goal :serialization-length)
    ;; action_server_package/BaseRotationActionResult _action_result
    (send _action_result :serialization-length)
    ;; action_server_package/BaseRotationActionFeedback _action_feedback
    (send _action_feedback :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; action_server_package/BaseRotationActionGoal _action_goal
       (send _action_goal :serialize s)
     ;; action_server_package/BaseRotationActionResult _action_result
       (send _action_result :serialize s)
     ;; action_server_package/BaseRotationActionFeedback _action_feedback
       (send _action_feedback :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; action_server_package/BaseRotationActionGoal _action_goal
     (send _action_goal :deserialize buf ptr-) (incf ptr- (send _action_goal :serialization-length))
   ;; action_server_package/BaseRotationActionResult _action_result
     (send _action_result :deserialize buf ptr-) (incf ptr- (send _action_result :serialization-length))
   ;; action_server_package/BaseRotationActionFeedback _action_feedback
     (send _action_feedback :deserialize buf ptr-) (incf ptr- (send _action_feedback :serialization-length))
   ;;
   self)
  )

(setf (get action_server_package::BaseRotationAction :md5sum-) "190ed08ebb2ee590db51d6504ffd6b2b")
(setf (get action_server_package::BaseRotationAction :datatype-) "action_server_package/BaseRotationAction")
(setf (get action_server_package::BaseRotationAction :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

BaseRotationActionGoal action_goal
BaseRotationActionResult action_result
BaseRotationActionFeedback action_feedback

================================================================================
MSG: action_server_package/BaseRotationActionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalID goal_id
BaseRotationGoal goal

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
MSG: action_server_package/BaseRotationGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define the goal
float32 number_of_degrees

================================================================================
MSG: action_server_package/BaseRotationActionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
BaseRotationResult result

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
MSG: action_server_package/BaseRotationResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define the result
float32 final_yaw

================================================================================
MSG: action_server_package/BaseRotationActionFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
BaseRotationFeedback feedback

================================================================================
MSG: action_server_package/BaseRotationFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define a feedback message
float32 degrees_rotated

")



(provide :action_server_package/BaseRotationAction "190ed08ebb2ee590db51d6504ffd6b2b")

