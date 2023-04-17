; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude defecto.msg.html

(cl:defclass <defecto> (roslisp-msg-protocol:ros-message)
  ((ros_poly
    :reader ros_poly
    :initarg :ros_poly
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (defecto_divpor_zonas
    :reader defecto_divpor_zonas
    :initarg :defecto_divpor_zonas
    :type (cl:vector irobot_fcpp_simul-msg:defecto_zona)
   :initform (cl:make-array 0 :element-type 'irobot_fcpp_simul-msg:defecto_zona :initial-element (cl:make-instance 'irobot_fcpp_simul-msg:defecto_zona)))
   (reparado
    :reader reparado
    :initarg :reparado
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass defecto (<defecto>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <defecto>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'defecto)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<defecto> is deprecated: use irobot_fcpp_simul-msg:defecto instead.")))

(cl:ensure-generic-function 'ros_poly-val :lambda-list '(m))
(cl:defmethod ros_poly-val ((m <defecto>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:ros_poly-val is deprecated.  Use irobot_fcpp_simul-msg:ros_poly instead.")
  (ros_poly m))

(cl:ensure-generic-function 'defecto_divpor_zonas-val :lambda-list '(m))
(cl:defmethod defecto_divpor_zonas-val ((m <defecto>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:defecto_divpor_zonas-val is deprecated.  Use irobot_fcpp_simul-msg:defecto_divpor_zonas instead.")
  (defecto_divpor_zonas m))

(cl:ensure-generic-function 'reparado-val :lambda-list '(m))
(cl:defmethod reparado-val ((m <defecto>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:reparado-val is deprecated.  Use irobot_fcpp_simul-msg:reparado instead.")
  (reparado m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <defecto>) ostream)
  "Serializes a message object of type '<defecto>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ros_poly) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'defecto_divpor_zonas))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'defecto_divpor_zonas))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'reparado) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <defecto>) istream)
  "Deserializes a message object of type '<defecto>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ros_poly) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'defecto_divpor_zonas) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'defecto_divpor_zonas)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'irobot_fcpp_simul-msg:defecto_zona))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:slot-value msg 'reparado) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<defecto>)))
  "Returns string type for a message object of type '<defecto>"
  "irobot_fcpp_simul/defecto")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'defecto)))
  "Returns string type for a message object of type 'defecto"
  "irobot_fcpp_simul/defecto")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<defecto>)))
  "Returns md5sum for a message object of type '<defecto>"
  "6f4dca0cbac38a321305ee29edd2c608")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'defecto)))
  "Returns md5sum for a message object of type 'defecto"
  "6f4dca0cbac38a321305ee29edd2c608")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<defecto>)))
  "Returns full string definition for message of type '<defecto>"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'defecto)))
  "Returns full string definition for message of type 'defecto"
  (cl:format cl:nil "geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <defecto>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ros_poly))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'defecto_divpor_zonas) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <defecto>))
  "Converts a ROS message object to a list"
  (cl:list 'defecto
    (cl:cons ':ros_poly (ros_poly msg))
    (cl:cons ':defecto_divpor_zonas (defecto_divpor_zonas msg))
    (cl:cons ':reparado (reparado msg))
))
