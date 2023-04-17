; Auto-generated. Do not edit!


(cl:in-package action_server_package-srv)


;//! \htmlinclude FCPP_in-request.msg.html

(cl:defclass <FCPP_in-request> (roslisp-msg-protocol:ros-message)
  ((id_input
    :reader id_input
    :initarg :id_input
    :type cl:integer
    :initform 0))
)

(cl:defclass FCPP_in-request (<FCPP_in-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_in-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_in-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-srv:<FCPP_in-request> is deprecated: use action_server_package-srv:FCPP_in-request instead.")))

(cl:ensure-generic-function 'id_input-val :lambda-list '(m))
(cl:defmethod id_input-val ((m <FCPP_in-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:id_input-val is deprecated.  Use action_server_package-srv:id_input instead.")
  (id_input m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_in-request>) ostream)
  "Serializes a message object of type '<FCPP_in-request>"
  (cl:let* ((signed (cl:slot-value msg 'id_input)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FCPP_in-request>) istream)
  "Deserializes a message object of type '<FCPP_in-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_input) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_in-request>)))
  "Returns string type for a service object of type '<FCPP_in-request>"
  "action_server_package/FCPP_inRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in-request)))
  "Returns string type for a service object of type 'FCPP_in-request"
  "action_server_package/FCPP_inRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_in-request>)))
  "Returns md5sum for a message object of type '<FCPP_in-request>"
  "3a9946ec5195dc8fb4f14eeb6ec2e339")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_in-request)))
  "Returns md5sum for a message object of type 'FCPP_in-request"
  "3a9946ec5195dc8fb4f14eeb6ec2e339")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_in-request>)))
  "Returns full string definition for message of type '<FCPP_in-request>"
  (cl:format cl:nil "int32 id_input~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_in-request)))
  "Returns full string definition for message of type 'FCPP_in-request"
  (cl:format cl:nil "int32 id_input~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_in-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_in-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_in-request
    (cl:cons ':id_input (id_input msg))
))
;//! \htmlinclude FCPP_in-response.msg.html

(cl:defclass <FCPP_in-response> (roslisp-msg-protocol:ros-message)
  ((n_defects
    :reader n_defects
    :initarg :n_defects
    :type cl:integer
    :initform 0)
   (xmin_chapa
    :reader xmin_chapa
    :initarg :xmin_chapa
    :type cl:float
    :initform 0.0)
   (xmax_chapa
    :reader xmax_chapa
    :initarg :xmax_chapa
    :type cl:float
    :initform 0.0)
   (ymin_chapa
    :reader ymin_chapa
    :initarg :ymin_chapa
    :type cl:float
    :initform 0.0)
   (ymax_chapa
    :reader ymax_chapa
    :initarg :ymax_chapa
    :type cl:float
    :initform 0.0)
   (poly_i
    :reader poly_i
    :initarg :poly_i
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (number_of_chapas
    :reader number_of_chapas
    :initarg :number_of_chapas
    :type cl:integer
    :initform 0))
)

(cl:defclass FCPP_in-response (<FCPP_in-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_in-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_in-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server_package-srv:<FCPP_in-response> is deprecated: use action_server_package-srv:FCPP_in-response instead.")))

(cl:ensure-generic-function 'n_defects-val :lambda-list '(m))
(cl:defmethod n_defects-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:n_defects-val is deprecated.  Use action_server_package-srv:n_defects instead.")
  (n_defects m))

(cl:ensure-generic-function 'xmin_chapa-val :lambda-list '(m))
(cl:defmethod xmin_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:xmin_chapa-val is deprecated.  Use action_server_package-srv:xmin_chapa instead.")
  (xmin_chapa m))

(cl:ensure-generic-function 'xmax_chapa-val :lambda-list '(m))
(cl:defmethod xmax_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:xmax_chapa-val is deprecated.  Use action_server_package-srv:xmax_chapa instead.")
  (xmax_chapa m))

(cl:ensure-generic-function 'ymin_chapa-val :lambda-list '(m))
(cl:defmethod ymin_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:ymin_chapa-val is deprecated.  Use action_server_package-srv:ymin_chapa instead.")
  (ymin_chapa m))

(cl:ensure-generic-function 'ymax_chapa-val :lambda-list '(m))
(cl:defmethod ymax_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:ymax_chapa-val is deprecated.  Use action_server_package-srv:ymax_chapa instead.")
  (ymax_chapa m))

(cl:ensure-generic-function 'poly_i-val :lambda-list '(m))
(cl:defmethod poly_i-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:poly_i-val is deprecated.  Use action_server_package-srv:poly_i instead.")
  (poly_i m))

(cl:ensure-generic-function 'number_of_chapas-val :lambda-list '(m))
(cl:defmethod number_of_chapas-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server_package-srv:number_of_chapas-val is deprecated.  Use action_server_package-srv:number_of_chapas instead.")
  (number_of_chapas m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_in-response>) ostream)
  "Serializes a message object of type '<FCPP_in-response>"
  (cl:let* ((signed (cl:slot-value msg 'n_defects)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xmin_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xmax_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ymin_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ymax_chapa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'poly_i) ostream)
  (cl:let* ((signed (cl:slot-value msg 'number_of_chapas)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FCPP_in-response>) istream)
  "Deserializes a message object of type '<FCPP_in-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_defects) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xmin_chapa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xmax_chapa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ymin_chapa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ymax_chapa) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'poly_i) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'number_of_chapas) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_in-response>)))
  "Returns string type for a service object of type '<FCPP_in-response>"
  "action_server_package/FCPP_inResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in-response)))
  "Returns string type for a service object of type 'FCPP_in-response"
  "action_server_package/FCPP_inResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_in-response>)))
  "Returns md5sum for a message object of type '<FCPP_in-response>"
  "3a9946ec5195dc8fb4f14eeb6ec2e339")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_in-response)))
  "Returns md5sum for a message object of type 'FCPP_in-response"
  "3a9946ec5195dc8fb4f14eeb6ec2e339")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_in-response>)))
  "Returns full string definition for message of type '<FCPP_in-response>"
  (cl:format cl:nil "int32 n_defects~%~%float32 xmin_chapa~%float32 xmax_chapa~%float32 ymin_chapa~%float32 ymax_chapa~%~%geometry_msgs/Polygon poly_i~%~%int32 number_of_chapas~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_in-response)))
  "Returns full string definition for message of type 'FCPP_in-response"
  (cl:format cl:nil "int32 n_defects~%~%float32 xmin_chapa~%float32 xmax_chapa~%float32 ymin_chapa~%float32 ymax_chapa~%~%geometry_msgs/Polygon poly_i~%~%int32 number_of_chapas~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_in-response>))
  (cl:+ 0
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'poly_i))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_in-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_in-response
    (cl:cons ':n_defects (n_defects msg))
    (cl:cons ':xmin_chapa (xmin_chapa msg))
    (cl:cons ':xmax_chapa (xmax_chapa msg))
    (cl:cons ':ymin_chapa (ymin_chapa msg))
    (cl:cons ':ymax_chapa (ymax_chapa msg))
    (cl:cons ':poly_i (poly_i msg))
    (cl:cons ':number_of_chapas (number_of_chapas msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FCPP_in)))
  'FCPP_in-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FCPP_in)))
  'FCPP_in-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in)))
  "Returns string type for a service object of type '<FCPP_in>"
  "action_server_package/FCPP_in")