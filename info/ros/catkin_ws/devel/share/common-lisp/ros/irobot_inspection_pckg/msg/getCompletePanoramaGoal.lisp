; Auto-generated. Do not edit!


(cl:in-package irobot_inspection_pckg-msg)


;//! \htmlinclude getCompletePanoramaGoal.msg.html

(cl:defclass <getCompletePanoramaGoal> (roslisp-msg-protocol:ros-message)
  ((folder_pano_path
    :reader folder_pano_path
    :initarg :folder_pano_path
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (images_number
    :reader images_number
    :initarg :images_number
    :type cl:integer
    :initform 0)
   (name_0
    :reader name_0
    :initarg :name_0
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (name_180
    :reader name_180
    :initarg :name_180
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass getCompletePanoramaGoal (<getCompletePanoramaGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getCompletePanoramaGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getCompletePanoramaGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_inspection_pckg-msg:<getCompletePanoramaGoal> is deprecated: use irobot_inspection_pckg-msg:getCompletePanoramaGoal instead.")))

(cl:ensure-generic-function 'folder_pano_path-val :lambda-list '(m))
(cl:defmethod folder_pano_path-val ((m <getCompletePanoramaGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:folder_pano_path-val is deprecated.  Use irobot_inspection_pckg-msg:folder_pano_path instead.")
  (folder_pano_path m))

(cl:ensure-generic-function 'images_number-val :lambda-list '(m))
(cl:defmethod images_number-val ((m <getCompletePanoramaGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:images_number-val is deprecated.  Use irobot_inspection_pckg-msg:images_number instead.")
  (images_number m))

(cl:ensure-generic-function 'name_0-val :lambda-list '(m))
(cl:defmethod name_0-val ((m <getCompletePanoramaGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:name_0-val is deprecated.  Use irobot_inspection_pckg-msg:name_0 instead.")
  (name_0 m))

(cl:ensure-generic-function 'name_180-val :lambda-list '(m))
(cl:defmethod name_180-val ((m <getCompletePanoramaGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_inspection_pckg-msg:name_180-val is deprecated.  Use irobot_inspection_pckg-msg:name_180 instead.")
  (name_180 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getCompletePanoramaGoal>) ostream)
  "Serializes a message object of type '<getCompletePanoramaGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'folder_pano_path) ostream)
  (cl:let* ((signed (cl:slot-value msg 'images_number)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'name_0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'name_180) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getCompletePanoramaGoal>) istream)
  "Deserializes a message object of type '<getCompletePanoramaGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'folder_pano_path) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'images_number) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'name_0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'name_180) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getCompletePanoramaGoal>)))
  "Returns string type for a message object of type '<getCompletePanoramaGoal>"
  "irobot_inspection_pckg/getCompletePanoramaGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getCompletePanoramaGoal)))
  "Returns string type for a message object of type 'getCompletePanoramaGoal"
  "irobot_inspection_pckg/getCompletePanoramaGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getCompletePanoramaGoal>)))
  "Returns md5sum for a message object of type '<getCompletePanoramaGoal>"
  "2465211dc6ab145b5fd1fa5a332f2607")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getCompletePanoramaGoal)))
  "Returns md5sum for a message object of type 'getCompletePanoramaGoal"
  "2465211dc6ab145b5fd1fa5a332f2607")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getCompletePanoramaGoal>)))
  "Returns full string definition for message of type '<getCompletePanoramaGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String folder_pano_path~%int32 images_number~%std_msgs/String name_0~%std_msgs/String name_180~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getCompletePanoramaGoal)))
  "Returns full string definition for message of type 'getCompletePanoramaGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%std_msgs/String folder_pano_path~%int32 images_number~%std_msgs/String name_0~%std_msgs/String name_180~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getCompletePanoramaGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'folder_pano_path))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'name_0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'name_180))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getCompletePanoramaGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'getCompletePanoramaGoal
    (cl:cons ':folder_pano_path (folder_pano_path msg))
    (cl:cons ':images_number (images_number msg))
    (cl:cons ':name_0 (name_0 msg))
    (cl:cons ':name_180 (name_180 msg))
))
