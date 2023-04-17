; Auto-generated. Do not edit!


(cl:in-package inspection_realsense-msg)


;//! \htmlinclude moveBackwardGoal.msg.html

(cl:defclass <moveBackwardGoal> (roslisp-msg-protocol:ros-message)
  ((vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0)
   (n_pasadas_ant
    :reader n_pasadas_ant
    :initarg :n_pasadas_ant
    :type cl:integer
    :initform 0)
   (n_imgs_ant
    :reader n_imgs_ant
    :initarg :n_imgs_ant
    :type cl:integer
    :initform 0))
)

(cl:defclass moveBackwardGoal (<moveBackwardGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <moveBackwardGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'moveBackwardGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name inspection_realsense-msg:<moveBackwardGoal> is deprecated: use inspection_realsense-msg:moveBackwardGoal instead.")))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <moveBackwardGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:vel-val is deprecated.  Use inspection_realsense-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'n_pasadas_ant-val :lambda-list '(m))
(cl:defmethod n_pasadas_ant-val ((m <moveBackwardGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:n_pasadas_ant-val is deprecated.  Use inspection_realsense-msg:n_pasadas_ant instead.")
  (n_pasadas_ant m))

(cl:ensure-generic-function 'n_imgs_ant-val :lambda-list '(m))
(cl:defmethod n_imgs_ant-val ((m <moveBackwardGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:n_imgs_ant-val is deprecated.  Use inspection_realsense-msg:n_imgs_ant instead.")
  (n_imgs_ant m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <moveBackwardGoal>) ostream)
  "Serializes a message object of type '<moveBackwardGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'n_pasadas_ant)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n_imgs_ant)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <moveBackwardGoal>) istream)
  "Deserializes a message object of type '<moveBackwardGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_pasadas_ant) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs_ant) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<moveBackwardGoal>)))
  "Returns string type for a message object of type '<moveBackwardGoal>"
  "inspection_realsense/moveBackwardGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'moveBackwardGoal)))
  "Returns string type for a message object of type 'moveBackwardGoal"
  "inspection_realsense/moveBackwardGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<moveBackwardGoal>)))
  "Returns md5sum for a message object of type '<moveBackwardGoal>"
  "26095be20a715ca0a2049a176afb9bed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'moveBackwardGoal)))
  "Returns md5sum for a message object of type 'moveBackwardGoal"
  "26095be20a715ca0a2049a176afb9bed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<moveBackwardGoal>)))
  "Returns full string definition for message of type '<moveBackwardGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 vel~%int32 n_pasadas_ant~%int32 n_imgs_ant~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'moveBackwardGoal)))
  "Returns full string definition for message of type 'moveBackwardGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 vel~%int32 n_pasadas_ant~%int32 n_imgs_ant~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <moveBackwardGoal>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <moveBackwardGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'moveBackwardGoal
    (cl:cons ':vel (vel msg))
    (cl:cons ':n_pasadas_ant (n_pasadas_ant msg))
    (cl:cons ':n_imgs_ant (n_imgs_ant msg))
))
