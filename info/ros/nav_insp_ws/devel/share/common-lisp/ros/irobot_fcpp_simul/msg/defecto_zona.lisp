; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude defecto_zona.msg.html

(cl:defclass <defecto_zona> (roslisp-msg-protocol:ros-message)
  ((ros_poly
    :reader ros_poly
    :initarg :ros_poly
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (trap_vec
    :reader trap_vec
    :initarg :trap_vec
    :type (cl:vector irobot_fcpp_simul-msg:defecto_simple)
   :initform (cl:make-array 0 :element-type 'irobot_fcpp_simul-msg:defecto_simple :initial-element (cl:make-instance 'irobot_fcpp_simul-msg:defecto_simple)))
   (direccion_rep
    :reader direccion_rep
    :initarg :direccion_rep
    :type cl:integer
    :initform 0)
   (reparado
    :reader reparado
    :initarg :reparado
    :type cl:boolean
    :initform cl:nil)
   (zona
    :reader zona
    :initarg :zona
    :type cl:integer
    :initform 0))
)

(cl:defclass defecto_zona (<defecto_zona>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <defecto_zona>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'defecto_zona)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<defecto_zona> is deprecated: use irobot_fcpp_simul-msg:defecto_zona instead.")))

(cl:ensure-generic-function 'ros_poly-val :lambda-list '(m))
(cl:defmethod ros_poly-val ((m <defecto_zona>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:ros_poly-val is deprecated.  Use irobot_fcpp_simul-msg:ros_poly instead.")
  (ros_poly m))

(cl:ensure-generic-function 'trap_vec-val :lambda-list '(m))
(cl:defmethod trap_vec-val ((m <defecto_zona>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:trap_vec-val is deprecated.  Use irobot_fcpp_simul-msg:trap_vec instead.")
  (trap_vec m))

(cl:ensure-generic-function 'direccion_rep-val :lambda-list '(m))
(cl:defmethod direccion_rep-val ((m <defecto_zona>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:direccion_rep-val is deprecated.  Use irobot_fcpp_simul-msg:direccion_rep instead.")
  (direccion_rep m))

(cl:ensure-generic-function 'reparado-val :lambda-list '(m))
(cl:defmethod reparado-val ((m <defecto_zona>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:reparado-val is deprecated.  Use irobot_fcpp_simul-msg:reparado instead.")
  (reparado m))

(cl:ensure-generic-function 'zona-val :lambda-list '(m))
(cl:defmethod zona-val ((m <defecto_zona>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:zona-val is deprecated.  Use irobot_fcpp_simul-msg:zona instead.")
  (zona m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <defecto_zona>) ostream)
  "Serializes a message object of type '<defecto_zona>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ros_poly) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'trap_vec))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'trap_vec))
  (cl:let* ((signed (cl:slot-value msg 'direccion_rep)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'reparado) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'zona)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <defecto_zona>) istream)
  "Deserializes a message object of type '<defecto_zona>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ros_poly) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'trap_vec) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'trap_vec)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'irobot_fcpp_simul-msg:defecto_simple))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direccion_rep) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'reparado) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'zona) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<defecto_zona>)))
  "Returns string type for a message object of type '<defecto_zona>"
  "irobot_fcpp_simul/defecto_zona")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'defecto_zona)))
  "Returns string type for a message object of type 'defecto_zona"
  "irobot_fcpp_simul/defecto_zona")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<defecto_zona>)))
  "Returns md5sum for a message object of type '<defecto_zona>"
  "66d6ef707c05e8c8eaa69b175e897e44")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'defecto_zona)))
  "Returns md5sum for a message object of type 'defecto_zona"
  "66d6ef707c05e8c8eaa69b175e897e44")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<defecto_zona>)))
  "Returns full string definition for message of type '<defecto_zona>"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'defecto_zona)))
  "Returns full string definition for message of type 'defecto_zona"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <defecto_zona>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ros_poly))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'trap_vec) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <defecto_zona>))
  "Converts a ROS message object to a list"
  (cl:list 'defecto_zona
    (cl:cons ':ros_poly (ros_poly msg))
    (cl:cons ':trap_vec (trap_vec msg))
    (cl:cons ':direccion_rep (direccion_rep msg))
    (cl:cons ':reparado (reparado msg))
    (cl:cons ':zona (zona msg))
))
