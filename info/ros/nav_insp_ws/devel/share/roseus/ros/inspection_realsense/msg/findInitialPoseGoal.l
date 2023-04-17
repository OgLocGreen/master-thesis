;; Auto-generated. Do not edit!


(when (boundp 'inspection_realsense::findInitialPoseGoal)
  (if (not (find-package "INSPECTION_REALSENSE"))
    (make-package "INSPECTION_REALSENSE"))
  (shadow 'findInitialPoseGoal (find-package "INSPECTION_REALSENSE")))
(unless (find-package "INSPECTION_REALSENSE::FINDINITIALPOSEGOAL")
  (make-package "INSPECTION_REALSENSE::FINDINITIALPOSEGOAL"))

(in-package "ROS")
;;//! \htmlinclude findInitialPoseGoal.msg.html


(defclass inspection_realsense::findInitialPoseGoal
  :super ros::object
  :slots (_vel _width_sheet _long_sheet _width_robot _long_robot _step ))

(defmethod inspection_realsense::findInitialPoseGoal
  (:init
   (&key
    ((:vel __vel) 0.0)
    ((:width_sheet __width_sheet) 0.0)
    ((:long_sheet __long_sheet) 0.0)
    ((:width_robot __width_robot) 0.0)
    ((:long_robot __long_robot) 0.0)
    ((:step __step) 0.0)
    )
   (send-super :init)
   (setq _vel (float __vel))
   (setq _width_sheet (float __width_sheet))
   (setq _long_sheet (float __long_sheet))
   (setq _width_robot (float __width_robot))
   (setq _long_robot (float __long_robot))
   (setq _step (float __step))
   self)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:width_sheet
   (&optional __width_sheet)
   (if __width_sheet (setq _width_sheet __width_sheet)) _width_sheet)
  (:long_sheet
   (&optional __long_sheet)
   (if __long_sheet (setq _long_sheet __long_sheet)) _long_sheet)
  (:width_robot
   (&optional __width_robot)
   (if __width_robot (setq _width_robot __width_robot)) _width_robot)
  (:long_robot
   (&optional __long_robot)
   (if __long_robot (setq _long_robot __long_robot)) _long_robot)
  (:step
   (&optional __step)
   (if __step (setq _step __step)) _step)
  (:serialization-length
   ()
   (+
    ;; float32 _vel
    4
    ;; float32 _width_sheet
    4
    ;; float32 _long_sheet
    4
    ;; float32 _width_robot
    4
    ;; float32 _long_robot
    4
    ;; float32 _step
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width_sheet
       (sys::poke _width_sheet (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_sheet
       (sys::poke _long_sheet (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width_robot
       (sys::poke _width_robot (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_robot
       (sys::poke _long_robot (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _step
       (sys::poke _step (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width_sheet
     (setq _width_sheet (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_sheet
     (setq _long_sheet (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width_robot
     (setq _width_robot (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_robot
     (setq _long_robot (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _step
     (setq _step (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get inspection_realsense::findInitialPoseGoal :md5sum-) "dfefd159abe631060bf2161faa81fdc1")
(setf (get inspection_realsense::findInitialPoseGoal :datatype-) "inspection_realsense/findInitialPoseGoal")
(setf (get inspection_realsense::findInitialPoseGoal :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
float32 vel
float32 width_sheet
float32 long_sheet
float32 width_robot
float32 long_robot
float32 step


")



(provide :inspection_realsense/findInitialPoseGoal "dfefd159abe631060bf2161faa81fdc1")

