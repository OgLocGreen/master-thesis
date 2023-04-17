; Auto-generated. Do not edit!


(cl:in-package inspection_realsense-msg)


;//! \htmlinclude moveBackwardResult.msg.html

(cl:defclass <moveBackwardResult> (roslisp-msg-protocol:ros-message)
  ((finished
    :reader finished
    :initarg :finished
    :type cl:boolean
    :initform cl:nil)
   (n_pasadas_act
    :reader n_pasadas_act
    :initarg :n_pasadas_act
    :type cl:integer
    :initform 0)
   (n_imgs_act
    :reader n_imgs_act
    :initarg :n_imgs_act
    :type cl:integer
    :initform 0))
)

(cl:defclass moveBackwardResult (<moveBackwardResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <moveBackwardResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'moveBackwardResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name inspection_realsense-msg:<moveBackwardResult> is deprecated: use inspection_realsense-msg:moveBackwardResult instead.")))

(cl:ensure-generic-function 'finished-val :lambda-list '(m))
(cl:defmethod finished-val ((m <moveBackwardResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:finished-val is deprecated.  Use inspection_realsense-msg:finished instead.")
  (finished m))

(cl:ensure-generic-function 'n_pasadas_act-val :lambda-list '(m))
(cl:defmethod n_pasadas_act-val ((m <moveBackwardResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:n_pasadas_act-val is deprecated.  Use inspection_realsense-msg:n_pasadas_act instead.")
  (n_pasadas_act m))

(cl:ensure-generic-function 'n_imgs_act-val :lambda-list '(m))
(cl:defmethod n_imgs_act-val ((m <moveBackwardResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader inspection_realsense-msg:n_imgs_act-val is deprecated.  Use inspection_realsense-msg:n_imgs_act instead.")
  (n_imgs_act m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <moveBackwardResult>) ostream)
  "Serializes a message object of type '<moveBackwardResult>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'finished) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'n_pasadas_act)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n_imgs_act)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <moveBackwardResult>) istream)
  "Deserializes a message object of type '<moveBackwardResult>"
    (cl:setf (cl:slot-value msg 'finished) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_pasadas_act) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs_act) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<moveBackwardResult>)))
  "Returns string type for a message object of type '<moveBackwardResult>"
  "inspection_realsense/moveBackwardResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'moveBackwardResult)))
  "Returns string type for a message object of type 'moveBackwardResult"
  "inspection_realsense/moveBackwardResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<moveBackwardResult>)))
  "Returns md5sum for a message object of type '<moveBackwardResult>"
  "1eb6bc0e5a253dc264ac900fe4b70f59")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'moveBackwardResult)))
  "Returns md5sum for a message object of type 'moveBackwardResult"
  "1eb6bc0e5a253dc264ac900fe4b70f59")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<moveBackwardResult>)))
  "Returns full string definition for message of type '<moveBackwardResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%bool finished~%int32 n_pasadas_act~%int32 n_imgs_act~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'moveBackwardResult)))
  "Returns full string definition for message of type 'moveBackwardResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%bool finished~%int32 n_pasadas_act~%int32 n_imgs_act~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <moveBackwardResult>))
  (cl:+ 0
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <moveBackwardResult>))
  "Converts a ROS message object to a list"
  (cl:list 'moveBackwardResult
    (cl:cons ':finished (finished msg))
    (cl:cons ':n_pasadas_act (n_pasadas_act msg))
    (cl:cons ':n_imgs_act (n_imgs_act msg))
))
