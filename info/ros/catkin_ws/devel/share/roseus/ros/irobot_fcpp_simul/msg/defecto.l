;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::defecto)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'defecto (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::DEFECTO")
  (make-package "IROBOT_FCPP_SIMUL::DEFECTO"))

(in-package "ROS")
;;//! \htmlinclude defecto.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::defecto
  :super ros::object
  :slots (_ros_poly _defecto_divpor_zonas _reparado ))

(defmethod irobot_fcpp_simul::defecto
  (:init
   (&key
    ((:ros_poly __ros_poly) (instance geometry_msgs::Polygon :init))
    ((:defecto_divpor_zonas __defecto_divpor_zonas) (let (r) (dotimes (i 0) (push (instance irobot_fcpp_simul::defecto_zona :init) r)) r))
    ((:reparado __reparado) nil)
    )
   (send-super :init)
   (setq _ros_poly __ros_poly)
   (setq _defecto_divpor_zonas __defecto_divpor_zonas)
   (setq _reparado __reparado)
   self)
  (:ros_poly
   (&rest __ros_poly)
   (if (keywordp (car __ros_poly))
       (send* _ros_poly __ros_poly)
     (progn
       (if __ros_poly (setq _ros_poly (car __ros_poly)))
       _ros_poly)))
  (:defecto_divpor_zonas
   (&rest __defecto_divpor_zonas)
   (if (keywordp (car __defecto_divpor_zonas))
       (send* _defecto_divpor_zonas __defecto_divpor_zonas)
     (progn
       (if __defecto_divpor_zonas (setq _defecto_divpor_zonas (car __defecto_divpor_zonas)))
       _defecto_divpor_zonas)))
  (:reparado
   (&optional __reparado)
   (if __reparado (setq _reparado __reparado)) _reparado)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Polygon _ros_poly
    (send _ros_poly :serialization-length)
    ;; irobot_fcpp_simul/defecto_zona[] _defecto_divpor_zonas
    (apply #'+ (send-all _defecto_divpor_zonas :serialization-length)) 4
    ;; bool _reparado
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Polygon _ros_poly
       (send _ros_poly :serialize s)
     ;; irobot_fcpp_simul/defecto_zona[] _defecto_divpor_zonas
     (write-long (length _defecto_divpor_zonas) s)
     (dolist (elem _defecto_divpor_zonas)
       (send elem :serialize s)
       )
     ;; bool _reparado
       (if _reparado (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Polygon _ros_poly
     (send _ros_poly :deserialize buf ptr-) (incf ptr- (send _ros_poly :serialization-length))
   ;; irobot_fcpp_simul/defecto_zona[] _defecto_divpor_zonas
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _defecto_divpor_zonas (let (r) (dotimes (i n) (push (instance irobot_fcpp_simul::defecto_zona :init) r)) r))
     (dolist (elem- _defecto_divpor_zonas)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; bool _reparado
     (setq _reparado (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get irobot_fcpp_simul::defecto :md5sum-) "6f4dca0cbac38a321305ee29edd2c608")
(setf (get irobot_fcpp_simul::defecto :datatype-) "irobot_fcpp_simul/defecto")
(setf (get irobot_fcpp_simul::defecto :definition-)
      "geometry_msgs/Polygon ros_poly
defecto_zona[] defecto_divpor_zonas

bool reparado

================================================================================
MSG: geometry_msgs/Polygon
#A specification of a polygon where the first and last points are assumed to be connected
Point32[] points

================================================================================
MSG: geometry_msgs/Point32
# This contains the position of a point in free space(with 32 bits of precision).
# It is recommeded to use Point wherever possible instead of Point32.  
# 
# This recommendation is to promote interoperability.  
#
# This message is designed to take up less space when sending
# lots of points at once, as in the case of a PointCloud.  

float32 x
float32 y
float32 z
================================================================================
MSG: irobot_fcpp_simul/defecto_zona
geometry_msgs/Polygon ros_poly
defecto_simple[] trap_vec

int32 direccion_rep
bool reparado
int32 zona

================================================================================
MSG: irobot_fcpp_simul/defecto_simple
geometry_msgs/Polygon ros_poly
int32 direccion_rep
bool reparado

")



(provide :irobot_fcpp_simul/defecto "6f4dca0cbac38a321305ee29edd2c608")


