; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-msg)


;//! \htmlinclude ComputeDefectsDecompGoal.msg.html

(cl:defclass <ComputeDefectsDecompGoal> (roslisp-msg-protocol:ros-message)
  ((chapa_id
    :reader chapa_id
    :initarg :chapa_id
    :type cl:integer
    :initform 0)
   (poly_defect
    :reader poly_defect
    :initarg :poly_defect
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
   (xmax
    :reader xmax
    :initarg :xmax
    :type cl:float
    :initform 0.0)
   (ymax
    :reader ymax
    :initarg :ymax
    :type cl:float
    :initform 0.0))
)

(cl:defclass ComputeDefectsDecompGoal (<ComputeDefectsDecompGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ComputeDefectsDecompGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ComputeDefectsDecompGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-msg:<ComputeDefectsDecompGoal> is deprecated: use irobot_fcpp_simul-msg:ComputeDefectsDecompGoal instead.")))

(cl:ensure-generic-function 'chapa_id-val :lambda-list '(m))
(cl:defmethod chapa_id-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:chapa_id-val is deprecated.  Use irobot_fcpp_simul-msg:chapa_id instead.")
  (chapa_id m))

(cl:ensure-generic-function 'poly_defect-val :lambda-list '(m))
(cl:defmethod poly_defect-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:poly_defect-val is deprecated.  Use irobot_fcpp_simul-msg:poly_defect instead.")
  (poly_defect m))

(cl:ensure-generic-function 'zone0-val :lambda-list '(m))
(cl:defmethod zone0-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:zone0-val is deprecated.  Use irobot_fcpp_simul-msg:zone0 instead.")
  (zone0 m))

(cl:ensure-generic-function 'zone90-val :lambda-list '(m))
(cl:defmethod zone90-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:zone90-val is deprecated.  Use irobot_fcpp_simul-msg:zone90 instead.")
  (zone90 m))

(cl:ensure-generic-function 'zone180-val :lambda-list '(m))
(cl:defmethod zone180-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:zone180-val is deprecated.  Use irobot_fcpp_simul-msg:zone180 instead.")
  (zone180 m))

(cl:ensure-generic-function 'zone270-val :lambda-list '(m))
(cl:defmethod zone270-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:zone270-val is deprecated.  Use irobot_fcpp_simul-msg:zone270 instead.")
  (zone270 m))

(cl:ensure-generic-function 'xmax-val :lambda-list '(m))
(cl:defmethod xmax-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:xmax-val is deprecated.  Use irobot_fcpp_simul-msg:xmax instead.")
  (xmax m))

(cl:ensure-generic-function 'ymax-val :lambda-list '(m))
(cl:defmethod ymax-val ((m <ComputeDefectsDecompGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-msg:ymax-val is deprecated.  Use irobot_fcpp_simul-msg:ymax instead.")
  (ymax m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ComputeDefectsDecompGoal>) ostream)
  "Serializes a message object of type '<ComputeDefectsDecompGoal>"
  (cl:let* ((signed (cl:slot-value msg 'chapa_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'poly_defect) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone90) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone180) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone270) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xmax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ymax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ComputeDefectsDecompGoal>) istream)
  "Deserializes a message object of type '<ComputeDefectsDecompGoal>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'chapa_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'poly_defect) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone90) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone180) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone270) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xmax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ymax) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ComputeDefectsDecompGoal>)))
  "Returns string type for a message object of type '<ComputeDefectsDecompGoal>"
  "irobot_fcpp_simul/ComputeDefectsDecompGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ComputeDefectsDecompGoal)))
  "Returns string type for a message object of type 'ComputeDefectsDecompGoal"
  "irobot_fcpp_simul/ComputeDefectsDecompGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ComputeDefectsDecompGoal>)))
  "Returns md5sum for a message object of type '<ComputeDefectsDecompGoal>"
  "100a9f9d0c5c91d1ec171cccc3fdc2c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ComputeDefectsDecompGoal)))
  "Returns md5sum for a message object of type 'ComputeDefectsDecompGoal"
  "100a9f9d0c5c91d1ec171cccc3fdc2c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ComputeDefectsDecompGoal>)))
  "Returns full string definition for message of type '<ComputeDefectsDecompGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%int32 chapa_id~%~%geometry_msgs/Polygon poly_defect~%~%~%geometry_msgs/Polygon zone0~%geometry_msgs/Polygon zone90~%geometry_msgs/Polygon zone180~%geometry_msgs/Polygon zone270~%~%float32 xmax~%float32 ymax~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ComputeDefectsDecompGoal)))
  "Returns full string definition for message of type 'ComputeDefectsDecompGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%int32 chapa_id~%~%geometry_msgs/Polygon poly_defect~%~%~%geometry_msgs/Polygon zone0~%geometry_msgs/Polygon zone90~%geometry_msgs/Polygon zone180~%geometry_msgs/Polygon zone270~%~%float32 xmax~%float32 ymax~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ComputeDefectsDecompGoal>))
  (cl:+ 0
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'poly_defect))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone90))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone180))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone270))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ComputeDefectsDecompGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'ComputeDefectsDecompGoal
    (cl:cons ':chapa_id (chapa_id msg))
    (cl:cons ':poly_defect (poly_defect msg))
    (cl:cons ':zone0 (zone0 msg))
    (cl:cons ':zone90 (zone90 msg))
    (cl:cons ':zone180 (zone180 msg))
    (cl:cons ':zone270 (zone270 msg))
    (cl:cons ':xmax (xmax msg))
    (cl:cons ':ymax (ymax msg))
))
