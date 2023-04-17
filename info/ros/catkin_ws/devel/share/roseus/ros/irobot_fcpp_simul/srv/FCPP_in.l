;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::FCPP_in)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'FCPP_in (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_IN")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_IN"))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_INREQUEST")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_INREQUEST"))
(unless (find-package "IROBOT_FCPP_SIMUL::FCPP_INRESPONSE")
  (make-package "IROBOT_FCPP_SIMUL::FCPP_INRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::FCPP_inRequest
  :super ros::object
  :slots (_id_input _get_working_zones _get_inspection_zones _get_rot_zone ))

(defmethod irobot_fcpp_simul::FCPP_inRequest
  (:init
   (&key
    ((:id_input __id_input) 0)
    ((:get_working_zones __get_working_zones) nil)
    ((:get_inspection_zones __get_inspection_zones) nil)
    ((:get_rot_zone __get_rot_zone) nil)
    )
   (send-super :init)
   (setq _id_input (round __id_input))
   (setq _get_working_zones __get_working_zones)
   (setq _get_inspection_zones __get_inspection_zones)
   (setq _get_rot_zone __get_rot_zone)
   self)
  (:id_input
   (&optional __id_input)
   (if __id_input (setq _id_input __id_input)) _id_input)
  (:get_working_zones
   (&optional __get_working_zones)
   (if __get_working_zones (setq _get_working_zones __get_working_zones)) _get_working_zones)
  (:get_inspection_zones
   (&optional __get_inspection_zones)
   (if __get_inspection_zones (setq _get_inspection_zones __get_inspection_zones)) _get_inspection_zones)
  (:get_rot_zone
   (&optional __get_rot_zone)
   (if __get_rot_zone (setq _get_rot_zone __get_rot_zone)) _get_rot_zone)
  (:serialization-length
   ()
   (+
    ;; int32 _id_input
    4
    ;; bool _get_working_zones
    1
    ;; bool _get_inspection_zones
    1
    ;; bool _get_rot_zone
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _id_input
       (write-long _id_input s)
     ;; bool _get_working_zones
       (if _get_working_zones (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_inspection_zones
       (if _get_inspection_zones (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_rot_zone
       (if _get_rot_zone (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _id_input
     (setq _id_input (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _get_working_zones
     (setq _get_working_zones (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_inspection_zones
     (setq _get_inspection_zones (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_rot_zone
     (setq _get_rot_zone (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass irobot_fcpp_simul::FCPP_inResponse
  :super ros::object
  :slots (_n_defects _herr_lat _herr_proa _herr_popa _long_robotx _long_roboty _tras_herrx _tras_herry _xmin_chapa _xmax_chapa _ymin_chapa _ymax_chapa _poly_i _zone0 _zone90 _zone180 _zone270 _zone_rot ))

(defmethod irobot_fcpp_simul::FCPP_inResponse
  (:init
   (&key
    ((:n_defects __n_defects) 0)
    ((:herr_lat __herr_lat) 0.0)
    ((:herr_proa __herr_proa) 0.0)
    ((:herr_popa __herr_popa) 0.0)
    ((:long_robotx __long_robotx) 0.0)
    ((:long_roboty __long_roboty) 0.0)
    ((:tras_herrx __tras_herrx) 0.0)
    ((:tras_herry __tras_herry) 0.0)
    ((:xmin_chapa __xmin_chapa) 0.0)
    ((:xmax_chapa __xmax_chapa) 0.0)
    ((:ymin_chapa __ymin_chapa) 0.0)
    ((:ymax_chapa __ymax_chapa) 0.0)
    ((:poly_i __poly_i) (instance geometry_msgs::Polygon :init))
    ((:zone0 __zone0) (instance geometry_msgs::Polygon :init))
    ((:zone90 __zone90) (instance geometry_msgs::Polygon :init))
    ((:zone180 __zone180) (instance geometry_msgs::Polygon :init))
    ((:zone270 __zone270) (instance geometry_msgs::Polygon :init))
    ((:zone_rot __zone_rot) (instance geometry_msgs::Polygon :init))
    )
   (send-super :init)
   (setq _n_defects (round __n_defects))
   (setq _herr_lat (float __herr_lat))
   (setq _herr_proa (float __herr_proa))
   (setq _herr_popa (float __herr_popa))
   (setq _long_robotx (float __long_robotx))
   (setq _long_roboty (float __long_roboty))
   (setq _tras_herrx (float __tras_herrx))
   (setq _tras_herry (float __tras_herry))
   (setq _xmin_chapa (float __xmin_chapa))
   (setq _xmax_chapa (float __xmax_chapa))
   (setq _ymin_chapa (float __ymin_chapa))
   (setq _ymax_chapa (float __ymax_chapa))
   (setq _poly_i __poly_i)
   (setq _zone0 __zone0)
   (setq _zone90 __zone90)
   (setq _zone180 __zone180)
   (setq _zone270 __zone270)
   (setq _zone_rot __zone_rot)
   self)
  (:n_defects
   (&optional __n_defects)
   (if __n_defects (setq _n_defects __n_defects)) _n_defects)
  (:herr_lat
   (&optional __herr_lat)
   (if __herr_lat (setq _herr_lat __herr_lat)) _herr_lat)
  (:herr_proa
   (&optional __herr_proa)
   (if __herr_proa (setq _herr_proa __herr_proa)) _herr_proa)
  (:herr_popa
   (&optional __herr_popa)
   (if __herr_popa (setq _herr_popa __herr_popa)) _herr_popa)
  (:long_robotx
   (&optional __long_robotx)
   (if __long_robotx (setq _long_robotx __long_robotx)) _long_robotx)
  (:long_roboty
   (&optional __long_roboty)
   (if __long_roboty (setq _long_roboty __long_roboty)) _long_roboty)
  (:tras_herrx
   (&optional __tras_herrx)
   (if __tras_herrx (setq _tras_herrx __tras_herrx)) _tras_herrx)
  (:tras_herry
   (&optional __tras_herry)
   (if __tras_herry (setq _tras_herry __tras_herry)) _tras_herry)
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
  (:zone_rot
   (&rest __zone_rot)
   (if (keywordp (car __zone_rot))
       (send* _zone_rot __zone_rot)
     (progn
       (if __zone_rot (setq _zone_rot (car __zone_rot)))
       _zone_rot)))
  (:serialization-length
   ()
   (+
    ;; int32 _n_defects
    4
    ;; float32 _herr_lat
    4
    ;; float32 _herr_proa
    4
    ;; float32 _herr_popa
    4
    ;; float32 _long_robotx
    4
    ;; float32 _long_roboty
    4
    ;; float32 _tras_herrx
    4
    ;; float32 _tras_herry
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
    ;; geometry_msgs/Polygon _zone0
    (send _zone0 :serialization-length)
    ;; geometry_msgs/Polygon _zone90
    (send _zone90 :serialization-length)
    ;; geometry_msgs/Polygon _zone180
    (send _zone180 :serialization-length)
    ;; geometry_msgs/Polygon _zone270
    (send _zone270 :serialization-length)
    ;; geometry_msgs/Polygon _zone_rot
    (send _zone_rot :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _n_defects
       (write-long _n_defects s)
     ;; float32 _herr_lat
       (sys::poke _herr_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _herr_proa
       (sys::poke _herr_proa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _herr_popa
       (sys::poke _herr_popa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_robotx
       (sys::poke _long_robotx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_roboty
       (sys::poke _long_roboty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herrx
       (sys::poke _tras_herrx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herry
       (sys::poke _tras_herry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
     ;; geometry_msgs/Polygon _zone0
       (send _zone0 :serialize s)
     ;; geometry_msgs/Polygon _zone90
       (send _zone90 :serialize s)
     ;; geometry_msgs/Polygon _zone180
       (send _zone180 :serialize s)
     ;; geometry_msgs/Polygon _zone270
       (send _zone270 :serialize s)
     ;; geometry_msgs/Polygon _zone_rot
       (send _zone_rot :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _n_defects
     (setq _n_defects (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _herr_lat
     (setq _herr_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _herr_proa
     (setq _herr_proa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _herr_popa
     (setq _herr_popa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_robotx
     (setq _long_robotx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_roboty
     (setq _long_roboty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herrx
     (setq _tras_herrx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herry
     (setq _tras_herry (sys::peek buf ptr- :float)) (incf ptr- 4)
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
   ;; geometry_msgs/Polygon _zone0
     (send _zone0 :deserialize buf ptr-) (incf ptr- (send _zone0 :serialization-length))
   ;; geometry_msgs/Polygon _zone90
     (send _zone90 :deserialize buf ptr-) (incf ptr- (send _zone90 :serialization-length))
   ;; geometry_msgs/Polygon _zone180
     (send _zone180 :deserialize buf ptr-) (incf ptr- (send _zone180 :serialization-length))
   ;; geometry_msgs/Polygon _zone270
     (send _zone270 :deserialize buf ptr-) (incf ptr- (send _zone270 :serialization-length))
   ;; geometry_msgs/Polygon _zone_rot
     (send _zone_rot :deserialize buf ptr-) (incf ptr- (send _zone_rot :serialization-length))
   ;;
   self)
  )

(defclass irobot_fcpp_simul::FCPP_in
  :super ros::object
  :slots ())

(setf (get irobot_fcpp_simul::FCPP_in :md5sum-) "26aa20be26a641c44400aa9da8ffcd13")
(setf (get irobot_fcpp_simul::FCPP_in :datatype-) "irobot_fcpp_simul/FCPP_in")
(setf (get irobot_fcpp_simul::FCPP_in :request) irobot_fcpp_simul::FCPP_inRequest)
(setf (get irobot_fcpp_simul::FCPP_in :response) irobot_fcpp_simul::FCPP_inResponse)

(defmethod irobot_fcpp_simul::FCPP_inRequest
  (:response () (instance irobot_fcpp_simul::FCPP_inResponse :init)))

(setf (get irobot_fcpp_simul::FCPP_inRequest :md5sum-) "26aa20be26a641c44400aa9da8ffcd13")
(setf (get irobot_fcpp_simul::FCPP_inRequest :datatype-) "irobot_fcpp_simul/FCPP_inRequest")
(setf (get irobot_fcpp_simul::FCPP_inRequest :definition-)
      "int32 id_input
bool get_working_zones
bool get_inspection_zones
bool get_rot_zone
---

int32 n_defects


float32 herr_lat
float32 herr_proa
float32 herr_popa


float32 long_robotx
float32 long_roboty
float32 tras_herrx
float32 tras_herry


float32 xmin_chapa
float32 xmax_chapa
float32 ymin_chapa
float32 ymax_chapa


geometry_msgs/Polygon poly_i


geometry_msgs/Polygon zone0
geometry_msgs/Polygon zone90
geometry_msgs/Polygon zone180
geometry_msgs/Polygon zone270



geometry_msgs/Polygon zone_rot



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

(setf (get irobot_fcpp_simul::FCPP_inResponse :md5sum-) "26aa20be26a641c44400aa9da8ffcd13")
(setf (get irobot_fcpp_simul::FCPP_inResponse :datatype-) "irobot_fcpp_simul/FCPP_inResponse")
(setf (get irobot_fcpp_simul::FCPP_inResponse :definition-)
      "int32 id_input
bool get_working_zones
bool get_inspection_zones
bool get_rot_zone
---

int32 n_defects


float32 herr_lat
float32 herr_proa
float32 herr_popa


float32 long_robotx
float32 long_roboty
float32 tras_herrx
float32 tras_herry


float32 xmin_chapa
float32 xmax_chapa
float32 ymin_chapa
float32 ymax_chapa


geometry_msgs/Polygon poly_i


geometry_msgs/Polygon zone0
geometry_msgs/Polygon zone90
geometry_msgs/Polygon zone180
geometry_msgs/Polygon zone270



geometry_msgs/Polygon zone_rot



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



(provide :irobot_fcpp_simul/FCPP_in "26aa20be26a641c44400aa9da8ffcd13")


