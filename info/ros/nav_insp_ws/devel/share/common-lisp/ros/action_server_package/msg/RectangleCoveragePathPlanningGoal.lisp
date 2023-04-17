; Auto-generated. Do not edit!


(cl:in-package action_server_package-msg)


;//! \htmlinclude RectangleCoveragePathPlanningGoal.msg.html

(cl:defclass <RectangleCoveragePathPlanningGoal> (roslisp-msg-protocol:ros-message)
  ((long_rectangle
    :reader long_rectangle
    :initarg :long_rectangle
    :type cl:float
    :initform 0.0)
   (width_rectangle
    :reader width_rectangle
    :initarg :width_rectangle
    :type cl:float
    :initform 0.0)
   (step
    :reader step
    :initarg :step
    :type cl:float
    :initform 0.0)
   (dist_lr
    :reader dist_lr
    :initarg :dist_lr
    :type cl:float
    :initform 0.0)
   (width_laser
    :reader width_laser
    :initarg :width_laser
    :type cl:float
    :initform 0.0))
)

(cl:defclass RectangleCoveragePathPlanningGoal (<RectangleCoveragePathPlanningGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RectangleCoveragePathPlanningGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RectangleCoveragePathPlanningGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-msg:<RectangleCoveragePathPlanningGoal> is deprecated: use action_server_package-msg:RectangleCoveragePathPlanningGoal instead.")))

(cl:ensure-generic-function 'long_rectangle-val :lambda-list '(m))
(cl:defmethod long_rectangle-val ((m <RectangleCoveragePathPlanningGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:long_rectangle-val is deprecated.  Use action_server_package-msg:long_rectangle instead.")
  (long_rectangle m))

(cl:ensure-generic-function 'width_rectangle-val :lambda-list '(m))
(cl:defmethod width_rectangle-val ((m <RectangleCoveragePathPlanningGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:width_rectangle-val is deprecated.  Use action_server_package-msg:width_rectangle instead.")
  (width_rectangle m))

(cl:ensure-generic-function 'step-val :lambda-list '(m))
(cl:defmethod step-val ((m <RectangleCoveragePathPlanningGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:step-val is deprecated.  Use action_server_package-msg:step instead.")
  (step m))

(cl:ensure-generic-function 'dist_lr-val :lambda-list '(m))
(cl:defmethod dist_lr-val ((m <RectangleCoveragePathPlanningGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:dist_lr-val is deprecated.  Use action_server_package-msg:dist_lr instead.")
  (dist_lr m))

(cl:ensure-generic-function 'width_laser-val :lambda-list '(m))
(cl:defmethod width_laser-val ((m <RectangleCoveragePathPlanningGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:width_laser-val is deprecated.  Use action_server_package-msg:width_laser instead.")
  (width_laser m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RectangleCoveragePathPlanningGoal>) ostream)
  "Serializes a message object of type '<RectangleCoveragePathPlanningGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_rectangle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_rectangle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'step))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dist_lr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_laser))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RectangleCoveragePathPlanningGoal>) istream)
  "Deserializes a message object of type '<RectangleCoveragePathPlanningGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_rectangle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_rectangle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'step) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_lr) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_laser) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RectangleCoveragePathPlanningGoal>)))
  "Returns string type for a message object of type '<RectangleCoveragePathPlanningGoal>"
  "action_server_package/RectangleCoveragePathPlanningGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RectangleCoveragePathPlanningGoal)))
  "Returns string type for a message object of type 'RectangleCoveragePathPlanningGoal"
  "action_server_package/RectangleCoveragePathPlanningGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RectangleCoveragePathPlanningGoal>)))
  "Returns md5sum for a message object of type '<RectangleCoveragePathPlanningGoal>"
  "fb214e6b9016e277d4f4a781e958ab46")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RectangleCoveragePathPlanningGoal)))
  "Returns md5sum for a message object of type 'RectangleCoveragePathPlanningGoal"
  "fb214e6b9016e277d4f4a781e958ab46")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RectangleCoveragePathPlanningGoal>)))
  "Returns full string definition for message of type '<RectangleCoveragePathPlanningGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 long_rectangle~%float32 width_rectangle~%float32 step~%float32 dist_lr~%float32 width_laser~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RectangleCoveragePathPlanningGoal)))
  "Returns full string definition for message of type 'RectangleCoveragePathPlanningGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 long_rectangle~%float32 width_rectangle~%float32 step~%float32 dist_lr~%float32 width_laser~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RectangleCoveragePathPlanningGoal>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RectangleCoveragePathPlanningGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'RectangleCoveragePathPlanningGoal
    (cl:cons ':long_rectangle (long_rectangle msg))
    (cl:cons ':width_rectangle (width_rectangle msg))
    (cl:cons ':step (step msg))
    (cl:cons ':dist_lr (dist_lr msg))
    (cl:cons ':width_laser (width_laser msg))
))
