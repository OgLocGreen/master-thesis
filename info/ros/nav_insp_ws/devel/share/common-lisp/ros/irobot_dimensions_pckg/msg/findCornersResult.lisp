; Auto-generated. Do not edit!


(cl:in-package irobot_dimensions_pckg-msg)


;//! \htmlinclude findCornersResult.msg.html

(cl:defclass <findCornersResult> (roslisp-msg-protocol:ros-message)
  ((finished
    :reader finished
    :initarg :finished
    :type cl:boolean
    :initform cl:nil)
   (n_imgs1
    :reader n_imgs1
    :initarg :n_imgs1
    :type cl:integer
    :initform 0)
   (n_imgs2
    :reader n_imgs2
    :initarg :n_imgs2
    :type cl:integer
    :initform 0))
)

(cl:defclass findCornersResult (<findCornersResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <findCornersResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'findCornersResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_dimensions_pckg-msg:<findCornersResult> is deprecated: use irobot_dimensions_pckg-msg:findCornersResult instead.")))

(cl:ensure-generic-function 'finished-val :lambda-list '(m))
(cl:defmethod finished-val ((m <findCornersResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:finished-val is deprecated.  Use irobot_dimensions_pckg-msg:finished instead.")
  (finished m))

(cl:ensure-generic-function 'n_imgs1-val :lambda-list '(m))
(cl:defmethod n_imgs1-val ((m <findCornersResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:n_imgs1-val is deprecated.  Use irobot_dimensions_pckg-msg:n_imgs1 instead.")
  (n_imgs1 m))

(cl:ensure-generic-function 'n_imgs2-val :lambda-list '(m))
(cl:defmethod n_imgs2-val ((m <findCornersResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:n_imgs2-val is deprecated.  Use irobot_dimensions_pckg-msg:n_imgs2 instead.")
  (n_imgs2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <findCornersResult>) ostream)
  "Serializes a message object of type '<findCornersResult>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'finished) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'n_imgs1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n_imgs2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <findCornersResult>) istream)
  "Deserializes a message object of type '<findCornersResult>"
    (cl:setf (cl:slot-value msg 'finished) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<findCornersResult>)))
  "Returns string type for a message object of type '<findCornersResult>"
  "irobot_dimensions_pckg/findCornersResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'findCornersResult)))
  "Returns string type for a message object of type 'findCornersResult"
  "irobot_dimensions_pckg/findCornersResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<findCornersResult>)))
  "Returns md5sum for a message object of type '<findCornersResult>"
  "887012e06d10bcb9605b129d45f0aa9a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'findCornersResult)))
  "Returns md5sum for a message object of type 'findCornersResult"
  "887012e06d10bcb9605b129d45f0aa9a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<findCornersResult>)))
  "Returns full string definition for message of type '<findCornersResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%bool finished~%int32 n_imgs1~%int32 n_imgs2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'findCornersResult)))
  "Returns full string definition for message of type 'findCornersResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%bool finished~%int32 n_imgs1~%int32 n_imgs2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <findCornersResult>))
  (cl:+ 0
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <findCornersResult>))
  "Converts a ROS message object to a list"
  (cl:list 'findCornersResult
    (cl:cons ':finished (finished msg))
    (cl:cons ':n_imgs1 (n_imgs1 msg))
    (cl:cons ':n_imgs2 (n_imgs2 msg))
))
