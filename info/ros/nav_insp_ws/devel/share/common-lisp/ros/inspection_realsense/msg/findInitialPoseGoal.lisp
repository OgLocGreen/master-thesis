; Auto-generated. Do not edit!


(cl:in-package inspection_realsense-msg)


;//! \htmlinclude findInitialPoseGoal.msg.html

(cl:defclass <findInitialPoseGoal> (roslisp-msg-protocol:ros-message)
  ((vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0)
   (width_sheet
    :reader width_sheet
    :initarg :width_sheet
    :type cl:float
    :initform 0.0)
   (long_sheet
    :reader long_sheet
    :initarg :long_sheet
    :type cl:float
    :initform 0.0)
   (width_robot
    :reader width_robot
    :initarg :width_robot
    :type cl:float
    :initform 0.0)
   (long_robot
    :reader long_robot
    :initarg :long_robot
    :type cl:float
    :initform 0.0)
   (step
    :reader step
    :initarg :step
    :type cl:float
    :initform 0.0))
)

(cl:defclass findInitialPoseGoal (<findInitialPoseGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <findInitialPoseGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'findInitialPoseGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name inspection_realsense-msg:<findInitialPoseGoal> is deprecated: use inspection_realsense-msg:findInitialPoseGoal instead.")))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:vel-val is deprecated.  Use inspection_realsense-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'width_sheet-val :lambda-list '(m))
(cl:defmethod width_sheet-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:width_sheet-val is deprecated.  Use inspection_realsense-msg:width_sheet instead.")
  (width_sheet m))

(cl:ensure-generic-function 'long_sheet-val :lambda-list '(m))
(cl:defmethod long_sheet-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:long_sheet-val is deprecated.  Use inspection_realsense-msg:long_sheet instead.")
  (long_sheet m))

(cl:ensure-generic-function 'width_robot-val :lambda-list '(m))
(cl:defmethod width_robot-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:width_robot-val is deprecated.  Use inspection_realsense-msg:width_robot instead.")
  (width_robot m))

(cl:ensure-generic-function 'long_robot-val :lambda-list '(m))
(cl:defmethod long_robot-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:long_robot-val is deprecated.  Use inspection_realsense-msg:long_robot instead.")
  (long_robot m))

(cl:ensure-generic-function 'step-val :lambda-list '(m))
(cl:defmethod step-val ((m <findInitialPoseGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:step-val is deprecated.  Use inspection_realsense-msg:step instead.")
  (step m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <findInitialPoseGoal>) ostream)
  "Serializes a message object of type '<findInitialPoseGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_sheet))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_sheet))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_robot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_robot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'step))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <findInitialPoseGoal>) istream)
  "Deserializes a message object of type '<findInitialPoseGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_sheet) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_sheet) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_robot) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_robot) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'step) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<findInitialPoseGoal>)))
  "Returns string type for a message object of type '<findInitialPoseGoal>"
  "inspection_realsense/findInitialPoseGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'findInitialPoseGoal)))
  "Returns string type for a message object of type 'findInitialPoseGoal"
  "inspection_realsense/findInitialPoseGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<findInitialPoseGoal>)))
  "Returns md5sum for a message object of type '<findInitialPoseGoal>"
  "dfefd159abe631060bf2161faa81fdc1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'findInitialPoseGoal)))
  "Returns md5sum for a message object of type 'findInitialPoseGoal"
  "dfefd159abe631060bf2161faa81fdc1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<findInitialPoseGoal>)))
  "Returns full string definition for message of type '<findInitialPoseGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 vel~%float32 width_sheet~%float32 long_sheet~%float32 width_robot~%float32 long_robot~%float32 step~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'findInitialPoseGoal)))
  "Returns full string definition for message of type 'findInitialPoseGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 vel~%float32 width_sheet~%float32 long_sheet~%float32 width_robot~%float32 long_robot~%float32 step~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <findInitialPoseGoal>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <findInitialPoseGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'findInitialPoseGoal
    (cl:cons ':vel (vel msg))
    (cl:cons ':width_sheet (width_sheet msg))
    (cl:cons ':long_sheet (long_sheet msg))
    (cl:cons ':width_robot (width_robot msg))
    (cl:cons ':long_robot (long_robot msg))
    (cl:cons ':step (step msg))
))
