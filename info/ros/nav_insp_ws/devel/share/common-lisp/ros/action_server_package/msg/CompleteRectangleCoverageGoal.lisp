; Auto-generated. Do not edit!


(cl:in-package action_server_package-msg)


;//! \htmlinclude CompleteRectangleCoverageGoal.msg.html

(cl:defclass <CompleteRectangleCoverageGoal> (roslisp-msg-protocol:ros-message)
  ((rect_long
    :reader rect_long
    :initarg :rect_long
    :type cl:float
    :initform 0.0)
   (rect_width
    :reader rect_width
    :initarg :rect_width
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
   (laser_width
    :reader laser_width
    :initarg :laser_width
    :type cl:float
    :initform 0.0)
   (vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0))
)

(cl:defclass CompleteRectangleCoverageGoal (<CompleteRectangleCoverageGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CompleteRectangleCoverageGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CompleteRectangleCoverageGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-msg:<CompleteRectangleCoverageGoal> is deprecated: use action_server_package-msg:CompleteRectangleCoverageGoal instead.")))

(cl:ensure-generic-function 'rect_long-val :lambda-list '(m))
(cl:defmethod rect_long-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:rect_long-val is deprecated.  Use action_server_package-msg:rect_long instead.")
  (rect_long m))

(cl:ensure-generic-function 'rect_width-val :lambda-list '(m))
(cl:defmethod rect_width-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:rect_width-val is deprecated.  Use action_server_package-msg:rect_width instead.")
  (rect_width m))

(cl:ensure-generic-function 'step-val :lambda-list '(m))
(cl:defmethod step-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:step-val is deprecated.  Use action_server_package-msg:step instead.")
  (step m))

(cl:ensure-generic-function 'dist_lr-val :lambda-list '(m))
(cl:defmethod dist_lr-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:dist_lr-val is deprecated.  Use action_server_package-msg:dist_lr instead.")
  (dist_lr m))

(cl:ensure-generic-function 'laser_width-val :lambda-list '(m))
(cl:defmethod laser_width-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:laser_width-val is deprecated.  Use action_server_package-msg:laser_width instead.")
  (laser_width m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <CompleteRectangleCoverageGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-msg:vel-val is deprecated.  Use action_server_package-msg:vel instead.")
  (vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CompleteRectangleCoverageGoal>) ostream)
  "Serializes a message object of type '<CompleteRectangleCoverageGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rect_long))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rect_width))))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'laser_width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CompleteRectangleCoverageGoal>) istream)
  "Deserializes a message object of type '<CompleteRectangleCoverageGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rect_long) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rect_width) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'laser_width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CompleteRectangleCoverageGoal>)))
  "Returns string type for a message object of type '<CompleteRectangleCoverageGoal>"
  "action_server_package/CompleteRectangleCoverageGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CompleteRectangleCoverageGoal)))
  "Returns string type for a message object of type 'CompleteRectangleCoverageGoal"
  "action_server_package/CompleteRectangleCoverageGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CompleteRectangleCoverageGoal>)))
  "Returns md5sum for a message object of type '<CompleteRectangleCoverageGoal>"
  "99f0c81406704524af476d87104d837e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CompleteRectangleCoverageGoal)))
  "Returns md5sum for a message object of type 'CompleteRectangleCoverageGoal"
  "99f0c81406704524af476d87104d837e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CompleteRectangleCoverageGoal>)))
  "Returns full string definition for message of type '<CompleteRectangleCoverageGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 rect_long~%float32 rect_width~%float32 step~%float32 dist_lr~%float32 laser_width~%~%float32 vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CompleteRectangleCoverageGoal)))
  "Returns full string definition for message of type 'CompleteRectangleCoverageGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32 rect_long~%float32 rect_width~%float32 step~%float32 dist_lr~%float32 laser_width~%~%float32 vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CompleteRectangleCoverageGoal>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CompleteRectangleCoverageGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'CompleteRectangleCoverageGoal
    (cl:cons ':rect_long (rect_long msg))
    (cl:cons ':rect_width (rect_width msg))
    (cl:cons ':step (step msg))
    (cl:cons ':dist_lr (dist_lr msg))
    (cl:cons ':laser_width (laser_width msg))
    (cl:cons ':vel (vel msg))
))
