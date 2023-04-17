; Auto-generated. Do not edit!


(cl:in-package irobot_dimensions_pckg-msg)


;//! \htmlinclude obtainDimensionGoal.msg.html

(cl:defclass <obtainDimensionGoal> (roslisp-msg-protocol:ros-message)
  ((folder_path1
    :reader folder_path1
    :initarg :folder_path1
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (n_imgs1
    :reader n_imgs1
    :initarg :n_imgs1
    :type cl:integer
    :initform 0)
   (folder_path2
    :reader folder_path2
    :initarg :folder_path2
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (n_imgs2
    :reader n_imgs2
    :initarg :n_imgs2
    :type cl:integer
    :initform 0))
)

(cl:defclass obtainDimensionGoal (<obtainDimensionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obtainDimensionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obtainDimensionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_dimensions_pckg-msg:<obtainDimensionGoal> is deprecated: use irobot_dimensions_pckg-msg:obtainDimensionGoal instead.")))

(cl:ensure-generic-function 'folder_path1-val :lambda-list '(m))
(cl:defmethod folder_path1-val ((m <obtainDimensionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:folder_path1-val is deprecated.  Use irobot_dimensions_pckg-msg:folder_path1 instead.")
  (folder_path1 m))

(cl:ensure-generic-function 'n_imgs1-val :lambda-list '(m))
(cl:defmethod n_imgs1-val ((m <obtainDimensionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:n_imgs1-val is deprecated.  Use irobot_dimensions_pckg-msg:n_imgs1 instead.")
  (n_imgs1 m))

(cl:ensure-generic-function 'folder_path2-val :lambda-list '(m))
(cl:defmethod folder_path2-val ((m <obtainDimensionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:folder_path2-val is deprecated.  Use irobot_dimensions_pckg-msg:folder_path2 instead.")
  (folder_path2 m))

(cl:ensure-generic-function 'n_imgs2-val :lambda-list '(m))
(cl:defmethod n_imgs2-val ((m <obtainDimensionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_dimensions_pckg-msg:n_imgs2-val is deprecated.  Use irobot_dimensions_pckg-msg:n_imgs2 instead.")
  (n_imgs2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obtainDimensionGoal>) ostream)
  "Serializes a message object of type '<obtainDimensionGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'folder_path1) ostream)
  (cl:let* ((signed (cl:slot-value msg 'n_imgs1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'folder_path2) ostream)
  (cl:let* ((signed (cl:slot-value msg 'n_imgs2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obtainDimensionGoal>) istream)
  "Deserializes a message object of type '<obtainDimensionGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'folder_path1) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'folder_path2) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_imgs2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obtainDimensionGoal>)))
  "Returns string type for a message object of type '<obtainDimensionGoal>"
  "irobot_dimensions_pckg/obtainDimensionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obtainDimensionGoal)))
  "Returns string type for a message object of type 'obtainDimensionGoal"
  "irobot_dimensions_pckg/obtainDimensionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obtainDimensionGoal>)))
  "Returns md5sum for a message object of type '<obtainDimensionGoal>"
  "d5a4c79a4840d0e4c90009d8806c0768")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obtainDimensionGoal)))
  "Returns md5sum for a message object of type 'obtainDimensionGoal"
  "d5a4c79a4840d0e4c90009d8806c0768")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obtainDimensionGoal>)))
  "Returns full string definition for message of type '<obtainDimensionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String folder_path1~%int32 n_imgs1~%std_msgs/String folder_path2~%int32 n_imgs2~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obtainDimensionGoal)))
  "Returns full string definition for message of type 'obtainDimensionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String folder_path1~%int32 n_imgs1~%std_msgs/String folder_path2~%int32 n_imgs2~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obtainDimensionGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'folder_path1))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'folder_path2))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obtainDimensionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'obtainDimensionGoal
    (cl:cons ':folder_path1 (folder_path1 msg))
    (cl:cons ':n_imgs1 (n_imgs1 msg))
    (cl:cons ':folder_path2 (folder_path2 msg))
    (cl:cons ':n_imgs2 (n_imgs2 msg))
))
