;; Auto-generated. Do not edit!


(when (boundp 'aux_controllers::SetFrame)
  (if (not (find-package "AUX_CONTROLLERS"))
    (make-package "AUX_CONTROLLERS"))
  (shadow 'SetFrame (find-package "AUX_CONTROLLERS")))
(unless (find-package "AUX_CONTROLLERS::SETFRAME")
  (make-package "AUX_CONTROLLERS::SETFRAME"))
(unless (find-package "AUX_CONTROLLERS::SETFRAMEREQUEST")
  (make-package "AUX_CONTROLLERS::SETFRAMEREQUEST"))
(unless (find-package "AUX_CONTROLLERS::SETFRAMERESPONSE")
  (make-package "AUX_CONTROLLERS::SETFRAMERESPONSE"))

(in-package "ROS")





(defclass aux_controllers::SetFrameRequest
  :super ros::object
  :slots (_ini _origin_x _origin_y _origin_z _rotation_roll _rotation_pitch _rotation_yaw ))

(defmethod aux_controllers::SetFrameRequest
  (:init
   (&key
    ((:ini __ini) nil)
    ((:origin_x __origin_x) 0.0)
    ((:origin_y __origin_y) 0.0)
    ((:origin_z __origin_z) 0.0)
    ((:rotation_roll __rotation_roll) 0.0)
    ((:rotation_pitch __rotation_pitch) 0.0)
    ((:rotation_yaw __rotation_yaw) 0.0)
    )
   (send-super :init)
   (setq _ini __ini)
   (setq _origin_x (float __origin_x))
   (setq _origin_y (float __origin_y))
   (setq _origin_z (float __origin_z))
   (setq _rotation_roll (float __rotation_roll))
   (setq _rotation_pitch (float __rotation_pitch))
   (setq _rotation_yaw (float __rotation_yaw))
   self)
  (:ini
   (&optional __ini)
   (if __ini (setq _ini __ini)) _ini)
  (:origin_x
   (&optional __origin_x)
   (if __origin_x (setq _origin_x __origin_x)) _origin_x)
  (:origin_y
   (&optional __origin_y)
   (if __origin_y (setq _origin_y __origin_y)) _origin_y)
  (:origin_z
   (&optional __origin_z)
   (if __origin_z (setq _origin_z __origin_z)) _origin_z)
  (:rotation_roll
   (&optional __rotation_roll)
   (if __rotation_roll (setq _rotation_roll __rotation_roll)) _rotation_roll)
  (:rotation_pitch
   (&optional __rotation_pitch)
   (if __rotation_pitch (setq _rotation_pitch __rotation_pitch)) _rotation_pitch)
  (:rotation_yaw
   (&optional __rotation_yaw)
   (if __rotation_yaw (setq _rotation_yaw __rotation_yaw)) _rotation_yaw)
  (:serialization-length
   ()
   (+
    ;; bool _ini
    1
    ;; float32 _origin_x
    4
    ;; float32 _origin_y
    4
    ;; float32 _origin_z
    4
    ;; float32 _rotation_roll
    4
    ;; float32 _rotation_pitch
    4
    ;; float32 _rotation_yaw
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _ini
       (if _ini (write-byte -1 s) (write-byte 0 s))
     ;; float32 _origin_x
       (sys::poke _origin_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _origin_y
       (sys::poke _origin_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _origin_z
       (sys::poke _origin_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rotation_roll
       (sys::poke _rotation_roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rotation_pitch
       (sys::poke _rotation_pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rotation_yaw
       (sys::poke _rotation_yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _ini
     (setq _ini (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _origin_x
     (setq _origin_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _origin_y
     (setq _origin_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _origin_z
     (setq _origin_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rotation_roll
     (setq _rotation_roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rotation_pitch
     (setq _rotation_pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rotation_yaw
     (setq _rotation_yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass aux_controllers::SetFrameResponse
  :super ros::object
  :slots (_respond ))

(defmethod aux_controllers::SetFrameResponse
  (:init
   (&key
    ((:respond __respond) nil)
    )
   (send-super :init)
   (setq _respond __respond)
   self)
  (:respond
   (&optional __respond)
   (if __respond (setq _respond __respond)) _respond)
  (:serialization-length
   ()
   (+
    ;; bool _respond
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _respond
       (if _respond (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _respond
     (setq _respond (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass aux_controllers::SetFrame
  :super ros::object
  :slots ())

(setf (get aux_controllers::SetFrame :md5sum-) "fc7b3836a679f38a5c6b9328b643f1e8")
(setf (get aux_controllers::SetFrame :datatype-) "aux_controllers/SetFrame")
(setf (get aux_controllers::SetFrame :request) aux_controllers::SetFrameRequest)
(setf (get aux_controllers::SetFrame :response) aux_controllers::SetFrameResponse)

(defmethod aux_controllers::SetFrameRequest
  (:response () (instance aux_controllers::SetFrameResponse :init)))

(setf (get aux_controllers::SetFrameRequest :md5sum-) "fc7b3836a679f38a5c6b9328b643f1e8")
(setf (get aux_controllers::SetFrameRequest :datatype-) "aux_controllers/SetFrameRequest")
(setf (get aux_controllers::SetFrameRequest :definition-)
      "bool ini

float32 origin_x
float32 origin_y
float32 origin_z

float32 rotation_roll
float32 rotation_pitch
float32 rotation_yaw

---
bool respond
")

(setf (get aux_controllers::SetFrameResponse :md5sum-) "fc7b3836a679f38a5c6b9328b643f1e8")
(setf (get aux_controllers::SetFrameResponse :datatype-) "aux_controllers/SetFrameResponse")
(setf (get aux_controllers::SetFrameResponse :definition-)
      "bool ini

float32 origin_x
float32 origin_y
float32 origin_z

float32 rotation_roll
float32 rotation_pitch
float32 rotation_yaw

---
bool respond
")



(provide :aux_controllers/SetFrame "fc7b3836a679f38a5c6b9328b643f1e8")


