; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-srv)


;//! \htmlinclude FCPP_in-request.msg.html

(cl:defclass <FCPP_in-request> (roslisp-msg-protocol:ros-message)
  ((id_input
    :reader id_input
    :initarg :id_input
    :type cl:integer
    :initform 0)
   (get_working_zones
    :reader get_working_zones
    :initarg :get_working_zones
    :type cl:boolean
    :initform cl:nil)
   (get_inspection_zones
    :reader get_inspection_zones
    :initarg :get_inspection_zones
    :type cl:boolean
    :initform cl:nil)
   (get_rot_zone
    :reader get_rot_zone
    :initarg :get_rot_zone
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass FCPP_in-request (<FCPP_in-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_in-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_in-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<FCPP_in-request> is deprecated: use irobot_fcpp_simul-srv:FCPP_in-request instead.")))

(cl:ensure-generic-function 'id_input-val :lambda-list '(m))
(cl:defmethod id_input-val ((m <FCPP_in-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:id_input-val is deprecated.  Use irobot_fcpp_simul-srv:id_input instead.")
  (id_input m))

(cl:ensure-generic-function 'get_working_zones-val :lambda-list '(m))
(cl:defmethod get_working_zones-val ((m <FCPP_in-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_working_zones-val is deprecated.  Use irobot_fcpp_simul-srv:get_working_zones instead.")
  (get_working_zones m))

(cl:ensure-generic-function 'get_inspection_zones-val :lambda-list '(m))
(cl:defmethod get_inspection_zones-val ((m <FCPP_in-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_inspection_zones-val is deprecated.  Use irobot_fcpp_simul-srv:get_inspection_zones instead.")
  (get_inspection_zones m))

(cl:ensure-generic-function 'get_rot_zone-val :lambda-list '(m))
(cl:defmethod get_rot_zone-val ((m <FCPP_in-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_rot_zone-val is deprecated.  Use irobot_fcpp_simul-srv:get_rot_zone instead.")
  (get_rot_zone m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_in-request>) ostream)
  "Serializes a message object of type '<FCPP_in-request>"
  (cl:let* ((signed (cl:slot-value msg 'id_input)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_working_zones) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_inspection_zones) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_rot_zone) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FCPP_in-request>) istream)
  "Deserializes a message object of type '<FCPP_in-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_input) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'get_working_zones) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_inspection_zones) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_rot_zone) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_in-request>)))
  "Returns string type for a service object of type '<FCPP_in-request>"
  "irobot_fcpp_simul/FCPP_inRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in-request)))
  "Returns string type for a service object of type 'FCPP_in-request"
  "irobot_fcpp_simul/FCPP_inRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_in-request>)))
  "Returns md5sum for a message object of type '<FCPP_in-request>"
  "26aa20be26a641c44400aa9da8ffcd13")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_in-request)))
  "Returns md5sum for a message object of type 'FCPP_in-request"
  "26aa20be26a641c44400aa9da8ffcd13")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_in-request>)))
  "Returns full string definition for message of type '<FCPP_in-request>"
  (cl:format cl:nil "int32 id_input~%bool get_working_zones~%bool get_inspection_zones~%bool get_rot_zone~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_in-request)))
  "Returns full string definition for message of type 'FCPP_in-request"
  (cl:format cl:nil "int32 id_input~%bool get_working_zones~%bool get_inspection_zones~%bool get_rot_zone~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_in-request>))
  (cl:+ 0
     4
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_in-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_in-request
    (cl:cons ':id_input (id_input msg))
    (cl:cons ':get_working_zones (get_working_zones msg))
    (cl:cons ':get_inspection_zones (get_inspection_zones msg))
    (cl:cons ':get_rot_zone (get_rot_zone msg))
))
;//! \htmlinclude FCPP_in-response.msg.html

(cl:defclass <FCPP_in-response> (roslisp-msg-protocol:ros-message)
  ((n_defects
    :reader n_defects
    :initarg :n_defects
    :type cl:integer
    :initform 0)
   (herr_lat
    :reader herr_lat
    :initarg :herr_lat
    :type cl:float
    :initform 0.0)
   (herr_proa
    :reader herr_proa
    :initarg :herr_proa
    :type cl:float
    :initform 0.0)
   (herr_popa
    :reader herr_popa
    :initarg :herr_popa
    :type cl:float
    :initform 0.0)
   (long_robotx
    :reader long_robotx
    :initarg :long_robotx
    :type cl:float
    :initform 0.0)
   (long_roboty
    :reader long_roboty
    :initarg :long_roboty
    :type cl:float
    :initform 0.0)
   (tras_herrx
    :reader tras_herrx
    :initarg :tras_herrx
    :type cl:float
    :initform 0.0)
   (tras_herry
    :reader tras_herry
    :initarg :tras_herry
    :type cl:float
    :initform 0.0)
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
   (zone0
    :reader zone0
    :initarg :zone0
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zone90
    :reader zone90
    :initarg :zone90
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zone180
    :reader zone180
    :initarg :zone180
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zone270
    :reader zone270
    :initarg :zone270
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zone_rot
    :reader zone_rot
    :initarg :zone_rot
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon)))
)

(cl:defclass FCPP_in-response (<FCPP_in-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_in-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_in-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<FCPP_in-response> is deprecated: use irobot_fcpp_simul-srv:FCPP_in-response instead.")))

(cl:ensure-generic-function 'n_defects-val :lambda-list '(m))
(cl:defmethod n_defects-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:n_defects-val is deprecated.  Use irobot_fcpp_simul-srv:n_defects instead.")
  (n_defects m))

(cl:ensure-generic-function 'herr_lat-val :lambda-list '(m))
(cl:defmethod herr_lat-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:herr_lat-val is deprecated.  Use irobot_fcpp_simul-srv:herr_lat instead.")
  (herr_lat m))

(cl:ensure-generic-function 'herr_proa-val :lambda-list '(m))
(cl:defmethod herr_proa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:herr_proa-val is deprecated.  Use irobot_fcpp_simul-srv:herr_proa instead.")
  (herr_proa m))

(cl:ensure-generic-function 'herr_popa-val :lambda-list '(m))
(cl:defmethod herr_popa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:herr_popa-val is deprecated.  Use irobot_fcpp_simul-srv:herr_popa instead.")
  (herr_popa m))

(cl:ensure-generic-function 'long_robotx-val :lambda-list '(m))
(cl:defmethod long_robotx-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_robotx-val is deprecated.  Use irobot_fcpp_simul-srv:long_robotx instead.")
  (long_robotx m))

(cl:ensure-generic-function 'long_roboty-val :lambda-list '(m))
(cl:defmethod long_roboty-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_roboty-val is deprecated.  Use irobot_fcpp_simul-srv:long_roboty instead.")
  (long_roboty m))

(cl:ensure-generic-function 'tras_herrx-val :lambda-list '(m))
(cl:defmethod tras_herrx-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herrx-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herrx instead.")
  (tras_herrx m))

(cl:ensure-generic-function 'tras_herry-val :lambda-list '(m))
(cl:defmethod tras_herry-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herry-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herry instead.")
  (tras_herry m))

(cl:ensure-generic-function 'xmin_chapa-val :lambda-list '(m))
(cl:defmethod xmin_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:xmin_chapa-val is deprecated.  Use irobot_fcpp_simul-srv:xmin_chapa instead.")
  (xmin_chapa m))

(cl:ensure-generic-function 'xmax_chapa-val :lambda-list '(m))
(cl:defmethod xmax_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:xmax_chapa-val is deprecated.  Use irobot_fcpp_simul-srv:xmax_chapa instead.")
  (xmax_chapa m))

(cl:ensure-generic-function 'ymin_chapa-val :lambda-list '(m))
(cl:defmethod ymin_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:ymin_chapa-val is deprecated.  Use irobot_fcpp_simul-srv:ymin_chapa instead.")
  (ymin_chapa m))

(cl:ensure-generic-function 'ymax_chapa-val :lambda-list '(m))
(cl:defmethod ymax_chapa-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:ymax_chapa-val is deprecated.  Use irobot_fcpp_simul-srv:ymax_chapa instead.")
  (ymax_chapa m))

(cl:ensure-generic-function 'poly_i-val :lambda-list '(m))
(cl:defmethod poly_i-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:poly_i-val is deprecated.  Use irobot_fcpp_simul-srv:poly_i instead.")
  (poly_i m))

(cl:ensure-generic-function 'zone0-val :lambda-list '(m))
(cl:defmethod zone0-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone0-val is deprecated.  Use irobot_fcpp_simul-srv:zone0 instead.")
  (zone0 m))

(cl:ensure-generic-function 'zone90-val :lambda-list '(m))
(cl:defmethod zone90-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone90-val is deprecated.  Use irobot_fcpp_simul-srv:zone90 instead.")
  (zone90 m))

(cl:ensure-generic-function 'zone180-val :lambda-list '(m))
(cl:defmethod zone180-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone180-val is deprecated.  Use irobot_fcpp_simul-srv:zone180 instead.")
  (zone180 m))

(cl:ensure-generic-function 'zone270-val :lambda-list '(m))
(cl:defmethod zone270-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone270-val is deprecated.  Use irobot_fcpp_simul-srv:zone270 instead.")
  (zone270 m))

(cl:ensure-generic-function 'zone_rot-val :lambda-list '(m))
(cl:defmethod zone_rot-val ((m <FCPP_in-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone_rot-val is deprecated.  Use irobot_fcpp_simul-srv:zone_rot instead.")
  (zone_rot m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_in-response>) ostream)
  "Serializes a message object of type '<FCPP_in-response>"
  (cl:let* ((signed (cl:slot-value msg 'n_defects)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'herr_lat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'herr_proa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'herr_popa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_robotx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_roboty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herrx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone90) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone180) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone270) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone_rot) ostream)
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
    (cl:setf (cl:slot-value msg 'herr_lat) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'herr_proa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'herr_popa) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_robotx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_roboty) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herrx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herry) (roslisp-utils:decode-single-float-bits bits)))
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
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone90) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone180) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone270) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone_rot) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_in-response>)))
  "Returns string type for a service object of type '<FCPP_in-response>"
  "irobot_fcpp_simul/FCPP_inResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in-response)))
  "Returns string type for a service object of type 'FCPP_in-response"
  "irobot_fcpp_simul/FCPP_inResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_in-response>)))
  "Returns md5sum for a message object of type '<FCPP_in-response>"
  "26aa20be26a641c44400aa9da8ffcd13")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_in-response)))
  "Returns md5sum for a message object of type 'FCPP_in-response"
  "26aa20be26a641c44400aa9da8ffcd13")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_in-response>)))
  "Returns full string definition for message of type '<FCPP_in-response>"
  (cl:format cl:nil "~%int32 n_defects~%~%~%float32 herr_lat~%float32 herr_proa~%float32 herr_popa~%~%~%float32 long_robotx~%float32 long_roboty~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 xmin_chapa~%float32 xmax_chapa~%float32 ymin_chapa~%float32 ymax_chapa~%~%~%geometry_msgs/Polygon poly_i~%~%~%geometry_msgs/Polygon zone0~%geometry_msgs/Polygon zone90~%geometry_msgs/Polygon zone180~%geometry_msgs/Polygon zone270~%~%~%~%geometry_msgs/Polygon zone_rot~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_in-response)))
  "Returns full string definition for message of type 'FCPP_in-response"
  (cl:format cl:nil "~%int32 n_defects~%~%~%float32 herr_lat~%float32 herr_proa~%float32 herr_popa~%~%~%float32 long_robotx~%float32 long_roboty~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 xmin_chapa~%float32 xmax_chapa~%float32 ymin_chapa~%float32 ymax_chapa~%~%~%geometry_msgs/Polygon poly_i~%~%~%geometry_msgs/Polygon zone0~%geometry_msgs/Polygon zone90~%geometry_msgs/Polygon zone180~%geometry_msgs/Polygon zone270~%~%~%~%geometry_msgs/Polygon zone_rot~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_in-response>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'poly_i))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone90))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone180))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone270))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone_rot))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_in-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_in-response
    (cl:cons ':n_defects (n_defects msg))
    (cl:cons ':herr_lat (herr_lat msg))
    (cl:cons ':herr_proa (herr_proa msg))
    (cl:cons ':herr_popa (herr_popa msg))
    (cl:cons ':long_robotx (long_robotx msg))
    (cl:cons ':long_roboty (long_roboty msg))
    (cl:cons ':tras_herrx (tras_herrx msg))
    (cl:cons ':tras_herry (tras_herry msg))
    (cl:cons ':xmin_chapa (xmin_chapa msg))
    (cl:cons ':xmax_chapa (xmax_chapa msg))
    (cl:cons ':ymin_chapa (ymin_chapa msg))
    (cl:cons ':ymax_chapa (ymax_chapa msg))
    (cl:cons ':poly_i (poly_i msg))
    (cl:cons ':zone0 (zone0 msg))
    (cl:cons ':zone90 (zone90 msg))
    (cl:cons ':zone180 (zone180 msg))
    (cl:cons ':zone270 (zone270 msg))
    (cl:cons ':zone_rot (zone_rot msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FCPP_in)))
  'FCPP_in-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FCPP_in)))
  'FCPP_in-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_in)))
  "Returns string type for a service object of type '<FCPP_in>"
  "irobot_fcpp_simul/FCPP_in")