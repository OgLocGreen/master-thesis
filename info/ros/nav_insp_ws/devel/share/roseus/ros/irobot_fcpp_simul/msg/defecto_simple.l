;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::defecto_simple)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'defecto_simple (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::DEFECTO_SIMPLE")
  (make-package "IROBOT_FCPP_SIMUL::DEFECTO_SIMPLE"))

(in-package "ROS")
;;//! \htmlinclude defecto_simple.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::defecto_simple
  :super ros::object
  :slots (_ros_poly _direccion_rep _reparado ))

(defmethod irobot_fcpp_simul::defecto_simple
  (:init
   (&key
    ((:ros_poly __ros_poly) (instance geometry_msgs::Polygon :init))
    ((:direccion_rep __direccion_rep) 0)
    ((:reparado __reparado) nil)
    )
   (send-super :init)
   (setq _ros_poly __ros_poly)
   (setq _direccion_rep (round __direccion_rep))
   (setq _reparado __reparado)
   self)
  (:ros_poly
   (&rest __ros_poly)
   (if (keywordp (car __ros_poly))
       (send* _ros_poly __ros_poly)
     (progn
       (if __ros_poly (setq _ros_poly (car __ros_poly)))
       _ros_poly)))
  (:direccion_rep
   (&optional __direccion_rep)
   (if __direccion_rep (setq _direccion_rep __direccion_rep)) _direccion_rep)
  (:reparado
   (&optional __reparado)
   (if __reparado (setq _reparado __reparado)) _reparado)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Polygon _ros_poly
    (send _ros_poly :serialization-length)
    ;; int32 _direccion_rep
    4
    ;; bool _reparado
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Polygon _ros_poly
       (send _ros_poly :serialize s)
     ;; int32 _direccion_rep
       (write-long _direccion_rep s)
     ;; bool _reparado
       (if _reparado (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Polygon _ros_poly
     (send _ros_poly :deserialize buf ptr-) (incf ptr- (send _ros_poly :serialization-length))
   ;; int32 _direccion_rep
     (setq _direccion_rep (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _reparado
     (setq _reparado (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get irobot_fcpp_simul::defecto_simple :md5sum-) "9e9103e825e653e77fe6292f6a6f8a76")
(setf (get irobot_fcpp_simul::defecto_simple :datatype-) "irobot_fcpp_simul/defecto_simple")
(setf (get irobot_fcpp_simul::defecto_simple :definition-)
      "geometry_msgs/Polygon ros_poly
int32 direccion_rep
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
")



(provide :irobot_fcpp_simul/defecto_simple "9e9103e825e653e77fe6292f6a6f8a76")


