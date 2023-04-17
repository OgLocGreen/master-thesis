;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::ComputeDefectsDecompGoal)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'ComputeDefectsDecompGoal (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::COMPUTEDEFECTSDECOMPGOAL")
  (make-package "IROBOT_FCPP_SIMUL::COMPUTEDEFECTSDECOMPGOAL"))

(in-package "ROS")
;;//! \htmlinclude ComputeDefectsDecompGoal.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::ComputeDefectsDecompGoal
  :super ros::object
  :slots (_chapa_id _poly_defect _zone0 _zone90 _zone180 _zone270 _xmax _ymax ))

(defmethod irobot_fcpp_simul::ComputeDefectsDecompGoal
  (:init
   (&key
    ((:chapa_id __chapa_id) 0)
    ((:poly_defect __poly_defect) (instance geometry_msgs::Polygon :init))
    ((:zone0 __zone0) (instance geometry_msgs::Polygon :init))
    ((:zone90 __zone90) (instance geometry_msgs::Polygon :init))
    ((:zone180 __zone180) (instance geometry_msgs::Polygon :init))
    ((:zone270 __zone270) (instance geometry_msgs::Polygon :init))
    ((:xmax __xmax) 0.0)
    ((:ymax __ymax) 0.0)
    )
   (send-super :init)
   (setq _chapa_id (round __chapa_id))
   (setq _poly_defect __poly_defect)
   (setq _zone0 __zone0)
   (setq _zone90 __zone90)
   (setq _zone180 __zone180)
   (setq _zone270 __zone270)
   (setq _xmax (float __xmax))
   (setq _ymax (float __ymax))
   self)
  (:chapa_id
   (&optional __chapa_id)
   (if __chapa_id (setq _chapa_id __chapa_id)) _chapa_id)
  (:poly_defect
   (&rest __poly_defect)
   (if (keywordp (car __poly_defect))
       (send* _poly_defect __poly_defect)
     (progn
       (if __poly_defect (setq _poly_defect (car __poly_defect)))
       _poly_defect)))
  (:zone0
   (&rest __zone0)
   (if (keywordp (car __zone0))
       (send* _zone0 __zone0)
     (progn
       (if __zone0 (setq _zone0 (car __zone0)))
       _zone0)))
  (:zone90
   (&rest __zone90)
   (if (keywordp (car __zone90))
       (send* _zone90 __zone90)
     (progn
       (if __zone90 (setq _zone90 (car __zone90)))
       _zone90)))
  (:zone180
   (&rest __zone180)
   (if (keywordp (car __zone180))
       (send* _zone180 __zone180)
     (progn
       (if __zone180 (setq _zone180 (car __zone180)))
       _zone180)))
  (:zone270
   (&rest __zone270)
   (if (keywordp (car __zone270))
       (send* _zone270 __zone270)
     (progn
       (if __zone270 (setq _zone270 (car __zone270)))
       _zone270)))
  (:xmax
   (&optional __xmax)
   (if __xmax (setq _xmax __xmax)) _xmax)
  (:ymax
   (&optional __ymax)
   (if __ymax (setq _ymax __ymax)) _ymax)
  (:serialization-length
   ()
   (+
    ;; int32 _chapa_id
    4
    ;; geometry_msgs/Polygon _poly_defect
    (send _poly_defect :serialization-length)
    ;; geometry_msgs/Polygon _zone0
    (send _zone0 :serialization-length)
    ;; geometry_msgs/Polygon _zone90
    (send _zone90 :serialization-length)
    ;; geometry_msgs/Polygon _zone180
    (send _zone180 :serialization-length)
    ;; geometry_msgs/Polygon _zone270
    (send _zone270 :serialization-length)
    ;; float32 _xmax
    4
    ;; float32 _ymax
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _chapa_id
       (write-long _chapa_id s)
     ;; geometry_msgs/Polygon _poly_defect
       (send _poly_defect :serialize s)
     ;; geometry_msgs/Polygon _zone0
       (send _zone0 :serialize s)
     ;; geometry_msgs/Polygon _zone90
       (send _zone90 :serialize s)
     ;; geometry_msgs/Polygon _zone180
       (send _zone180 :serialize s)
     ;; geometry_msgs/Polygon _zone270
       (send _zone270 :serialize s)
     ;; float32 _xmax
       (sys::poke _xmax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ymax
       (sys::poke _ymax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _chapa_id
     (setq _chapa_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Polygon _poly_defect
     (send _poly_defect :deserialize buf ptr-) (incf ptr- (send _poly_defect :serialization-length))
   ;; geometry_msgs/Polygon _zone0
     (send _zone0 :deserialize buf ptr-) (incf ptr- (send _zone0 :serialization-length))
   ;; geometry_msgs/Polygon _zone90
     (send _zone90 :deserialize buf ptr-) (incf ptr- (send _zone90 :serialization-length))
   ;; geometry_msgs/Polygon _zone180
     (send _zone180 :deserialize buf ptr-) (incf ptr- (send _zone180 :serialization-length))
   ;; geometry_msgs/Polygon _zone270
     (send _zone270 :deserialize buf ptr-) (incf ptr- (send _zone270 :serialization-length))
   ;; float32 _xmax
     (setq _xmax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ymax
     (setq _ymax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get irobot_fcpp_simul::ComputeDefectsDecompGoal :md5sum-) "100a9f9d0c5c91d1ec171cccc3fdc2c8")
(setf (get irobot_fcpp_simul::ComputeDefectsDecompGoal :datatype-) "irobot_fcpp_simul/ComputeDefectsDecompGoal")
(setf (get irobot_fcpp_simul::ComputeDefectsDecompGoal :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define the goal
int32 chapa_id

geometry_msgs/Polygon poly_defect


geometry_msgs/Polygon zone0
geometry_msgs/Polygon zone90
geometry_msgs/Polygon zone180
geometry_msgs/Polygon zone270

float32 xmax
float32 ymax


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



(provide :irobot_fcpp_simul/ComputeDefectsDecompGoal "100a9f9d0c5c91d1ec171cccc3fdc2c8")


