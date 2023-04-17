;; Auto-generated. Do not edit!


(when (boundp 'action_server_package::FCPP_in)
  (if (not (find-package "ACTION_SERVER_PACKAGE"))
    (make-package "ACTION_SERVER_PACKAGE"))
  (shadow 'FCPP_in (find-package "ACTION_SERVER_PACKAGE")))
(unless (find-package "ACTION_SERVER_PACKAGE::FCPP_IN")
  (make-package "ACTION_SERVER_PACKAGE::FCPP_IN"))
(unless (find-package "ACTION_SERVER_PACKAGE::FCPP_INREQUEST")
  (make-package "ACTION_SERVER_PACKAGE::FCPP_INREQUEST"))
(unless (find-package "ACTION_SERVER_PACKAGE::FCPP_INRESPONSE")
  (make-package "ACTION_SERVER_PACKAGE::FCPP_INRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass action_server_package::FCPP_inRequest
  :super ros::object
  :slots (_id_input ))

(defmethod action_server_package::FCPP_inRequest
  (:init
   (&key
    ((:id_input __id_input) 0)
    )
   (send-super :init)
   (setq _id_input (round __id_input))
   self)
  (:id_input
   (&optional __id_input)
   (if __id_input (setq _id_input __id_input)) _id_input)
  (:serialization-length
   ()
   (+
    ;; int32 _id_input
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _id_input
       (write-long _id_input s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _id_input
     (setq _id_input (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass action_server_package::FCPP_inResponse
  :super ros::object
  :slots (_n_defects _xmin_chapa _xmax_chapa _ymin_chapa _ymax_chapa _poly_i _number_of_chapas ))

(defmethod action_server_package::FCPP_inResponse
  (:init
   (&key
    ((:n_defects __n_defects) 0)
    ((:xmin_chapa __xmin_chapa) 0.0)
    ((:xmax_chapa __xmax_chapa) 0.0)
    ((:ymin_chapa __ymin_chapa) 0.0)
    ((:ymax_chapa __ymax_chapa) 0.0)
    ((:poly_i __poly_i) (instance geometry_msgs::Polygon :init))
    ((:number_of_chapas __number_of_chapas) 0)
    )
   (send-super :init)
   (setq _n_defects (round __n_defects))
   (setq _xmin_chapa (float __xmin_chapa))
   (setq _xmax_chapa (float __xmax_chapa))
   (setq _ymin_chapa (float __ymin_chapa))
   (setq _ymax_chapa (float __ymax_chapa))
   (setq _poly_i __poly_i)
   (setq _number_of_chapas (round __number_of_chapas))
   self)
  (:n_defects
   (&optional __n_defects)
   (if __n_defects (setq _n_defects __n_defects)) _n_defects)
  (:xmin_chapa
   (&optional __xmin_chapa)
   (if __xmin_chapa (setq _xmin_chapa __xmin_chapa)) _xmin_chapa)
  (:xmax_chapa
   (&optional __xmax_chapa)
   (if __xmax_chapa (setq _xmax_chapa __xmax_chapa)) _xmax_chapa)
  (:ymin_chapa
   (&optional __ymin_chapa)
   (if __ymin_chapa (setq _ymin_chapa __ymin_chapa)) _ymin_chapa)
  (:ymax_chapa
   (&optional __ymax_chapa)
   (if __ymax_chapa (setq _ymax_chapa __ymax_chapa)) _ymax_chapa)
  (:poly_i
   (&rest __poly_i)
   (if (keywordp (car __poly_i))
       (send* _poly_i __poly_i)
     (progn
       (if __poly_i (setq _poly_i (car __poly_i)))
       _poly_i)))
  (:number_of_chapas
   (&optional __number_of_chapas)
   (if __number_of_chapas (setq _number_of_chapas __number_of_chapas)) _number_of_chapas)
  (:serialization-length
   ()
   (+
    ;; int32 _n_defects
    4
    ;; float32 _xmin_chapa
    4
    ;; float32 _xmax_chapa
    4
    ;; float32 _ymin_chapa
    4
    ;; float32 _ymax_chapa
    4
    ;; geometry_msgs/Polygon _poly_i
    (send _poly_i :serialization-length)
    ;; int32 _number_of_chapas
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _n_defects
       (write-long _n_defects s)
     ;; float32 _xmin_chapa
       (sys::poke _xmin_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _xmax_chapa
       (sys::poke _xmax_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ymin_chapa
       (sys::poke _ymin_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ymax_chapa
       (sys::poke _ymax_chapa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Polygon _poly_i
       (send _poly_i :serialize s)
     ;; int32 _number_of_chapas
       (write-long _number_of_chapas s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _n_defects
     (setq _n_defects (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _xmin_chapa
     (setq _xmin_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _xmax_chapa
     (setq _xmax_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ymin_chapa
     (setq _ymin_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ymax_chapa
     (setq _ymax_chapa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Polygon _poly_i
     (send _poly_i :deserialize buf ptr-) (incf ptr- (send _poly_i :serialization-length))
   ;; int32 _number_of_chapas
     (setq _number_of_chapas (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass action_server_package::FCPP_in
  :super ros::object
  :slots ())

(setf (get action_server_package::FCPP_in :md5sum-) "3a9946ec5195dc8fb4f14eeb6ec2e339")
(setf (get action_server_package::FCPP_in :datatype-) "action_server_package/FCPP_in")
(setf (get action_server_package::FCPP_in :request) action_server_package::FCPP_inRequest)
(setf (get action_server_package::FCPP_in :response) action_server_package::FCPP_inResponse)

(defmethod action_server_package::FCPP_inRequest
  (:response () (instance action_server_package::FCPP_inResponse :init)))

(setf (get action_server_package::FCPP_inRequest :md5sum-) "3a9946ec5195dc8fb4f14eeb6ec2e339")
(setf (get action_server_package::FCPP_inRequest :datatype-) "action_server_package/FCPP_inRequest")
(setf (get action_server_package::FCPP_inRequest :definition-)
      "int32 id_input
---
int32 n_defects

float32 xmin_chapa
float32 xmax_chapa
float32 ymin_chapa
float32 ymax_chapa

geometry_msgs/Polygon poly_i

int32 number_of_chapas

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
")

(setf (get action_server_package::FCPP_inResponse :md5sum-) "3a9946ec5195dc8fb4f14eeb6ec2e339")
(setf (get action_server_package::FCPP_inResponse :datatype-) "action_server_package/FCPP_inResponse")
(setf (get action_server_package::FCPP_inResponse :definition-)
      "int32 id_input
---
int32 n_defects

float32 xmin_chapa
float32 xmax_chapa
float32 ymin_chapa
float32 ymax_chapa

geometry_msgs/Polygon poly_i

int32 number_of_chapas

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
")



(provide :action_server_package/FCPP_in "3a9946ec5195dc8fb4f14eeb6ec2e339")


