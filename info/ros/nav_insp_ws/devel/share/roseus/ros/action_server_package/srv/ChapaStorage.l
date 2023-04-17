;; Auto-generated. Do not edit!


(when (boundp 'action_server_package::ChapaStorage)
  (if (not (find-package "ACTION_SERVER_PACKAGE"))
    (make-package "ACTION_SERVER_PACKAGE"))
  (shadow 'ChapaStorage (find-package "ACTION_SERVER_PACKAGE")))
(unless (find-package "ACTION_SERVER_PACKAGE::CHAPASTORAGE")
  (make-package "ACTION_SERVER_PACKAGE::CHAPASTORAGE"))
(unless (find-package "ACTION_SERVER_PACKAGE::CHAPASTORAGEREQUEST")
  (make-package "ACTION_SERVER_PACKAGE::CHAPASTORAGEREQUEST"))
(unless (find-package "ACTION_SERVER_PACKAGE::CHAPASTORAGERESPONSE")
  (make-package "ACTION_SERVER_PACKAGE::CHAPASTORAGERESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass action_server_package::ChapaStorageRequest
  :super ros::object
  :slots (_id_chapa ))

(defmethod action_server_package::ChapaStorageRequest
  (:init
   (&key
    ((:id_chapa __id_chapa) 0)
    )
   (send-super :init)
   (setq _id_chapa (round __id_chapa))
   self)
  (:id_chapa
   (&optional __id_chapa)
   (if __id_chapa (setq _id_chapa __id_chapa)) _id_chapa)
  (:serialization-length
   ()
   (+
    ;; int32 _id_chapa
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _id_chapa
       (write-long _id_chapa s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _id_chapa
     (setq _id_chapa (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass action_server_package::ChapaStorageResponse
  :super ros::object
  :slots (_long_chapa _width_chapa _coordA _coordB _coordC _coordD _number_of_chapas ))

(defmethod action_server_package::ChapaStorageResponse
  (:init
   (&key
    ((:long_chapa __long_chapa) 0.0)
    ((:width_chapa __width_chapa) 0.0)
    ((:coordA __coordA) (instance geometry_msgs::Point :init))
    ((:coordB __coordB) (instance geometry_msgs::Point :init))
    ((:coordC __coordC) (instance geometry_msgs::Point :init))
    ((:coordD __coordD) (instance geometry_msgs::Point :init))
    ((:number_of_chapas __number_of_chapas) 0)
    )
   (send-super :init)
   (setq _long_chapa (float __long_chapa))
   (setq _width_chapa (float __width_chapa))
   (setq _coordA __coordA)
   (setq _coordB __coordB)
   (setq _coordC __coordC)
   (setq _coordD __coordD)
   (setq _number_of_chapas (round __number_of_chapas))
   self)
  (:long_chapa
   (&optional __long_chapa)
   (if __long_chapa (setq _long_chapa __long_chapa)) _long_chapa)
  (:width_chapa
   (&optional __width_chapa)
   (if __width_chapa (setq _width_chapa __width_chapa)) _width_chapa)
  (:coordA
   (&rest __coordA)
   (if (keywordp (car __coordA))
       (send* _coordA __coordA)
     (progn
       (if __coordA (setq _coordA (car __coordA)))
       _coordA)))
  (:coordB
   (&rest __coordB)
   (if (keywordp (car __coordB))
       (send* _coordB __coordB)
     (progn
       (if __coordB (setq _coordB (car __coordB)))
       _coordB)))
  (:coordC
   (&rest __coordC)
   (if (keywordp (car __coordC))
       (send* _coordC __coordC)
     (progn
       (if __coordC (setq _coordC (car __coordC)))
       _coordC)))
  (:coordD
   (&rest __coordD)
   (if (keywordp (car __coordD))
       (send* _coordD __coordD)
     (progn
       (if __coordD (setq _coordD (car __coordD)))
       _coordD)))
  (:number_of_chapas
   (&optional __number_of_chapas)
   (if __number_of_chapas (setq _number_of_chapas __number_of_chapas)) _number_of_chapas)
  (:serialization-length
   ()
   (+
    ;; float32 _long_chapa
    4
    ;; float32 _width_chapa
    4
    ;; geometry_msgs/Point _coordA
    (send _coordA :serialization-length)
    ;; geometry_msgs/Point _coordB
    (send _coordB :serialization-length)
    ;; geometry_msgs/Point _coordC
    (send _coordC :serialization-length)
    ;; geometry_msgs/Point _coordD
    (send _coordD :serialization-length)
    ;; int32 _number_of_chapas
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _long_chapa
       (sys::poke _long_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width_chapa
       (sys::poke _width_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Point _coordA
       (send _coordA :serialize s)
     ;; geometry_msgs/Point _coordB
       (send _coordB :serialize s)
     ;; geometry_msgs/Point _coordC
       (send _coordC :serialize s)
     ;; geometry_msgs/Point _coordD
       (send _coordD :serialize s)
     ;; int32 _number_of_chapas
       (write-long _number_of_chapas s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _long_chapa
     (setq _long_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width_chapa
     (setq _width_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Point _coordA
     (send _coordA :deserialize buf ptr-) (incf ptr- (send _coordA :serialization-length))
   ;; geometry_msgs/Point _coordB
     (send _coordB :deserialize buf ptr-) (incf ptr- (send _coordB :serialization-length))
   ;; geometry_msgs/Point _coordC
     (send _coordC :deserialize buf ptr-) (incf ptr- (send _coordC :serialization-length))
   ;; geometry_msgs/Point _coordD
     (send _coordD :deserialize buf ptr-) (incf ptr- (send _coordD :serialization-length))
   ;; int32 _number_of_chapas
     (setq _number_of_chapas (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass action_server_package::ChapaStorage
  :super ros::object
  :slots ())

(setf (get action_server_package::ChapaStorage :md5sum-) "d420ea154534426ff59c21556a0bdbf4")
(setf (get action_server_package::ChapaStorage :datatype-) "action_server_package/ChapaStorage")
(setf (get action_server_package::ChapaStorage :request) action_server_package::ChapaStorageRequest)
(setf (get action_server_package::ChapaStorage :response) action_server_package::ChapaStorageResponse)

(defmethod action_server_package::ChapaStorageRequest
  (:response () (instance action_server_package::ChapaStorageResponse :init)))

(setf (get action_server_package::ChapaStorageRequest :md5sum-) "d420ea154534426ff59c21556a0bdbf4")
(setf (get action_server_package::ChapaStorageRequest :datatype-) "action_server_package/ChapaStorageRequest")
(setf (get action_server_package::ChapaStorageRequest :definition-)
      "int32 id_chapa
---
float32 long_chapa
float32 width_chapa

geometry_msgs/Point coordA
geometry_msgs/Point coordB
geometry_msgs/Point coordC
geometry_msgs/Point coordD

int32 number_of_chapas

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get action_server_package::ChapaStorageResponse :md5sum-) "d420ea154534426ff59c21556a0bdbf4")
(setf (get action_server_package::ChapaStorageResponse :datatype-) "action_server_package/ChapaStorageResponse")
(setf (get action_server_package::ChapaStorageResponse :definition-)
      "int32 id_chapa
---
float32 long_chapa
float32 width_chapa

geometry_msgs/Point coordA
geometry_msgs/Point coordB
geometry_msgs/Point coordC
geometry_msgs/Point coordD

int32 number_of_chapas

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :action_server_package/ChapaStorage "d420ea154534426ff59c21556a0bdbf4")


