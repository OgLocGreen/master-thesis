;; Auto-generated. Do not edit!


(when (boundp 'inspection_realsense::Twist_inspection)
  (if (not (find-package "INSPECTION_REALSENSE"))
    (make-package "INSPECTION_REALSENSE"))
  (shadow 'Twist_inspection (find-package "INSPECTION_REALSENSE")))
(unless (find-package "INSPECTION_REALSENSE::TWIST_INSPECTION")
  (make-package "INSPECTION_REALSENSE::TWIST_INSPECTION"))

(in-package "ROS")
;;//! \htmlinclude Twist_inspection.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass inspection_realsense::Twist_inspection
  :super ros::object
  :slots (_linear _angular _distance_left ))

(defmethod inspection_realsense::Twist_inspection
  (:init
   (&key
    ((:linear __linear) (instance geometry_msgs::Vector3 :init))
    ((:angular __angular) (instance geometry_msgs::Vector3 :init))
    ((:distance_left __distance_left) 0.0)
    )
   (send-super :init)
   (setq _linear __linear)
   (setq _angular __angular)
   (setq _distance_left (float __distance_left))
   self)
  (:linear
   (&rest __linear)
   (if (keywordp (car __linear))
       (send* _linear __linear)
     (progn
       (if __linear (setq _linear (car __linear)))
       _linear)))
  (:angular
   (&rest __angular)
   (if (keywordp (car __angular))
       (send* _angular __angular)
     (progn
       (if __angular (setq _angular (car __angular)))
       _angular)))
  (:distance_left
   (&optional __distance_left)
   (if __distance_left (setq _distance_left __distance_left)) _distance_left)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _linear
    (send _linear :serialization-length)
    ;; geometry_msgs/Vector3 _angular
    (send _angular :serialization-length)
    ;; float32 _distance_left
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _linear
       (send _linear :serialize s)
     ;; geometry_msgs/Vector3 _angular
       (send _angular :serialize s)
     ;; float32 _distance_left
       (sys::poke _distance_left (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _linear
     (send _linear :deserialize buf ptr-) (incf ptr- (send _linear :serialization-length))
   ;; geometry_msgs/Vector3 _angular
     (send _angular :deserialize buf ptr-) (incf ptr- (send _angular :serialization-length))
   ;; float32 _distance_left
     (setq _distance_left (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get inspection_realsense::Twist_inspection :md5sum-) "a6d97e5058c8a6d2a96e566db38def37")
(setf (get inspection_realsense::Twist_inspection :datatype-) "inspection_realsense/Twist_inspection")
(setf (get inspection_realsense::Twist_inspection :definition-)
      "# This expresses velocity in free space broken into it's linear and angular parts. Also, the distance left to leave the sheet
geometry_msgs/Vector3  linear
geometry_msgs/Vector3  angular
float32  distance_left

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :inspection_realsense/Twist_inspection "a6d97e5058c8a6d2a96e566db38def37")


