; Auto-generated. Do not edit!


(cl:in-package action_server_package-srv)


;//! \htmlinclude ChapaStorage-request.msg.html

(cl:defclass <ChapaStorage-request> (roslisp-msg-protocol:ros-message)
  ((id_chapa
    :reader id_chapa
    :initarg :id_chapa
    :type cl:integer
    :initform 0))
)

(cl:defclass ChapaStorage-request (<ChapaStorage-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ChapaStorage-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ChapaStorage-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-srv:<ChapaStorage-request> is deprecated: use action_server_package-srv:ChapaStorage-request instead.")))

(cl:ensure-generic-function 'id_chapa-val :lambda-list '(m))
(cl:defmethod id_chapa-val ((m <ChapaStorage-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:id_chapa-val is deprecated.  Use action_server_package-srv:id_chapa instead.")
  (id_chapa m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ChapaStorage-request>) ostream)
  "Serializes a message object of type '<ChapaStorage-request>"
  (cl:let* ((signed (cl:slot-value msg 'id_chapa)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ChapaStorage-request>) istream)
  "Deserializes a message object of type '<ChapaStorage-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_chapa) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ChapaStorage-request>)))
  "Returns string type for a service object of type '<ChapaStorage-request>"
  "action_server_package/ChapaStorageRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ChapaStorage-request)))
  "Returns string type for a service object of type 'ChapaStorage-request"
  "action_server_package/ChapaStorageRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ChapaStorage-request>)))
  "Returns md5sum for a message object of type '<ChapaStorage-request>"
  "d420ea154534426ff59c21556a0bdbf4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ChapaStorage-request)))
  "Returns md5sum for a message object of type 'ChapaStorage-request"
  "d420ea154534426ff59c21556a0bdbf4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ChapaStorage-request>)))
  "Returns full string definition for message of type '<ChapaStorage-request>"
  (cl:format cl:nil "int32 id_chapa~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ChapaStorage-request)))
  "Returns full string definition for message of type 'ChapaStorage-request"
  (cl:format cl:nil "int32 id_chapa~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ChapaStorage-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ChapaStorage-request>))
  "Converts a ROS message object to a list"
  (cl:list 'ChapaStorage-request
    (cl:cons ':id_chapa (id_chapa msg))
))
;//! \htmlinclude ChapaStorage-response.msg.html

(cl:defclass <ChapaStorage-response> (roslisp-msg-protocol:ros-message)
  ((long_chapa
    :reader long_chapa
    :initarg :long_chapa
    :type cl:float
    :initform 0.0)
   (width_chapa
    :reader width_chapa
    :initarg :width_chapa
    :type cl:float
    :initform 0.0)
   (coordA
    :reader coordA
    :initarg :coordA
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (coordB
    :reader coordB
    :initarg :coordB
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (coordC
    :reader coordC
    :initarg :coordC
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (coordD
    :reader coordD
    :initarg :coordD
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (number_of_chapas
    :reader number_of_chapas
    :initarg :number_of_chapas
    :type cl:integer
    :initform 0))
)

(cl:defclass ChapaStorage-response (<ChapaStorage-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ChapaStorage-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ChapaStorage-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-srv:<ChapaStorage-response> is deprecated: use action_server_package-srv:ChapaStorage-response instead.")))

(cl:ensure-generic-function 'long_chapa-val :lambda-list '(m))
(cl:defmethod long_chapa-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:long_chapa-val is deprecated.  Use action_server_package-srv:long_chapa instead.")
  (long_chapa m))

(cl:ensure-generic-function 'width_chapa-val :lambda-list '(m))
(cl:defmethod width_chapa-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:width_chapa-val is deprecated.  Use action_server_package-srv:width_chapa instead.")
  (width_chapa m))

(cl:ensure-generic-function 'coordA-val :lambda-list '(m))
(cl:defmethod coordA-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:coordA-val is deprecated.  Use action_server_package-srv:coordA instead.")
  (coordA m))

(cl:ensure-generic-function 'coordB-val :lambda-list '(m))
(cl:defmethod coordB-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:coordB-val is deprecated.  Use action_server_package-srv:coordB instead.")
  (coordB m))

(cl:ensure-generic-function 'coordC-val :lambda-list '(m))
(cl:defmethod coordC-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:coordC-val is deprecated.  Use action_server_package-srv:coordC instead.")
  (coordC m))

(cl:ensure-generic-function 'coordD-val :lambda-list '(m))
(cl:defmethod coordD-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:coordD-val is deprecated.  Use action_server_package-srv:coordD instead.")
  (coordD m))

(cl:ensure-generic-function 'number_of_chapas-val :lambda-list '(m))
(cl:defmethod number_of_chapas-val ((m <ChapaStorage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:number_of_chapas-val is deprecated.  Use action_server_package-srv:number_of_chapas instead.")
  (number_of_chapas m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ChapaStorage-response>) ostream)
  "Serializes a message object of type '<ChapaStorage-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'coordA) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'coordB) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'coordC) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'coordD) ostream)
  (cl:let* ((signed (cl:slot-value msg 'number_of_chapas)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ChapaStorage-response>) istream)
  "Deserializes a message object of type '<ChapaStorage-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_chapa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_chapa) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'coordA) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'coordB) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'coordC) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'coordD) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'number_of_chapas) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ChapaStorage-response>)))
  "Returns string type for a service object of type '<ChapaStorage-response>"
  "action_server_package/ChapaStorageResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ChapaStorage-response)))
  "Returns string type for a service object of type 'ChapaStorage-response"
  "action_server_package/ChapaStorageResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ChapaStorage-response>)))
  "Returns md5sum for a message object of type '<ChapaStorage-response>"
  "d420ea154534426ff59c21556a0bdbf4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ChapaStorage-response)))
  "Returns md5sum for a message object of type 'ChapaStorage-response"
  "d420ea154534426ff59c21556a0bdbf4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ChapaStorage-response>)))
  "Returns full string definition for message of type '<ChapaStorage-response>"
  (cl:format cl:nil "float32 long_chapa~%float32 width_chapa~%~%geometry_msgs/Point coordA~%geometry_msgs/Point coordB~%geometry_msgs/Point coordC~%geometry_msgs/Point coordD~%~%int32 number_of_chapas~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ChapaStorage-response)))
  "Returns full string definition for message of type 'ChapaStorage-response"
  (cl:format cl:nil "float32 long_chapa~%float32 width_chapa~%~%geometry_msgs/Point coordA~%geometry_msgs/Point coordB~%geometry_msgs/Point coordC~%geometry_msgs/Point coordD~%~%int32 number_of_chapas~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ChapaStorage-response>))
  (cl:+ 0
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'coordA))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'coordB))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'coordC))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'coordD))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ChapaStorage-response>))
  "Converts a ROS message object to a list"
  (cl:list 'ChapaStorage-response
    (cl:cons ':long_chapa (long_chapa msg))
    (cl:cons ':width_chapa (width_chapa msg))
    (cl:cons ':coordA (coordA msg))
    (cl:cons ':coordB (coordB msg))
    (cl:cons ':coordC (coordC msg))
    (cl:cons ':coordD (coordD msg))
    (cl:cons ':number_of_chapas (number_of_chapas msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'ChapaStorage)))
  'ChapaStorage-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'ChapaStorage)))
  'ChapaStorage-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ChapaStorage)))
  "Returns string type for a service object of type '<ChapaStorage>"
  "action_server_package/ChapaStorage")