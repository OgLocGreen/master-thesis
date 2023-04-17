;; Auto-generated. Do not edit!


(when (boundp 'irobot_fcpp_simul::IROBOT_ir_data)
  (if (not (find-package "IROBOT_FCPP_SIMUL"))
    (make-package "IROBOT_FCPP_SIMUL"))
  (shadow 'IROBOT_ir_data (find-package "IROBOT_FCPP_SIMUL")))
(unless (find-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATA")
  (make-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATA"))
(unless (find-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATAREQUEST")
  (make-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATAREQUEST"))
(unless (find-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATARESPONSE")
  (make-package "IROBOT_FCPP_SIMUL::IROBOT_IR_DATARESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass irobot_fcpp_simul::IROBOT_ir_dataRequest
  :super ros::object
  :slots (_load_inputdata _load_polygon _get_input_data _get_working_zonesh _get_working_zonesc _get_inspection_zones _get_rot_zone _compute_adquireimgs _compute_panorama _merge_panoramas _compute_detectpolys _compute_fcpp_defect_i _compute_fcpp_zone_i _compute_fcpp_inspection_zone_i _execute_fcpp_defect_i _execute_fcpp_zone_i _change_defect_reparation_goal _change_inspection_goal _get_poly_i _get_defect_i _get_defect_path _get_inspection_i _get_inspection_path _activate_vizs _long_robotx _long_roboty _long_herrx _long_herry _tras_herrx _tras_herry _long_camx _long_camy _tras_camx _tras_camy _long_areax _long_areay _input_poly _id_poly _id_defecto _id_zona ))

(defmethod irobot_fcpp_simul::IROBOT_ir_dataRequest
  (:init
   (&key
    ((:load_inputdata __load_inputdata) nil)
    ((:load_polygon __load_polygon) nil)
    ((:get_input_data __get_input_data) nil)
    ((:get_working_zonesh __get_working_zonesh) nil)
    ((:get_working_zonesc __get_working_zonesc) nil)
    ((:get_inspection_zones __get_inspection_zones) nil)
    ((:get_rot_zone __get_rot_zone) nil)
    ((:compute_adquireimgs __compute_adquireimgs) nil)
    ((:compute_panorama __compute_panorama) nil)
    ((:merge_panoramas __merge_panoramas) nil)
    ((:compute_detectpolys __compute_detectpolys) nil)
    ((:compute_fcpp_defect_i __compute_fcpp_defect_i) nil)
    ((:compute_fcpp_zone_i __compute_fcpp_zone_i) nil)
    ((:compute_fcpp_inspection_zone_i __compute_fcpp_inspection_zone_i) nil)
    ((:execute_fcpp_defect_i __execute_fcpp_defect_i) nil)
    ((:execute_fcpp_zone_i __execute_fcpp_zone_i) nil)
    ((:change_defect_reparation_goal __change_defect_reparation_goal) nil)
    ((:change_inspection_goal __change_inspection_goal) nil)
    ((:get_poly_i __get_poly_i) nil)
    ((:get_defect_i __get_defect_i) nil)
    ((:get_defect_path __get_defect_path) nil)
    ((:get_inspection_i __get_inspection_i) nil)
    ((:get_inspection_path __get_inspection_path) nil)
    ((:activate_vizs __activate_vizs) nil)
    ((:long_robotx __long_robotx) 0.0)
    ((:long_roboty __long_roboty) 0.0)
    ((:long_herrx __long_herrx) 0.0)
    ((:long_herry __long_herry) 0.0)
    ((:tras_herrx __tras_herrx) 0.0)
    ((:tras_herry __tras_herry) 0.0)
    ((:long_camx __long_camx) 0.0)
    ((:long_camy __long_camy) 0.0)
    ((:tras_camx __tras_camx) 0.0)
    ((:tras_camy __tras_camy) 0.0)
    ((:long_areax __long_areax) 0.0)
    ((:long_areay __long_areay) 0.0)
    ((:input_poly __input_poly) (instance geometry_msgs::Polygon :init))
    ((:id_poly __id_poly) 0)
    ((:id_defecto __id_defecto) 0)
    ((:id_zona __id_zona) 0)
    )
   (send-super :init)
   (setq _load_inputdata __load_inputdata)
   (setq _load_polygon __load_polygon)
   (setq _get_input_data __get_input_data)
   (setq _get_working_zonesh __get_working_zonesh)
   (setq _get_working_zonesc __get_working_zonesc)
   (setq _get_inspection_zones __get_inspection_zones)
   (setq _get_rot_zone __get_rot_zone)
   (setq _compute_adquireimgs __compute_adquireimgs)
   (setq _compute_panorama __compute_panorama)
   (setq _merge_panoramas __merge_panoramas)
   (setq _compute_detectpolys __compute_detectpolys)
   (setq _compute_fcpp_defect_i __compute_fcpp_defect_i)
   (setq _compute_fcpp_zone_i __compute_fcpp_zone_i)
   (setq _compute_fcpp_inspection_zone_i __compute_fcpp_inspection_zone_i)
   (setq _execute_fcpp_defect_i __execute_fcpp_defect_i)
   (setq _execute_fcpp_zone_i __execute_fcpp_zone_i)
   (setq _change_defect_reparation_goal __change_defect_reparation_goal)
   (setq _change_inspection_goal __change_inspection_goal)
   (setq _get_poly_i __get_poly_i)
   (setq _get_defect_i __get_defect_i)
   (setq _get_defect_path __get_defect_path)
   (setq _get_inspection_i __get_inspection_i)
   (setq _get_inspection_path __get_inspection_path)
   (setq _activate_vizs __activate_vizs)
   (setq _long_robotx (float __long_robotx))
   (setq _long_roboty (float __long_roboty))
   (setq _long_herrx (float __long_herrx))
   (setq _long_herry (float __long_herry))
   (setq _tras_herrx (float __tras_herrx))
   (setq _tras_herry (float __tras_herry))
   (setq _long_camx (float __long_camx))
   (setq _long_camy (float __long_camy))
   (setq _tras_camx (float __tras_camx))
   (setq _tras_camy (float __tras_camy))
   (setq _long_areax (float __long_areax))
   (setq _long_areay (float __long_areay))
   (setq _input_poly __input_poly)
   (setq _id_poly (round __id_poly))
   (setq _id_defecto (round __id_defecto))
   (setq _id_zona (round __id_zona))
   self)
  (:load_inputdata
   (&optional __load_inputdata)
   (if __load_inputdata (setq _load_inputdata __load_inputdata)) _load_inputdata)
  (:load_polygon
   (&optional __load_polygon)
   (if __load_polygon (setq _load_polygon __load_polygon)) _load_polygon)
  (:get_input_data
   (&optional __get_input_data)
   (if __get_input_data (setq _get_input_data __get_input_data)) _get_input_data)
  (:get_working_zonesh
   (&optional __get_working_zonesh)
   (if __get_working_zonesh (setq _get_working_zonesh __get_working_zonesh)) _get_working_zonesh)
  (:get_working_zonesc
   (&optional __get_working_zonesc)
   (if __get_working_zonesc (setq _get_working_zonesc __get_working_zonesc)) _get_working_zonesc)
  (:get_inspection_zones
   (&optional __get_inspection_zones)
   (if __get_inspection_zones (setq _get_inspection_zones __get_inspection_zones)) _get_inspection_zones)
  (:get_rot_zone
   (&optional __get_rot_zone)
   (if __get_rot_zone (setq _get_rot_zone __get_rot_zone)) _get_rot_zone)
  (:compute_adquireimgs
   (&optional __compute_adquireimgs)
   (if __compute_adquireimgs (setq _compute_adquireimgs __compute_adquireimgs)) _compute_adquireimgs)
  (:compute_panorama
   (&optional __compute_panorama)
   (if __compute_panorama (setq _compute_panorama __compute_panorama)) _compute_panorama)
  (:merge_panoramas
   (&optional __merge_panoramas)
   (if __merge_panoramas (setq _merge_panoramas __merge_panoramas)) _merge_panoramas)
  (:compute_detectpolys
   (&optional __compute_detectpolys)
   (if __compute_detectpolys (setq _compute_detectpolys __compute_detectpolys)) _compute_detectpolys)
  (:compute_fcpp_defect_i
   (&optional __compute_fcpp_defect_i)
   (if __compute_fcpp_defect_i (setq _compute_fcpp_defect_i __compute_fcpp_defect_i)) _compute_fcpp_defect_i)
  (:compute_fcpp_zone_i
   (&optional __compute_fcpp_zone_i)
   (if __compute_fcpp_zone_i (setq _compute_fcpp_zone_i __compute_fcpp_zone_i)) _compute_fcpp_zone_i)
  (:compute_fcpp_inspection_zone_i
   (&optional __compute_fcpp_inspection_zone_i)
   (if __compute_fcpp_inspection_zone_i (setq _compute_fcpp_inspection_zone_i __compute_fcpp_inspection_zone_i)) _compute_fcpp_inspection_zone_i)
  (:execute_fcpp_defect_i
   (&optional __execute_fcpp_defect_i)
   (if __execute_fcpp_defect_i (setq _execute_fcpp_defect_i __execute_fcpp_defect_i)) _execute_fcpp_defect_i)
  (:execute_fcpp_zone_i
   (&optional __execute_fcpp_zone_i)
   (if __execute_fcpp_zone_i (setq _execute_fcpp_zone_i __execute_fcpp_zone_i)) _execute_fcpp_zone_i)
  (:change_defect_reparation_goal
   (&optional __change_defect_reparation_goal)
   (if __change_defect_reparation_goal (setq _change_defect_reparation_goal __change_defect_reparation_goal)) _change_defect_reparation_goal)
  (:change_inspection_goal
   (&optional __change_inspection_goal)
   (if __change_inspection_goal (setq _change_inspection_goal __change_inspection_goal)) _change_inspection_goal)
  (:get_poly_i
   (&optional __get_poly_i)
   (if __get_poly_i (setq _get_poly_i __get_poly_i)) _get_poly_i)
  (:get_defect_i
   (&optional __get_defect_i)
   (if __get_defect_i (setq _get_defect_i __get_defect_i)) _get_defect_i)
  (:get_defect_path
   (&optional __get_defect_path)
   (if __get_defect_path (setq _get_defect_path __get_defect_path)) _get_defect_path)
  (:get_inspection_i
   (&optional __get_inspection_i)
   (if __get_inspection_i (setq _get_inspection_i __get_inspection_i)) _get_inspection_i)
  (:get_inspection_path
   (&optional __get_inspection_path)
   (if __get_inspection_path (setq _get_inspection_path __get_inspection_path)) _get_inspection_path)
  (:activate_vizs
   (&optional __activate_vizs)
   (if __activate_vizs (setq _activate_vizs __activate_vizs)) _activate_vizs)
  (:long_robotx
   (&optional __long_robotx)
   (if __long_robotx (setq _long_robotx __long_robotx)) _long_robotx)
  (:long_roboty
   (&optional __long_roboty)
   (if __long_roboty (setq _long_roboty __long_roboty)) _long_roboty)
  (:long_herrx
   (&optional __long_herrx)
   (if __long_herrx (setq _long_herrx __long_herrx)) _long_herrx)
  (:long_herry
   (&optional __long_herry)
   (if __long_herry (setq _long_herry __long_herry)) _long_herry)
  (:tras_herrx
   (&optional __tras_herrx)
   (if __tras_herrx (setq _tras_herrx __tras_herrx)) _tras_herrx)
  (:tras_herry
   (&optional __tras_herry)
   (if __tras_herry (setq _tras_herry __tras_herry)) _tras_herry)
  (:long_camx
   (&optional __long_camx)
   (if __long_camx (setq _long_camx __long_camx)) _long_camx)
  (:long_camy
   (&optional __long_camy)
   (if __long_camy (setq _long_camy __long_camy)) _long_camy)
  (:tras_camx
   (&optional __tras_camx)
   (if __tras_camx (setq _tras_camx __tras_camx)) _tras_camx)
  (:tras_camy
   (&optional __tras_camy)
   (if __tras_camy (setq _tras_camy __tras_camy)) _tras_camy)
  (:long_areax
   (&optional __long_areax)
   (if __long_areax (setq _long_areax __long_areax)) _long_areax)
  (:long_areay
   (&optional __long_areay)
   (if __long_areay (setq _long_areay __long_areay)) _long_areay)
  (:input_poly
   (&rest __input_poly)
   (if (keywordp (car __input_poly))
       (send* _input_poly __input_poly)
     (progn
       (if __input_poly (setq _input_poly (car __input_poly)))
       _input_poly)))
  (:id_poly
   (&optional __id_poly)
   (if __id_poly (setq _id_poly __id_poly)) _id_poly)
  (:id_defecto
   (&optional __id_defecto)
   (if __id_defecto (setq _id_defecto __id_defecto)) _id_defecto)
  (:id_zona
   (&optional __id_zona)
   (if __id_zona (setq _id_zona __id_zona)) _id_zona)
  (:serialization-length
   ()
   (+
    ;; bool _load_inputdata
    1
    ;; bool _load_polygon
    1
    ;; bool _get_input_data
    1
    ;; bool _get_working_zonesh
    1
    ;; bool _get_working_zonesc
    1
    ;; bool _get_inspection_zones
    1
    ;; bool _get_rot_zone
    1
    ;; bool _compute_adquireimgs
    1
    ;; bool _compute_panorama
    1
    ;; bool _merge_panoramas
    1
    ;; bool _compute_detectpolys
    1
    ;; bool _compute_fcpp_defect_i
    1
    ;; bool _compute_fcpp_zone_i
    1
    ;; bool _compute_fcpp_inspection_zone_i
    1
    ;; bool _execute_fcpp_defect_i
    1
    ;; bool _execute_fcpp_zone_i
    1
    ;; bool _change_defect_reparation_goal
    1
    ;; bool _change_inspection_goal
    1
    ;; bool _get_poly_i
    1
    ;; bool _get_defect_i
    1
    ;; bool _get_defect_path
    1
    ;; bool _get_inspection_i
    1
    ;; bool _get_inspection_path
    1
    ;; bool _activate_vizs
    1
    ;; float32 _long_robotx
    4
    ;; float32 _long_roboty
    4
    ;; float32 _long_herrx
    4
    ;; float32 _long_herry
    4
    ;; float32 _tras_herrx
    4
    ;; float32 _tras_herry
    4
    ;; float32 _long_camx
    4
    ;; float32 _long_camy
    4
    ;; float32 _tras_camx
    4
    ;; float32 _tras_camy
    4
    ;; float32 _long_areax
    4
    ;; float32 _long_areay
    4
    ;; geometry_msgs/Polygon _input_poly
    (send _input_poly :serialization-length)
    ;; int32 _id_poly
    4
    ;; int32 _id_defecto
    4
    ;; int32 _id_zona
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _load_inputdata
       (if _load_inputdata (write-byte -1 s) (write-byte 0 s))
     ;; bool _load_polygon
       (if _load_polygon (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_input_data
       (if _get_input_data (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_working_zonesh
       (if _get_working_zonesh (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_working_zonesc
       (if _get_working_zonesc (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_inspection_zones
       (if _get_inspection_zones (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_rot_zone
       (if _get_rot_zone (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_adquireimgs
       (if _compute_adquireimgs (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_panorama
       (if _compute_panorama (write-byte -1 s) (write-byte 0 s))
     ;; bool _merge_panoramas
       (if _merge_panoramas (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_detectpolys
       (if _compute_detectpolys (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_fcpp_defect_i
       (if _compute_fcpp_defect_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_fcpp_zone_i
       (if _compute_fcpp_zone_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _compute_fcpp_inspection_zone_i
       (if _compute_fcpp_inspection_zone_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _execute_fcpp_defect_i
       (if _execute_fcpp_defect_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _execute_fcpp_zone_i
       (if _execute_fcpp_zone_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _change_defect_reparation_goal
       (if _change_defect_reparation_goal (write-byte -1 s) (write-byte 0 s))
     ;; bool _change_inspection_goal
       (if _change_inspection_goal (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_poly_i
       (if _get_poly_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_defect_i
       (if _get_defect_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_defect_path
       (if _get_defect_path (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_inspection_i
       (if _get_inspection_i (write-byte -1 s) (write-byte 0 s))
     ;; bool _get_inspection_path
       (if _get_inspection_path (write-byte -1 s) (write-byte 0 s))
     ;; bool _activate_vizs
       (if _activate_vizs (write-byte -1 s) (write-byte 0 s))
     ;; float32 _long_robotx
       (sys::poke _long_robotx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_roboty
       (sys::poke _long_roboty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_herrx
       (sys::poke _long_herrx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_herry
       (sys::poke _long_herry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herrx
       (sys::poke _tras_herrx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herry
       (sys::poke _tras_herry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_camx
       (sys::poke _long_camx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_camy
       (sys::poke _long_camy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_camx
       (sys::poke _tras_camx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_camy
       (sys::poke _tras_camy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_areax
       (sys::poke _long_areax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_areay
       (sys::poke _long_areay (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Polygon _input_poly
       (send _input_poly :serialize s)
     ;; int32 _id_poly
       (write-long _id_poly s)
     ;; int32 _id_defecto
       (write-long _id_defecto s)
     ;; int32 _id_zona
       (write-long _id_zona s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _load_inputdata
     (setq _load_inputdata (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _load_polygon
     (setq _load_polygon (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_input_data
     (setq _get_input_data (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_working_zonesh
     (setq _get_working_zonesh (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_working_zonesc
     (setq _get_working_zonesc (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_inspection_zones
     (setq _get_inspection_zones (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_rot_zone
     (setq _get_rot_zone (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_adquireimgs
     (setq _compute_adquireimgs (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_panorama
     (setq _compute_panorama (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _merge_panoramas
     (setq _merge_panoramas (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_detectpolys
     (setq _compute_detectpolys (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_fcpp_defect_i
     (setq _compute_fcpp_defect_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_fcpp_zone_i
     (setq _compute_fcpp_zone_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _compute_fcpp_inspection_zone_i
     (setq _compute_fcpp_inspection_zone_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _execute_fcpp_defect_i
     (setq _execute_fcpp_defect_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _execute_fcpp_zone_i
     (setq _execute_fcpp_zone_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _change_defect_reparation_goal
     (setq _change_defect_reparation_goal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _change_inspection_goal
     (setq _change_inspection_goal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_poly_i
     (setq _get_poly_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_defect_i
     (setq _get_defect_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_defect_path
     (setq _get_defect_path (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_inspection_i
     (setq _get_inspection_i (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _get_inspection_path
     (setq _get_inspection_path (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _activate_vizs
     (setq _activate_vizs (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _long_robotx
     (setq _long_robotx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_roboty
     (setq _long_roboty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_herrx
     (setq _long_herrx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_herry
     (setq _long_herry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herrx
     (setq _tras_herrx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herry
     (setq _tras_herry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_camx
     (setq _long_camx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_camy
     (setq _long_camy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_camx
     (setq _tras_camx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_camy
     (setq _tras_camy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_areax
     (setq _long_areax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_areay
     (setq _long_areay (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Polygon _input_poly
     (send _input_poly :deserialize buf ptr-) (incf ptr- (send _input_poly :serialization-length))
   ;; int32 _id_poly
     (setq _id_poly (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _id_defecto
     (setq _id_defecto (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _id_zona
     (setq _id_zona (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass irobot_fcpp_simul::IROBOT_ir_dataResponse
  :super ros::object
  :slots (_long_robotx _long_roboty _long_herrx _long_herry _tras_herrx _tras_herry _long_camx _long_camy _tras_camx _tras_camy _long_areax _long_areay _zoneh0 _zoneh90 _zoneh180 _zoneh270 _zonec0 _zonec90 _zonec180 _zonec270 _path_tray0 _path_tray90 _path_tray180 _path_tray270 _zone_rot _defecto_i _poly_i _n_defectos _defect_i_paths _inspection_i_paths ))

(defmethod irobot_fcpp_simul::IROBOT_ir_dataResponse
  (:init
   (&key
    ((:long_robotx __long_robotx) 0.0)
    ((:long_roboty __long_roboty) 0.0)
    ((:long_herrx __long_herrx) 0.0)
    ((:long_herry __long_herry) 0.0)
    ((:tras_herrx __tras_herrx) 0.0)
    ((:tras_herry __tras_herry) 0.0)
    ((:long_camx __long_camx) 0.0)
    ((:long_camy __long_camy) 0.0)
    ((:tras_camx __tras_camx) 0.0)
    ((:tras_camy __tras_camy) 0.0)
    ((:long_areax __long_areax) 0.0)
    ((:long_areay __long_areay) 0.0)
    ((:zoneh0 __zoneh0) (instance geometry_msgs::Polygon :init))
    ((:zoneh90 __zoneh90) (instance geometry_msgs::Polygon :init))
    ((:zoneh180 __zoneh180) (instance geometry_msgs::Polygon :init))
    ((:zoneh270 __zoneh270) (instance geometry_msgs::Polygon :init))
    ((:zonec0 __zonec0) (instance geometry_msgs::Polygon :init))
    ((:zonec90 __zonec90) (instance geometry_msgs::Polygon :init))
    ((:zonec180 __zonec180) (instance geometry_msgs::Polygon :init))
    ((:zonec270 __zonec270) (instance geometry_msgs::Polygon :init))
    ((:path_tray0 __path_tray0) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    ((:path_tray90 __path_tray90) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    ((:path_tray180 __path_tray180) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    ((:path_tray270 __path_tray270) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    ((:zone_rot __zone_rot) (instance geometry_msgs::Polygon :init))
    ((:defecto_i __defecto_i) (instance irobot_fcpp_simul::defecto :init))
    ((:poly_i __poly_i) (instance geometry_msgs::Polygon :init))
    ((:n_defectos __n_defectos) 0)
    ((:defect_i_paths __defect_i_paths) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    ((:inspection_i_paths __inspection_i_paths) (let (r) (dotimes (i 0) (push (instance geometry_msgs::PoseArray :init) r)) r))
    )
   (send-super :init)
   (setq _long_robotx (float __long_robotx))
   (setq _long_roboty (float __long_roboty))
   (setq _long_herrx (float __long_herrx))
   (setq _long_herry (float __long_herry))
   (setq _tras_herrx (float __tras_herrx))
   (setq _tras_herry (float __tras_herry))
   (setq _long_camx (float __long_camx))
   (setq _long_camy (float __long_camy))
   (setq _tras_camx (float __tras_camx))
   (setq _tras_camy (float __tras_camy))
   (setq _long_areax (float __long_areax))
   (setq _long_areay (float __long_areay))
   (setq _zoneh0 __zoneh0)
   (setq _zoneh90 __zoneh90)
   (setq _zoneh180 __zoneh180)
   (setq _zoneh270 __zoneh270)
   (setq _zonec0 __zonec0)
   (setq _zonec90 __zonec90)
   (setq _zonec180 __zonec180)
   (setq _zonec270 __zonec270)
   (setq _path_tray0 __path_tray0)
   (setq _path_tray90 __path_tray90)
   (setq _path_tray180 __path_tray180)
   (setq _path_tray270 __path_tray270)
   (setq _zone_rot __zone_rot)
   (setq _defecto_i __defecto_i)
   (setq _poly_i __poly_i)
   (setq _n_defectos (round __n_defectos))
   (setq _defect_i_paths __defect_i_paths)
   (setq _inspection_i_paths __inspection_i_paths)
   self)
  (:long_robotx
   (&optional __long_robotx)
   (if __long_robotx (setq _long_robotx __long_robotx)) _long_robotx)
  (:long_roboty
   (&optional __long_roboty)
   (if __long_roboty (setq _long_roboty __long_roboty)) _long_roboty)
  (:long_herrx
   (&optional __long_herrx)
   (if __long_herrx (setq _long_herrx __long_herrx)) _long_herrx)
  (:long_herry
   (&optional __long_herry)
   (if __long_herry (setq _long_herry __long_herry)) _long_herry)
  (:tras_herrx
   (&optional __tras_herrx)
   (if __tras_herrx (setq _tras_herrx __tras_herrx)) _tras_herrx)
  (:tras_herry
   (&optional __tras_herry)
   (if __tras_herry (setq _tras_herry __tras_herry)) _tras_herry)
  (:long_camx
   (&optional __long_camx)
   (if __long_camx (setq _long_camx __long_camx)) _long_camx)
  (:long_camy
   (&optional __long_camy)
   (if __long_camy (setq _long_camy __long_camy)) _long_camy)
  (:tras_camx
   (&optional __tras_camx)
   (if __tras_camx (setq _tras_camx __tras_camx)) _tras_camx)
  (:tras_camy
   (&optional __tras_camy)
   (if __tras_camy (setq _tras_camy __tras_camy)) _tras_camy)
  (:long_areax
   (&optional __long_areax)
   (if __long_areax (setq _long_areax __long_areax)) _long_areax)
  (:long_areay
   (&optional __long_areay)
   (if __long_areay (setq _long_areay __long_areay)) _long_areay)
  (:zoneh0
   (&rest __zoneh0)
   (if (keywordp (car __zoneh0))
       (send* _zoneh0 __zoneh0)
     (progn
       (if __zoneh0 (setq _zoneh0 (car __zoneh0)))
       _zoneh0)))
  (:zoneh90
   (&rest __zoneh90)
   (if (keywordp (car __zoneh90))
       (send* _zoneh90 __zoneh90)
     (progn
       (if __zoneh90 (setq _zoneh90 (car __zoneh90)))
       _zoneh90)))
  (:zoneh180
   (&rest __zoneh180)
   (if (keywordp (car __zoneh180))
       (send* _zoneh180 __zoneh180)
     (progn
       (if __zoneh180 (setq _zoneh180 (car __zoneh180)))
       _zoneh180)))
  (:zoneh270
   (&rest __zoneh270)
   (if (keywordp (car __zoneh270))
       (send* _zoneh270 __zoneh270)
     (progn
       (if __zoneh270 (setq _zoneh270 (car __zoneh270)))
       _zoneh270)))
  (:zonec0
   (&rest __zonec0)
   (if (keywordp (car __zonec0))
       (send* _zonec0 __zonec0)
     (progn
       (if __zonec0 (setq _zonec0 (car __zonec0)))
       _zonec0)))
  (:zonec90
   (&rest __zonec90)
   (if (keywordp (car __zonec90))
       (send* _zonec90 __zonec90)
     (progn
       (if __zonec90 (setq _zonec90 (car __zonec90)))
       _zonec90)))
  (:zonec180
   (&rest __zonec180)
   (if (keywordp (car __zonec180))
       (send* _zonec180 __zonec180)
     (progn
       (if __zonec180 (setq _zonec180 (car __zonec180)))
       _zonec180)))
  (:zonec270
   (&rest __zonec270)
   (if (keywordp (car __zonec270))
       (send* _zonec270 __zonec270)
     (progn
       (if __zonec270 (setq _zonec270 (car __zonec270)))
       _zonec270)))
  (:path_tray0
   (&rest __path_tray0)
   (if (keywordp (car __path_tray0))
       (send* _path_tray0 __path_tray0)
     (progn
       (if __path_tray0 (setq _path_tray0 (car __path_tray0)))
       _path_tray0)))
  (:path_tray90
   (&rest __path_tray90)
   (if (keywordp (car __path_tray90))
       (send* _path_tray90 __path_tray90)
     (progn
       (if __path_tray90 (setq _path_tray90 (car __path_tray90)))
       _path_tray90)))
  (:path_tray180
   (&rest __path_tray180)
   (if (keywordp (car __path_tray180))
       (send* _path_tray180 __path_tray180)
     (progn
       (if __path_tray180 (setq _path_tray180 (car __path_tray180)))
       _path_tray180)))
  (:path_tray270
   (&rest __path_tray270)
   (if (keywordp (car __path_tray270))
       (send* _path_tray270 __path_tray270)
     (progn
       (if __path_tray270 (setq _path_tray270 (car __path_tray270)))
       _path_tray270)))
  (:zone_rot
   (&rest __zone_rot)
   (if (keywordp (car __zone_rot))
       (send* _zone_rot __zone_rot)
     (progn
       (if __zone_rot (setq _zone_rot (car __zone_rot)))
       _zone_rot)))
  (:defecto_i
   (&rest __defecto_i)
   (if (keywordp (car __defecto_i))
       (send* _defecto_i __defecto_i)
     (progn
       (if __defecto_i (setq _defecto_i (car __defecto_i)))
       _defecto_i)))
  (:poly_i
   (&rest __poly_i)
   (if (keywordp (car __poly_i))
       (send* _poly_i __poly_i)
     (progn
       (if __poly_i (setq _poly_i (car __poly_i)))
       _poly_i)))
  (:n_defectos
   (&optional __n_defectos)
   (if __n_defectos (setq _n_defectos __n_defectos)) _n_defectos)
  (:defect_i_paths
   (&rest __defect_i_paths)
   (if (keywordp (car __defect_i_paths))
       (send* _defect_i_paths __defect_i_paths)
     (progn
       (if __defect_i_paths (setq _defect_i_paths (car __defect_i_paths)))
       _defect_i_paths)))
  (:inspection_i_paths
   (&rest __inspection_i_paths)
   (if (keywordp (car __inspection_i_paths))
       (send* _inspection_i_paths __inspection_i_paths)
     (progn
       (if __inspection_i_paths (setq _inspection_i_paths (car __inspection_i_paths)))
       _inspection_i_paths)))
  (:serialization-length
   ()
   (+
    ;; float32 _long_robotx
    4
    ;; float32 _long_roboty
    4
    ;; float32 _long_herrx
    4
    ;; float32 _long_herry
    4
    ;; float32 _tras_herrx
    4
    ;; float32 _tras_herry
    4
    ;; float32 _long_camx
    4
    ;; float32 _long_camy
    4
    ;; float32 _tras_camx
    4
    ;; float32 _tras_camy
    4
    ;; float32 _long_areax
    4
    ;; float32 _long_areay
    4
    ;; geometry_msgs/Polygon _zoneh0
    (send _zoneh0 :serialization-length)
    ;; geometry_msgs/Polygon _zoneh90
    (send _zoneh90 :serialization-length)
    ;; geometry_msgs/Polygon _zoneh180
    (send _zoneh180 :serialization-length)
    ;; geometry_msgs/Polygon _zoneh270
    (send _zoneh270 :serialization-length)
    ;; geometry_msgs/Polygon _zonec0
    (send _zonec0 :serialization-length)
    ;; geometry_msgs/Polygon _zonec90
    (send _zonec90 :serialization-length)
    ;; geometry_msgs/Polygon _zonec180
    (send _zonec180 :serialization-length)
    ;; geometry_msgs/Polygon _zonec270
    (send _zonec270 :serialization-length)
    ;; geometry_msgs/PoseArray[] _path_tray0
    (apply #'+ (send-all _path_tray0 :serialization-length)) 4
    ;; geometry_msgs/PoseArray[] _path_tray90
    (apply #'+ (send-all _path_tray90 :serialization-length)) 4
    ;; geometry_msgs/PoseArray[] _path_tray180
    (apply #'+ (send-all _path_tray180 :serialization-length)) 4
    ;; geometry_msgs/PoseArray[] _path_tray270
    (apply #'+ (send-all _path_tray270 :serialization-length)) 4
    ;; geometry_msgs/Polygon _zone_rot
    (send _zone_rot :serialization-length)
    ;; irobot_fcpp_simul/defecto _defecto_i
    (send _defecto_i :serialization-length)
    ;; geometry_msgs/Polygon _poly_i
    (send _poly_i :serialization-length)
    ;; int32 _n_defectos
    4
    ;; geometry_msgs/PoseArray[] _defect_i_paths
    (apply #'+ (send-all _defect_i_paths :serialization-length)) 4
    ;; geometry_msgs/PoseArray[] _inspection_i_paths
    (apply #'+ (send-all _inspection_i_paths :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _long_robotx
       (sys::poke _long_robotx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_roboty
       (sys::poke _long_roboty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_herrx
       (sys::poke _long_herrx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_herry
       (sys::poke _long_herry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herrx
       (sys::poke _tras_herrx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_herry
       (sys::poke _tras_herry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_camx
       (sys::poke _long_camx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_camy
       (sys::poke _long_camy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_camx
       (sys::poke _tras_camx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tras_camy
       (sys::poke _tras_camy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_areax
       (sys::poke _long_areax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _long_areay
       (sys::poke _long_areay (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Polygon _zoneh0
       (send _zoneh0 :serialize s)
     ;; geometry_msgs/Polygon _zoneh90
       (send _zoneh90 :serialize s)
     ;; geometry_msgs/Polygon _zoneh180
       (send _zoneh180 :serialize s)
     ;; geometry_msgs/Polygon _zoneh270
       (send _zoneh270 :serialize s)
     ;; geometry_msgs/Polygon _zonec0
       (send _zonec0 :serialize s)
     ;; geometry_msgs/Polygon _zonec90
       (send _zonec90 :serialize s)
     ;; geometry_msgs/Polygon _zonec180
       (send _zonec180 :serialize s)
     ;; geometry_msgs/Polygon _zonec270
       (send _zonec270 :serialize s)
     ;; geometry_msgs/PoseArray[] _path_tray0
     (write-long (length _path_tray0) s)
     (dolist (elem _path_tray0)
       (send elem :serialize s)
       )
     ;; geometry_msgs/PoseArray[] _path_tray90
     (write-long (length _path_tray90) s)
     (dolist (elem _path_tray90)
       (send elem :serialize s)
       )
     ;; geometry_msgs/PoseArray[] _path_tray180
     (write-long (length _path_tray180) s)
     (dolist (elem _path_tray180)
       (send elem :serialize s)
       )
     ;; geometry_msgs/PoseArray[] _path_tray270
     (write-long (length _path_tray270) s)
     (dolist (elem _path_tray270)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Polygon _zone_rot
       (send _zone_rot :serialize s)
     ;; irobot_fcpp_simul/defecto _defecto_i
       (send _defecto_i :serialize s)
     ;; geometry_msgs/Polygon _poly_i
       (send _poly_i :serialize s)
     ;; int32 _n_defectos
       (write-long _n_defectos s)
     ;; geometry_msgs/PoseArray[] _defect_i_paths
     (write-long (length _defect_i_paths) s)
     (dolist (elem _defect_i_paths)
       (send elem :serialize s)
       )
     ;; geometry_msgs/PoseArray[] _inspection_i_paths
     (write-long (length _inspection_i_paths) s)
     (dolist (elem _inspection_i_paths)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _long_robotx
     (setq _long_robotx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_roboty
     (setq _long_roboty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_herrx
     (setq _long_herrx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_herry
     (setq _long_herry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herrx
     (setq _tras_herrx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_herry
     (setq _tras_herry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_camx
     (setq _long_camx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_camy
     (setq _long_camy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_camx
     (setq _tras_camx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tras_camy
     (setq _tras_camy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_areax
     (setq _long_areax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _long_areay
     (setq _long_areay (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Polygon _zoneh0
     (send _zoneh0 :deserialize buf ptr-) (incf ptr- (send _zoneh0 :serialization-length))
   ;; geometry_msgs/Polygon _zoneh90
     (send _zoneh90 :deserialize buf ptr-) (incf ptr- (send _zoneh90 :serialization-length))
   ;; geometry_msgs/Polygon _zoneh180
     (send _zoneh180 :deserialize buf ptr-) (incf ptr- (send _zoneh180 :serialization-length))
   ;; geometry_msgs/Polygon _zoneh270
     (send _zoneh270 :deserialize buf ptr-) (incf ptr- (send _zoneh270 :serialization-length))
   ;; geometry_msgs/Polygon _zonec0
     (send _zonec0 :deserialize buf ptr-) (incf ptr- (send _zonec0 :serialization-length))
   ;; geometry_msgs/Polygon _zonec90
     (send _zonec90 :deserialize buf ptr-) (incf ptr- (send _zonec90 :serialization-length))
   ;; geometry_msgs/Polygon _zonec180
     (send _zonec180 :deserialize buf ptr-) (incf ptr- (send _zonec180 :serialization-length))
   ;; geometry_msgs/Polygon _zonec270
     (send _zonec270 :deserialize buf ptr-) (incf ptr- (send _zonec270 :serialization-length))
   ;; geometry_msgs/PoseArray[] _path_tray0
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _path_tray0 (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _path_tray0)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/PoseArray[] _path_tray90
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _path_tray90 (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _path_tray90)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/PoseArray[] _path_tray180
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _path_tray180 (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _path_tray180)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/PoseArray[] _path_tray270
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _path_tray270 (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _path_tray270)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Polygon _zone_rot
     (send _zone_rot :deserialize buf ptr-) (incf ptr- (send _zone_rot :serialization-length))
   ;; irobot_fcpp_simul/defecto _defecto_i
     (send _defecto_i :deserialize buf ptr-) (incf ptr- (send _defecto_i :serialization-length))
   ;; geometry_msgs/Polygon _poly_i
     (send _poly_i :deserialize buf ptr-) (incf ptr- (send _poly_i :serialization-length))
   ;; int32 _n_defectos
     (setq _n_defectos (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/PoseArray[] _defect_i_paths
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _defect_i_paths (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _defect_i_paths)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/PoseArray[] _inspection_i_paths
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _inspection_i_paths (let (r) (dotimes (i n) (push (instance geometry_msgs::PoseArray :init) r)) r))
     (dolist (elem- _inspection_i_paths)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass irobot_fcpp_simul::IROBOT_ir_data
  :super ros::object
  :slots ())

(setf (get irobot_fcpp_simul::IROBOT_ir_data :md5sum-) "7a9f483678423eac1cf4e98d3bca8c59")
(setf (get irobot_fcpp_simul::IROBOT_ir_data :datatype-) "irobot_fcpp_simul/IROBOT_ir_data")
(setf (get irobot_fcpp_simul::IROBOT_ir_data :request) irobot_fcpp_simul::IROBOT_ir_dataRequest)
(setf (get irobot_fcpp_simul::IROBOT_ir_data :response) irobot_fcpp_simul::IROBOT_ir_dataResponse)

(defmethod irobot_fcpp_simul::IROBOT_ir_dataRequest
  (:response () (instance irobot_fcpp_simul::IROBOT_ir_dataResponse :init)))

(setf (get irobot_fcpp_simul::IROBOT_ir_dataRequest :md5sum-) "7a9f483678423eac1cf4e98d3bca8c59")
(setf (get irobot_fcpp_simul::IROBOT_ir_dataRequest :datatype-) "irobot_fcpp_simul/IROBOT_ir_dataRequest")
(setf (get irobot_fcpp_simul::IROBOT_ir_dataRequest :definition-)
      "bool load_inputdata
bool load_polygon

bool get_input_data
bool get_working_zonesh
bool get_working_zonesc
bool get_inspection_zones
bool get_rot_zone


bool compute_adquireimgs
bool compute_panorama
bool merge_panoramas
bool compute_detectpolys

bool compute_fcpp_defect_i
bool compute_fcpp_zone_i
bool compute_fcpp_inspection_zone_i

bool execute_fcpp_defect_i
bool execute_fcpp_zone_i

bool change_defect_reparation_goal
bool change_inspection_goal


bool get_poly_i
bool get_defect_i
bool get_defect_path

bool get_inspection_i
bool get_inspection_path

bool activate_vizs


float32 long_robotx
float32 long_roboty


float32 long_herrx
float32 long_herry
float32 tras_herrx
float32 tras_herry


float32 long_camx
float32 long_camy
float32 tras_camx
float32 tras_camy


float32 long_areax
float32 long_areay


geometry_msgs/Polygon input_poly


int32 id_poly


int32 id_defecto


int32 id_zona



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
---


float32 long_robotx
float32 long_roboty


float32 long_herrx
float32 long_herry
float32 tras_herrx
float32 tras_herry


float32 long_camx
float32 long_camy
float32 tras_camx
float32 tras_camy


float32 long_areax
float32 long_areay


geometry_msgs/Polygon zoneh0
geometry_msgs/Polygon zoneh90
geometry_msgs/Polygon zoneh180
geometry_msgs/Polygon zoneh270


geometry_msgs/Polygon zonec0
geometry_msgs/Polygon zonec90
geometry_msgs/Polygon zonec180
geometry_msgs/Polygon zonec270


geometry_msgs/PoseArray[] path_tray0
geometry_msgs/PoseArray[] path_tray90
geometry_msgs/PoseArray[] path_tray180
geometry_msgs/PoseArray[] path_tray270



geometry_msgs/Polygon zone_rot


defecto defecto_i
geometry_msgs/Polygon poly_i
int32 n_defectos

geometry_msgs/PoseArray[] defect_i_paths
geometry_msgs/PoseArray[] inspection_i_paths



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
MSG: geometry_msgs/PoseArray
# An array of poses with a header for global reference.

Header header

Pose[] poses

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: irobot_fcpp_simul/defecto
geometry_msgs/Polygon ros_poly
defecto_zona[] defecto_divpor_zonas

bool reparado

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

(setf (get irobot_fcpp_simul::IROBOT_ir_dataResponse :md5sum-) "7a9f483678423eac1cf4e98d3bca8c59")
(setf (get irobot_fcpp_simul::IROBOT_ir_dataResponse :datatype-) "irobot_fcpp_simul/IROBOT_ir_dataResponse")
(setf (get irobot_fcpp_simul::IROBOT_ir_dataResponse :definition-)
      "bool load_inputdata
bool load_polygon

bool get_input_data
bool get_working_zonesh
bool get_working_zonesc
bool get_inspection_zones
bool get_rot_zone


bool compute_adquireimgs
bool compute_panorama
bool merge_panoramas
bool compute_detectpolys

bool compute_fcpp_defect_i
bool compute_fcpp_zone_i
bool compute_fcpp_inspection_zone_i

bool execute_fcpp_defect_i
bool execute_fcpp_zone_i

bool change_defect_reparation_goal
bool change_inspection_goal


bool get_poly_i
bool get_defect_i
bool get_defect_path

bool get_inspection_i
bool get_inspection_path

bool activate_vizs


float32 long_robotx
float32 long_roboty


float32 long_herrx
float32 long_herry
float32 tras_herrx
float32 tras_herry


float32 long_camx
float32 long_camy
float32 tras_camx
float32 tras_camy


float32 long_areax
float32 long_areay


geometry_msgs/Polygon input_poly


int32 id_poly


int32 id_defecto


int32 id_zona



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
---


float32 long_robotx
float32 long_roboty


float32 long_herrx
float32 long_herry
float32 tras_herrx
float32 tras_herry


float32 long_camx
float32 long_camy
float32 tras_camx
float32 tras_camy


float32 long_areax
float32 long_areay


geometry_msgs/Polygon zoneh0
geometry_msgs/Polygon zoneh90
geometry_msgs/Polygon zoneh180
geometry_msgs/Polygon zoneh270


geometry_msgs/Polygon zonec0
geometry_msgs/Polygon zonec90
geometry_msgs/Polygon zonec180
geometry_msgs/Polygon zonec270


geometry_msgs/PoseArray[] path_tray0
geometry_msgs/PoseArray[] path_tray90
geometry_msgs/PoseArray[] path_tray180
geometry_msgs/PoseArray[] path_tray270



geometry_msgs/Polygon zone_rot


defecto defecto_i
geometry_msgs/Polygon poly_i
int32 n_defectos

geometry_msgs/PoseArray[] defect_i_paths
geometry_msgs/PoseArray[] inspection_i_paths



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
MSG: geometry_msgs/PoseArray
# An array of poses with a header for global reference.

Header header

Pose[] poses

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: irobot_fcpp_simul/defecto
geometry_msgs/Polygon ros_poly
defecto_zona[] defecto_divpor_zonas

bool reparado

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



(provide :irobot_fcpp_simul/IROBOT_ir_data "7a9f483678423eac1cf4e98d3bca8c59")


