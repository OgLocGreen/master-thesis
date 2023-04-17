;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::defecto_zona)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'defecto_zona (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::DEFECTO_ZONA")
  (make-package "IROBOT_FCPP_SIMUL::DEFECTO_ZONA"))

(in-package "ROS")
;;//! \htmlinclude defecto_zona.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::defecto_zona
  :super ros::object
  :slots (_ros_poly _trap_vec _direccion_rep _reparado _zona ))

(defmethod irobot_fcpp_simul::defecto_zona
  (:init
   (&key
    ((:ros_poly __ros_poly) (instance geometry_msgs::Polygon :init))
    ((:trap_vec __trap_vec) (let (r) (dotimes (i 0) (push (instance irobot_fcpp_simul::defecto_simple :init) r)) r))
    ((:direccion_rep __direccion_rep) 0)
    ((:reparado __reparado) nil)
    ((:zona __zona) 0)
    )
   (send-super :init)
   (setq _ros_poly __ros_poly)
   (setq _trap_vec __trap_vec)
   (setq _direccion_rep (round __direccion_rep))
   (setq _reparado __reparado)
   (setq _zona (round __zona))
   self)
  (:ros_poly
   (&rest __ros_poly)
   (if (keywordp (car __ros_poly))
       (send* _ros_poly __ros_poly)
     (progn
       (if __ros_poly (setq _ros_poly (car __ros_poly)))
       _ros_poly)))
  (:trap_vec
   (&rest __trap_vec)
   (if (keywordp (car __trap_vec))
       (send* _trap_vec __trap_vec)
     (progn
       (if __trap_vec (setq _trap_vec (car __trap_vec)))
       _trap_vec)))
  (:direccion_rep
   (&optional __direccion_rep)
   (if __direccion_rep (setq _direccion_rep __direccion_rep)) _direccion_rep)
  (:reparado
   (&optional __reparado)
   (if __reparado (setq _reparado __reparado)) _reparado)
  (:zona
   (&optional __zona)
   (if __zona (setq _zona __zona)) _zona)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Polygon _ros_poly
    (send _ros_poly :serialization-length)
    ;; irobot_fcpp_simul/defecto_simple[] _trap_vec
    (apply #'+ (send-all _trap_vec :serialization-length)) 4
    ;; int32 _direccion_rep
    4
    ;; bool _reparado
    1
    ;; int32 _zona
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Polygon _ros_poly
       (send _ros_poly :serialize s)
     ;; irobot_fcpp_simul/defecto_simple[] _trap_vec
     (write-long (length _trap_vec) s)
     (dolist (elem _trap_vec)
       (send elem :serialize s)
       )
     ;; int32 _direccion_rep
       (write-long _direccion_rep s)
     ;; bool _reparado
       (if _reparado (write-byte -1 s) (write-byte 0 s))
     ;; int32 _zona
       (write-long _zona s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Polygon _ros_poly
     (send _ros_poly :deserialize buf ptr-) (incf ptr- (send _ros_poly :serialization-length))
   ;; irobot_fcpp_simul/defecto_simple[] _trap_vec
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trap_vec (let (r) (dotimes (i n) (push (instance irobot_fcpp_simul::defecto_simple :init) r)) r))
     (dolist (elem- _trap_vec)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _direccion_rep
     (setq _direccion_rep (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _reparado
     (setq _reparado (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int32 _zona
     (setq _zona (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get irobot_fcpp_simul::defecto_zona :md5sum-) "66d6ef707c05e8c8eaa69b175e897e44")
(setf (get irobot_fcpp_simul::defecto_zona :datatype-) "irobot_fcpp_simul/defecto_zona")
(setf (get irobot_fcpp_simul::defecto_zona :definition-)
      "geometry_msgs/Polygon ros_poly
defecto_simple[] trap_vec

int32 direccion_rep
bool reparado
int32 zona

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
MSG: irobot_fcpp_simul/defecto_simple
geometry_msgs/Polygon ros_poly
int32 direccion_rep
bool reparado

")



(provide :irobot_fcpp_simul/defecto_zona "66d6ef707c05e8c8eaa69b175e897e44")


