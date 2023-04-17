; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-srv)


;//! \htmlinclude FCPP_out-request.msg.html

(cl:defclass <FCPP_out-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass FCPP_out-request (<FCPP_out-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_out-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_out-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<FCPP_out-request> is deprecated: use irobot_fcpp_simul-srv:FCPP_out-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_out-request>) ostream)
  "Serializes a message object of type '<FCPP_out-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FCPP_out-request>) istream)
  "Deserializes a message object of type '<FCPP_out-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_out-request>)))
  "Returns string type for a service object of type '<FCPP_out-request>"
  "irobot_fcpp_simul/FCPP_outRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_out-request)))
  "Returns string type for a service object of type 'FCPP_out-request"
  "irobot_fcpp_simul/FCPP_outRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_out-request>)))
  "Returns md5sum for a message object of type '<FCPP_out-request>"
  "30c6047a6867f6dfad71ccb5b3d8e613")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_out-request)))
  "Returns md5sum for a message object of type 'FCPP_out-request"
  "30c6047a6867f6dfad71ccb5b3d8e613")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_out-request>)))
  "Returns full string definition for message of type '<FCPP_out-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_out-request)))
  "Returns full string definition for message of type 'FCPP_out-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_out-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_out-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_out-request
))
;//! \htmlinclude FCPP_out-response.msg.html

(cl:defclass <FCPP_out-response> (roslisp-msg-protocol:ros-message)
  ((defecto_out
    :reader defecto_out
    :initarg :defecto_out
    :type (cl:vector irobot_fcpp_simul-msg:defecto)
   :initform (cl:make-array 0 :element-type 'irobot_fcpp_simul-msg:defecto :initial-element (cl:make-instance 'irobot_fcpp_simul-msg:defecto))))
)

(cl:defclass FCPP_out-response (<FCPP_out-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FCPP_out-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FCPP_out-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<FCPP_out-response> is deprecated: use irobot_fcpp_simul-srv:FCPP_out-response instead.")))

(cl:ensure-generic-function 'defecto_out-val :lambda-list '(m))
(cl:defmethod defecto_out-val ((m <FCPP_out-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:defecto_out-val is deprecated.  Use irobot_fcpp_simul-srv:defecto_out instead.")
  (defecto_out m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FCPP_out-response>) ostream)
  "Serializes a message object of type '<FCPP_out-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'defecto_out))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'defecto_out))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FCPP_out-response>) istream)
  "Deserializes a message object of type '<FCPP_out-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'defecto_out) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'defecto_out)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'irobot_fcpp_simul-msg:defecto))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FCPP_out-response>)))
  "Returns string type for a service object of type '<FCPP_out-response>"
  "irobot_fcpp_simul/FCPP_outResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_out-response)))
  "Returns string type for a service object of type 'FCPP_out-response"
  "irobot_fcpp_simul/FCPP_outResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FCPP_out-response>)))
  "Returns md5sum for a message object of type '<FCPP_out-response>"
  "30c6047a6867f6dfad71ccb5b3d8e613")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FCPP_out-response)))
  "Returns md5sum for a message object of type 'FCPP_out-response"
  "30c6047a6867f6dfad71ccb5b3d8e613")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FCPP_out-response>)))
  "Returns full string definition for message of type '<FCPP_out-response>"
  (cl:format cl:nil "defecto[] defecto_out~%~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto~%geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FCPP_out-response)))
  "Returns full string definition for message of type 'FCPP_out-response"
  (cl:format cl:nil "defecto[] defecto_out~%~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto~%geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FCPP_out-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'defecto_out) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FCPP_out-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FCPP_out-response
    (cl:cons ':defecto_out (defecto_out msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FCPP_out)))
  'FCPP_out-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FCPP_out)))
  'FCPP_out-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FCPP_out)))
  "Returns string type for a service object of type '<FCPP_out>"
  "irobot_fcpp_simul/FCPP_out")