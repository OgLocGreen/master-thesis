; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude defecto_simple.msg.html

(cl:defclass <defecto_simple> (roslisp-msg-protocol:ros-message)
  ((ros_poly
    :reader ros_poly
    :initarg :ros_poly
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (direccion_rep
    :reader direccion_rep
    :initarg :direccion_rep
    :type cl:integer
    :initform 0)
   (reparado
    :reader reparado
    :initarg :reparado
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass defecto_simple (<defecto_simple>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <defecto_simple>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'defecto_simple)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<defecto_simple> is deprecated: use irobot_fcpp_simul-msg:defecto_simple instead.")))

(cl:ensure-generic-function 'ros_poly-val :lambda-list '(m))
(cl:defmethod ros_poly-val ((m <defecto_simple>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:ros_poly-val is deprecated.  Use irobot_fcpp_simul-msg:ros_poly instead.")
  (ros_poly m))

(cl:ensure-generic-function 'direccion_rep-val :lambda-list '(m))
(cl:defmethod direccion_rep-val ((m <defecto_simple>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:direccion_rep-val is deprecated.  Use irobot_fcpp_simul-msg:direccion_rep instead.")
  (direccion_rep m))

(cl:ensure-generic-function 'reparado-val :lambda-list '(m))
(cl:defmethod reparado-val ((m <defecto_simple>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:reparado-val is deprecated.  Use irobot_fcpp_simul-msg:reparado instead.")
  (reparado m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <defecto_simple>) ostream)
  "Serializes a message object of type '<defecto_simple>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ros_poly) ostream)
  (cl:let* ((signed (cl:slot-value msg 'direccion_rep)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'reparado) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <defecto_simple>) istream)
  "Deserializes a message object of type '<defecto_simple>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ros_poly) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direccion_rep) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'reparado) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<defecto_simple>)))
  "Returns string type for a message object of type '<defecto_simple>"
  "irobot_fcpp_simul/defecto_simple")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'defecto_simple)))
  "Returns string type for a message object of type 'defecto_simple"
  "irobot_fcpp_simul/defecto_simple")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<defecto_simple>)))
  "Returns md5sum for a message object of type '<defecto_simple>"
  "9e9103e825e653e77fe6292f6a6f8a76")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'defecto_simple)))
  "Returns md5sum for a message object of type 'defecto_simple"
  "9e9103e825e653e77fe6292f6a6f8a76")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<defecto_simple>)))
  "Returns full string definition for message of type '<defecto_simple>"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'defecto_simple)))
  "Returns full string definition for message of type 'defecto_simple"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <defecto_simple>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ros_poly))
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <defecto_simple>))
  "Converts a ROS message object to a list"
  (cl:list 'defecto_simple
    (cl:cons ':ros_poly (ros_poly msg))
    (cl:cons ':direccion_rep (direccion_rep msg))
    (cl:cons ':reparado (reparado msg))
))
