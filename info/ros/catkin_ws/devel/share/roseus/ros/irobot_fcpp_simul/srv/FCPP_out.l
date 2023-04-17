;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::FCPP_out)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'FCPP_out (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_OUT")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_OUT"))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_OUTREQUEST")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_OUTREQUEST"))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_OUTRESPONSE")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_OUTRESPONSE"))

(in-package "ROS")





(defclass irobot_fcpp_simul::FCPP_outRequest
  :super ros::object
  :slots ())

(defmethod irobot_fcpp_simul::FCPP_outRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass irobot_fcpp_simul::FCPP_outResponse
  :super ros::object
  :slots (_defecto_out ))

(defmethod irobot_fcpp_simul::FCPP_outResponse
  (:init
   (&key
    ((:defecto_out __defecto_out) (let (r) (dotimes (i 0) (push (instance irobot_fcpp_simul::defecto :init) r)) r))
    )
   (send-super :init)
   (setq _defecto_out __defecto_out)
   self)
  (:defecto_out
   (&rest __defecto_out)
   (if (keywordp (car __defecto_out))
       (send* _defecto_out __defecto_out)
     (progn
       (if __defecto_out (setq _defecto_out (car __defecto_out)))
       _defecto_out)))
  (:serialization-length
   ()
   (+
    ;; irobot_fcpp_simul/defecto[] _defecto_out
    (apply #'+ (send-all _defecto_out :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; irobot_fcpp_simul/defecto[] _defecto_out
     (write-long (length _defecto_out) s)
     (dolist (elem _defecto_out)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; irobot_fcpp_simul/defecto[] _defecto_out
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _defecto_out (let (r) (dotimes (i n) (push (instance irobot_fcpp_simul::defecto :init) r)) r))
     (dolist (elem- _defecto_out)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass irobot_fcpp_simul::FCPP_out
  :super ros::object
  :slots ())

(setf (get irobot_fcpp_simul::FCPP_out :md5sum-) "30c6047a6867f6dfad71ccb5b3d8e613")
(setf (get irobot_fcpp_simul::FCPP_out :datatype-) "irobot_fcpp_simul/FCPP_out")
(setf (get irobot_fcpp_simul::FCPP_out :request) irobot_fcpp_simul::FCPP_outRequest)
(setf (get irobot_fcpp_simul::FCPP_out :response) irobot_fcpp_simul::FCPP_outResponse)

(defmethod irobot_fcpp_simul::FCPP_outRequest
  (:response () (instance irobot_fcpp_simul::FCPP_outResponse :init)))

(setf (get irobot_fcpp_simul::FCPP_outRequest :md5sum-) "30c6047a6867f6dfad71ccb5b3d8e613")
(setf (get irobot_fcpp_simul::FCPP_outRequest :datatype-) "irobot_fcpp_simul/FCPP_outRequest")
(setf (get irobot_fcpp_simul::FCPP_outRequest :definition-)
      "---
defecto[] defecto_out


================================================================================
MSG: irobot_fcpp_simul/defecto
geometry_msgs/Polygon ros_poly
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

(setf (get irobot_fcpp_simul::FCPP_outResponse :md5sum-) "30c6047a6867f6dfad71ccb5b3d8e613")
(setf (get irobot_fcpp_simul::FCPP_outResponse :datatype-) "irobot_fcpp_simul/FCPP_outResponse")
(setf (get irobot_fcpp_simul::FCPP_outResponse :definition-)
      "---
defecto[] defecto_out


================================================================================
MSG: irobot_fcpp_simul/defecto
geometry_msgs/Polygon ros_poly
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



(provide :irobot_fcpp_simul/FCPP_out "30c6047a6867f6dfad71ccb5b3d8e613")


