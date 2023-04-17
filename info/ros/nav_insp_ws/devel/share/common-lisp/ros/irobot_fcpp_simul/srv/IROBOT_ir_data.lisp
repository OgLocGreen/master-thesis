; Auto-generated. Do not edit!


(cl:in-package irobot_fcpp_simul-srv)


;//! \htmlinclude IROBOT_ir_data-request.msg.html

(cl:defclass <IROBOT_ir_data-request> (roslisp-msg-protocol:ros-message)
  ((load_inputdata
    :reader load_inputdata
    :initarg :load_inputdata
    :type cl:boolean
    :initform cl:nil)
   (load_polygon
    :reader load_polygon
    :initarg :load_polygon
    :type cl:boolean
    :initform cl:nil)
   (get_input_data
    :reader get_input_data
    :initarg :get_input_data
    :type cl:boolean
    :initform cl:nil)
   (get_working_zonesh
    :reader get_working_zonesh
    :initarg :get_working_zonesh
    :type cl:boolean
    :initform cl:nil)
   (get_working_zonesc
    :reader get_working_zonesc
    :initarg :get_working_zonesc
    :type cl:boolean
    :initform cl:nil)
   (get_inspection_zones
    :reader get_inspection_zones
    :initarg :get_inspection_zones
    :type cl:boolean
    :initform cl:nil)
   (get_rot_zone
    :reader get_rot_zone
    :initarg :get_rot_zone
    :type cl:boolean
    :initform cl:nil)
   (compute_adquireimgs
    :reader compute_adquireimgs
    :initarg :compute_adquireimgs
    :type cl:boolean
    :initform cl:nil)
   (compute_panorama
    :reader compute_panorama
    :initarg :compute_panorama
    :type cl:boolean
    :initform cl:nil)
   (merge_panoramas
    :reader merge_panoramas
    :initarg :merge_panoramas
    :type cl:boolean
    :initform cl:nil)
   (compute_detectpolys
    :reader compute_detectpolys
    :initarg :compute_detectpolys
    :type cl:boolean
    :initform cl:nil)
   (compute_fcpp_defect_i
    :reader compute_fcpp_defect_i
    :initarg :compute_fcpp_defect_i
    :type cl:boolean
    :initform cl:nil)
   (compute_fcpp_zone_i
    :reader compute_fcpp_zone_i
    :initarg :compute_fcpp_zone_i
    :type cl:boolean
    :initform cl:nil)
   (compute_fcpp_inspection_zone_i
    :reader compute_fcpp_inspection_zone_i
    :initarg :compute_fcpp_inspection_zone_i
    :type cl:boolean
    :initform cl:nil)
   (execute_fcpp_defect_i
    :reader execute_fcpp_defect_i
    :initarg :execute_fcpp_defect_i
    :type cl:boolean
    :initform cl:nil)
   (execute_fcpp_zone_i
    :reader execute_fcpp_zone_i
    :initarg :execute_fcpp_zone_i
    :type cl:boolean
    :initform cl:nil)
   (change_defect_reparation_goal
    :reader change_defect_reparation_goal
    :initarg :change_defect_reparation_goal
    :type cl:boolean
    :initform cl:nil)
   (change_inspection_goal
    :reader change_inspection_goal
    :initarg :change_inspection_goal
    :type cl:boolean
    :initform cl:nil)
   (get_poly_i
    :reader get_poly_i
    :initarg :get_poly_i
    :type cl:boolean
    :initform cl:nil)
   (get_defect_i
    :reader get_defect_i
    :initarg :get_defect_i
    :type cl:boolean
    :initform cl:nil)
   (get_defect_path
    :reader get_defect_path
    :initarg :get_defect_path
    :type cl:boolean
    :initform cl:nil)
   (get_inspection_i
    :reader get_inspection_i
    :initarg :get_inspection_i
    :type cl:boolean
    :initform cl:nil)
   (get_inspection_path
    :reader get_inspection_path
    :initarg :get_inspection_path
    :type cl:boolean
    :initform cl:nil)
   (activate_vizs
    :reader activate_vizs
    :initarg :activate_vizs
    :type cl:boolean
    :initform cl:nil)
   (long_robotx
    :reader long_robotx
    :initarg :long_robotx
    :type cl:float
    :initform 0.0)
   (long_roboty
    :reader long_roboty
    :initarg :long_roboty
    :type cl:float
    :initform 0.0)
   (long_herrx
    :reader long_herrx
    :initarg :long_herrx
    :type cl:float
    :initform 0.0)
   (long_herry
    :reader long_herry
    :initarg :long_herry
    :type cl:float
    :initform 0.0)
   (tras_herrx
    :reader tras_herrx
    :initarg :tras_herrx
    :type cl:float
    :initform 0.0)
   (tras_herry
    :reader tras_herry
    :initarg :tras_herry
    :type cl:float
    :initform 0.0)
   (long_camx
    :reader long_camx
    :initarg :long_camx
    :type cl:float
    :initform 0.0)
   (long_camy
    :reader long_camy
    :initarg :long_camy
    :type cl:float
    :initform 0.0)
   (tras_camx
    :reader tras_camx
    :initarg :tras_camx
    :type cl:float
    :initform 0.0)
   (tras_camy
    :reader tras_camy
    :initarg :tras_camy
    :type cl:float
    :initform 0.0)
   (long_areax
    :reader long_areax
    :initarg :long_areax
    :type cl:float
    :initform 0.0)
   (long_areay
    :reader long_areay
    :initarg :long_areay
    :type cl:float
    :initform 0.0)
   (input_poly
    :reader input_poly
    :initarg :input_poly
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (id_poly
    :reader id_poly
    :initarg :id_poly
    :type cl:integer
    :initform 0)
   (id_defecto
    :reader id_defecto
    :initarg :id_defecto
    :type cl:integer
    :initform 0)
   (id_defect_repair
    :reader id_defect_repair
    :initarg :id_defect_repair
    :type cl:integer
    :initform 0)
   (id_zona
    :reader id_zona
    :initarg :id_zona
    :type cl:integer
    :initform 0)
   (path_panorama
    :reader path_panorama
    :initarg :path_panorama
    :type cl:string
    :initform ""))
)

(cl:defclass IROBOT_ir_data-request (<IROBOT_ir_data-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <IROBOT_ir_data-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'IROBOT_ir_data-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<IROBOT_ir_data-request> is deprecated: use irobot_fcpp_simul-srv:IROBOT_ir_data-request instead.")))

(cl:ensure-generic-function 'load_inputdata-val :lambda-list '(m))
(cl:defmethod load_inputdata-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:load_inputdata-val is deprecated.  Use irobot_fcpp_simul-srv:load_inputdata instead.")
  (load_inputdata m))

(cl:ensure-generic-function 'load_polygon-val :lambda-list '(m))
(cl:defmethod load_polygon-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:load_polygon-val is deprecated.  Use irobot_fcpp_simul-srv:load_polygon instead.")
  (load_polygon m))

(cl:ensure-generic-function 'get_input_data-val :lambda-list '(m))
(cl:defmethod get_input_data-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_input_data-val is deprecated.  Use irobot_fcpp_simul-srv:get_input_data instead.")
  (get_input_data m))

(cl:ensure-generic-function 'get_working_zonesh-val :lambda-list '(m))
(cl:defmethod get_working_zonesh-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_working_zonesh-val is deprecated.  Use irobot_fcpp_simul-srv:get_working_zonesh instead.")
  (get_working_zonesh m))

(cl:ensure-generic-function 'get_working_zonesc-val :lambda-list '(m))
(cl:defmethod get_working_zonesc-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_working_zonesc-val is deprecated.  Use irobot_fcpp_simul-srv:get_working_zonesc instead.")
  (get_working_zonesc m))

(cl:ensure-generic-function 'get_inspection_zones-val :lambda-list '(m))
(cl:defmethod get_inspection_zones-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_inspection_zones-val is deprecated.  Use irobot_fcpp_simul-srv:get_inspection_zones instead.")
  (get_inspection_zones m))

(cl:ensure-generic-function 'get_rot_zone-val :lambda-list '(m))
(cl:defmethod get_rot_zone-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_rot_zone-val is deprecated.  Use irobot_fcpp_simul-srv:get_rot_zone instead.")
  (get_rot_zone m))

(cl:ensure-generic-function 'compute_adquireimgs-val :lambda-list '(m))
(cl:defmethod compute_adquireimgs-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_adquireimgs-val is deprecated.  Use irobot_fcpp_simul-srv:compute_adquireimgs instead.")
  (compute_adquireimgs m))

(cl:ensure-generic-function 'compute_panorama-val :lambda-list '(m))
(cl:defmethod compute_panorama-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_panorama-val is deprecated.  Use irobot_fcpp_simul-srv:compute_panorama instead.")
  (compute_panorama m))

(cl:ensure-generic-function 'merge_panoramas-val :lambda-list '(m))
(cl:defmethod merge_panoramas-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:merge_panoramas-val is deprecated.  Use irobot_fcpp_simul-srv:merge_panoramas instead.")
  (merge_panoramas m))

(cl:ensure-generic-function 'compute_detectpolys-val :lambda-list '(m))
(cl:defmethod compute_detectpolys-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_detectpolys-val is deprecated.  Use irobot_fcpp_simul-srv:compute_detectpolys instead.")
  (compute_detectpolys m))

(cl:ensure-generic-function 'compute_fcpp_defect_i-val :lambda-list '(m))
(cl:defmethod compute_fcpp_defect_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_fcpp_defect_i-val is deprecated.  Use irobot_fcpp_simul-srv:compute_fcpp_defect_i instead.")
  (compute_fcpp_defect_i m))

(cl:ensure-generic-function 'compute_fcpp_zone_i-val :lambda-list '(m))
(cl:defmethod compute_fcpp_zone_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_fcpp_zone_i-val is deprecated.  Use irobot_fcpp_simul-srv:compute_fcpp_zone_i instead.")
  (compute_fcpp_zone_i m))

(cl:ensure-generic-function 'compute_fcpp_inspection_zone_i-val :lambda-list '(m))
(cl:defmethod compute_fcpp_inspection_zone_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:compute_fcpp_inspection_zone_i-val is deprecated.  Use irobot_fcpp_simul-srv:compute_fcpp_inspection_zone_i instead.")
  (compute_fcpp_inspection_zone_i m))

(cl:ensure-generic-function 'execute_fcpp_defect_i-val :lambda-list '(m))
(cl:defmethod execute_fcpp_defect_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:execute_fcpp_defect_i-val is deprecated.  Use irobot_fcpp_simul-srv:execute_fcpp_defect_i instead.")
  (execute_fcpp_defect_i m))

(cl:ensure-generic-function 'execute_fcpp_zone_i-val :lambda-list '(m))
(cl:defmethod execute_fcpp_zone_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:execute_fcpp_zone_i-val is deprecated.  Use irobot_fcpp_simul-srv:execute_fcpp_zone_i instead.")
  (execute_fcpp_zone_i m))

(cl:ensure-generic-function 'change_defect_reparation_goal-val :lambda-list '(m))
(cl:defmethod change_defect_reparation_goal-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:change_defect_reparation_goal-val is deprecated.  Use irobot_fcpp_simul-srv:change_defect_reparation_goal instead.")
  (change_defect_reparation_goal m))

(cl:ensure-generic-function 'change_inspection_goal-val :lambda-list '(m))
(cl:defmethod change_inspection_goal-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:change_inspection_goal-val is deprecated.  Use irobot_fcpp_simul-srv:change_inspection_goal instead.")
  (change_inspection_goal m))

(cl:ensure-generic-function 'get_poly_i-val :lambda-list '(m))
(cl:defmethod get_poly_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_poly_i-val is deprecated.  Use irobot_fcpp_simul-srv:get_poly_i instead.")
  (get_poly_i m))

(cl:ensure-generic-function 'get_defect_i-val :lambda-list '(m))
(cl:defmethod get_defect_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_defect_i-val is deprecated.  Use irobot_fcpp_simul-srv:get_defect_i instead.")
  (get_defect_i m))

(cl:ensure-generic-function 'get_defect_path-val :lambda-list '(m))
(cl:defmethod get_defect_path-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_defect_path-val is deprecated.  Use irobot_fcpp_simul-srv:get_defect_path instead.")
  (get_defect_path m))

(cl:ensure-generic-function 'get_inspection_i-val :lambda-list '(m))
(cl:defmethod get_inspection_i-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_inspection_i-val is deprecated.  Use irobot_fcpp_simul-srv:get_inspection_i instead.")
  (get_inspection_i m))

(cl:ensure-generic-function 'get_inspection_path-val :lambda-list '(m))
(cl:defmethod get_inspection_path-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:get_inspection_path-val is deprecated.  Use irobot_fcpp_simul-srv:get_inspection_path instead.")
  (get_inspection_path m))

(cl:ensure-generic-function 'activate_vizs-val :lambda-list '(m))
(cl:defmethod activate_vizs-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:activate_vizs-val is deprecated.  Use irobot_fcpp_simul-srv:activate_vizs instead.")
  (activate_vizs m))

(cl:ensure-generic-function 'long_robotx-val :lambda-list '(m))
(cl:defmethod long_robotx-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_robotx-val is deprecated.  Use irobot_fcpp_simul-srv:long_robotx instead.")
  (long_robotx m))

(cl:ensure-generic-function 'long_roboty-val :lambda-list '(m))
(cl:defmethod long_roboty-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_roboty-val is deprecated.  Use irobot_fcpp_simul-srv:long_roboty instead.")
  (long_roboty m))

(cl:ensure-generic-function 'long_herrx-val :lambda-list '(m))
(cl:defmethod long_herrx-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_herrx-val is deprecated.  Use irobot_fcpp_simul-srv:long_herrx instead.")
  (long_herrx m))

(cl:ensure-generic-function 'long_herry-val :lambda-list '(m))
(cl:defmethod long_herry-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_herry-val is deprecated.  Use irobot_fcpp_simul-srv:long_herry instead.")
  (long_herry m))

(cl:ensure-generic-function 'tras_herrx-val :lambda-list '(m))
(cl:defmethod tras_herrx-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herrx-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herrx instead.")
  (tras_herrx m))

(cl:ensure-generic-function 'tras_herry-val :lambda-list '(m))
(cl:defmethod tras_herry-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herry-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herry instead.")
  (tras_herry m))

(cl:ensure-generic-function 'long_camx-val :lambda-list '(m))
(cl:defmethod long_camx-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_camx-val is deprecated.  Use irobot_fcpp_simul-srv:long_camx instead.")
  (long_camx m))

(cl:ensure-generic-function 'long_camy-val :lambda-list '(m))
(cl:defmethod long_camy-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_camy-val is deprecated.  Use irobot_fcpp_simul-srv:long_camy instead.")
  (long_camy m))

(cl:ensure-generic-function 'tras_camx-val :lambda-list '(m))
(cl:defmethod tras_camx-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_camx-val is deprecated.  Use irobot_fcpp_simul-srv:tras_camx instead.")
  (tras_camx m))

(cl:ensure-generic-function 'tras_camy-val :lambda-list '(m))
(cl:defmethod tras_camy-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_camy-val is deprecated.  Use irobot_fcpp_simul-srv:tras_camy instead.")
  (tras_camy m))

(cl:ensure-generic-function 'long_areax-val :lambda-list '(m))
(cl:defmethod long_areax-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_areax-val is deprecated.  Use irobot_fcpp_simul-srv:long_areax instead.")
  (long_areax m))

(cl:ensure-generic-function 'long_areay-val :lambda-list '(m))
(cl:defmethod long_areay-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_areay-val is deprecated.  Use irobot_fcpp_simul-srv:long_areay instead.")
  (long_areay m))

(cl:ensure-generic-function 'input_poly-val :lambda-list '(m))
(cl:defmethod input_poly-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:input_poly-val is deprecated.  Use irobot_fcpp_simul-srv:input_poly instead.")
  (input_poly m))

(cl:ensure-generic-function 'id_poly-val :lambda-list '(m))
(cl:defmethod id_poly-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:id_poly-val is deprecated.  Use irobot_fcpp_simul-srv:id_poly instead.")
  (id_poly m))

(cl:ensure-generic-function 'id_defecto-val :lambda-list '(m))
(cl:defmethod id_defecto-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:id_defecto-val is deprecated.  Use irobot_fcpp_simul-srv:id_defecto instead.")
  (id_defecto m))

(cl:ensure-generic-function 'id_defect_repair-val :lambda-list '(m))
(cl:defmethod id_defect_repair-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:id_defect_repair-val is deprecated.  Use irobot_fcpp_simul-srv:id_defect_repair instead.")
  (id_defect_repair m))

(cl:ensure-generic-function 'id_zona-val :lambda-list '(m))
(cl:defmethod id_zona-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:id_zona-val is deprecated.  Use irobot_fcpp_simul-srv:id_zona instead.")
  (id_zona m))

(cl:ensure-generic-function 'path_panorama-val :lambda-list '(m))
(cl:defmethod path_panorama-val ((m <IROBOT_ir_data-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:path_panorama-val is deprecated.  Use irobot_fcpp_simul-srv:path_panorama instead.")
  (path_panorama m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <IROBOT_ir_data-request>) ostream)
  "Serializes a message object of type '<IROBOT_ir_data-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'load_inputdata) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'load_polygon) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_input_data) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_working_zonesh) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_working_zonesc) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_inspection_zones) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_rot_zone) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_adquireimgs) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_panorama) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'merge_panoramas) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_detectpolys) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_fcpp_defect_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_fcpp_zone_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'compute_fcpp_inspection_zone_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'execute_fcpp_defect_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'execute_fcpp_zone_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'change_defect_reparation_goal) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'change_inspection_goal) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_poly_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_defect_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_defect_path) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_inspection_i) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'get_inspection_path) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'activate_vizs) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_robotx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_roboty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_herrx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_herry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herrx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_camx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_camy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_camx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_camy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_areax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_areay))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'input_poly) ostream)
  (cl:let* ((signed (cl:slot-value msg 'id_poly)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'id_defecto)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'id_defect_repair)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'id_zona)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'path_panorama))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'path_panorama))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <IROBOT_ir_data-request>) istream)
  "Deserializes a message object of type '<IROBOT_ir_data-request>"
    (cl:setf (cl:slot-value msg 'load_inputdata) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'load_polygon) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_input_data) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_working_zonesh) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_working_zonesc) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_inspection_zones) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_rot_zone) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_adquireimgs) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_panorama) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'merge_panoramas) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_detectpolys) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_fcpp_defect_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_fcpp_zone_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'compute_fcpp_inspection_zone_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'execute_fcpp_defect_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'execute_fcpp_zone_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'change_defect_reparation_goal) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'change_inspection_goal) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_poly_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_defect_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_defect_path) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_inspection_i) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'get_inspection_path) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'activate_vizs) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_robotx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_roboty) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_herrx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_herry) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herrx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herry) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_camx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_camy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_camx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_camy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_areax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_areay) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'input_poly) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_poly) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_defecto) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_defect_repair) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id_zona) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'path_panorama) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'path_panorama) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<IROBOT_ir_data-request>)))
  "Returns string type for a service object of type '<IROBOT_ir_data-request>"
  "irobot_fcpp_simul/IROBOT_ir_dataRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IROBOT_ir_data-request)))
  "Returns string type for a service object of type 'IROBOT_ir_data-request"
  "irobot_fcpp_simul/IROBOT_ir_dataRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<IROBOT_ir_data-request>)))
  "Returns md5sum for a message object of type '<IROBOT_ir_data-request>"
  "ae9b2e14b3730f735edbdd6f2ac13cb8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'IROBOT_ir_data-request)))
  "Returns md5sum for a message object of type 'IROBOT_ir_data-request"
  "ae9b2e14b3730f735edbdd6f2ac13cb8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<IROBOT_ir_data-request>)))
  "Returns full string definition for message of type '<IROBOT_ir_data-request>"
  (cl:format cl:nil "bool load_inputdata~%bool load_polygon~%~%bool get_input_data~%bool get_working_zonesh~%bool get_working_zonesc~%bool get_inspection_zones~%bool get_rot_zone~%~%~%bool compute_adquireimgs~%bool compute_panorama~%bool merge_panoramas~%bool compute_detectpolys~%~%bool compute_fcpp_defect_i~%bool compute_fcpp_zone_i~%bool compute_fcpp_inspection_zone_i~%~%bool execute_fcpp_defect_i~%bool execute_fcpp_zone_i~%~%bool change_defect_reparation_goal~%bool change_inspection_goal~%~%~%bool get_poly_i~%bool get_defect_i~%bool get_defect_path~%~%bool get_inspection_i~%bool get_inspection_path~%~%bool activate_vizs~%~%~%float32 long_robotx~%float32 long_roboty~%~%~%float32 long_herrx~%float32 long_herry~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 long_camx~%float32 long_camy~%float32 tras_camx~%float32 tras_camy~%~%~%float32 long_areax~%float32 long_areay~%~%~%geometry_msgs/Polygon input_poly~%~%~%int32 id_poly~%~%~%int32 id_defecto~%int32 id_defect_repair~%~%~%int32 id_zona~%~%~%string path_panorama~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'IROBOT_ir_data-request)))
  "Returns full string definition for message of type 'IROBOT_ir_data-request"
  (cl:format cl:nil "bool load_inputdata~%bool load_polygon~%~%bool get_input_data~%bool get_working_zonesh~%bool get_working_zonesc~%bool get_inspection_zones~%bool get_rot_zone~%~%~%bool compute_adquireimgs~%bool compute_panorama~%bool merge_panoramas~%bool compute_detectpolys~%~%bool compute_fcpp_defect_i~%bool compute_fcpp_zone_i~%bool compute_fcpp_inspection_zone_i~%~%bool execute_fcpp_defect_i~%bool execute_fcpp_zone_i~%~%bool change_defect_reparation_goal~%bool change_inspection_goal~%~%~%bool get_poly_i~%bool get_defect_i~%bool get_defect_path~%~%bool get_inspection_i~%bool get_inspection_path~%~%bool activate_vizs~%~%~%float32 long_robotx~%float32 long_roboty~%~%~%float32 long_herrx~%float32 long_herry~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 long_camx~%float32 long_camy~%float32 tras_camx~%float32 tras_camy~%~%~%float32 long_areax~%float32 long_areay~%~%~%geometry_msgs/Polygon input_poly~%~%~%int32 id_poly~%~%~%int32 id_defecto~%int32 id_defect_repair~%~%~%int32 id_zona~%~%~%string path_panorama~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <IROBOT_ir_data-request>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'input_poly))
     4
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'path_panorama))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <IROBOT_ir_data-request>))
  "Converts a ROS message object to a list"
  (cl:list 'IROBOT_ir_data-request
    (cl:cons ':load_inputdata (load_inputdata msg))
    (cl:cons ':load_polygon (load_polygon msg))
    (cl:cons ':get_input_data (get_input_data msg))
    (cl:cons ':get_working_zonesh (get_working_zonesh msg))
    (cl:cons ':get_working_zonesc (get_working_zonesc msg))
    (cl:cons ':get_inspection_zones (get_inspection_zones msg))
    (cl:cons ':get_rot_zone (get_rot_zone msg))
    (cl:cons ':compute_adquireimgs (compute_adquireimgs msg))
    (cl:cons ':compute_panorama (compute_panorama msg))
    (cl:cons ':merge_panoramas (merge_panoramas msg))
    (cl:cons ':compute_detectpolys (compute_detectpolys msg))
    (cl:cons ':compute_fcpp_defect_i (compute_fcpp_defect_i msg))
    (cl:cons ':compute_fcpp_zone_i (compute_fcpp_zone_i msg))
    (cl:cons ':compute_fcpp_inspection_zone_i (compute_fcpp_inspection_zone_i msg))
    (cl:cons ':execute_fcpp_defect_i (execute_fcpp_defect_i msg))
    (cl:cons ':execute_fcpp_zone_i (execute_fcpp_zone_i msg))
    (cl:cons ':change_defect_reparation_goal (change_defect_reparation_goal msg))
    (cl:cons ':change_inspection_goal (change_inspection_goal msg))
    (cl:cons ':get_poly_i (get_poly_i msg))
    (cl:cons ':get_defect_i (get_defect_i msg))
    (cl:cons ':get_defect_path (get_defect_path msg))
    (cl:cons ':get_inspection_i (get_inspection_i msg))
    (cl:cons ':get_inspection_path (get_inspection_path msg))
    (cl:cons ':activate_vizs (activate_vizs msg))
    (cl:cons ':long_robotx (long_robotx msg))
    (cl:cons ':long_roboty (long_roboty msg))
    (cl:cons ':long_herrx (long_herrx msg))
    (cl:cons ':long_herry (long_herry msg))
    (cl:cons ':tras_herrx (tras_herrx msg))
    (cl:cons ':tras_herry (tras_herry msg))
    (cl:cons ':long_camx (long_camx msg))
    (cl:cons ':long_camy (long_camy msg))
    (cl:cons ':tras_camx (tras_camx msg))
    (cl:cons ':tras_camy (tras_camy msg))
    (cl:cons ':long_areax (long_areax msg))
    (cl:cons ':long_areay (long_areay msg))
    (cl:cons ':input_poly (input_poly msg))
    (cl:cons ':id_poly (id_poly msg))
    (cl:cons ':id_defecto (id_defecto msg))
    (cl:cons ':id_defect_repair (id_defect_repair msg))
    (cl:cons ':id_zona (id_zona msg))
    (cl:cons ':path_panorama (path_panorama msg))
))
;//! \htmlinclude IROBOT_ir_data-response.msg.html

(cl:defclass <IROBOT_ir_data-response> (roslisp-msg-protocol:ros-message)
  ((long_robotx
    :reader long_robotx
    :initarg :long_robotx
    :type cl:float
    :initform 0.0)
   (long_roboty
    :reader long_roboty
    :initarg :long_roboty
    :type cl:float
    :initform 0.0)
   (long_herrx
    :reader long_herrx
    :initarg :long_herrx
    :type cl:float
    :initform 0.0)
   (long_herry
    :reader long_herry
    :initarg :long_herry
    :type cl:float
    :initform 0.0)
   (tras_herrx
    :reader tras_herrx
    :initarg :tras_herrx
    :type cl:float
    :initform 0.0)
   (tras_herry
    :reader tras_herry
    :initarg :tras_herry
    :type cl:float
    :initform 0.0)
   (long_camx
    :reader long_camx
    :initarg :long_camx
    :type cl:float
    :initform 0.0)
   (long_camy
    :reader long_camy
    :initarg :long_camy
    :type cl:float
    :initform 0.0)
   (tras_camx
    :reader tras_camx
    :initarg :tras_camx
    :type cl:float
    :initform 0.0)
   (tras_camy
    :reader tras_camy
    :initarg :tras_camy
    :type cl:float
    :initform 0.0)
   (long_areax
    :reader long_areax
    :initarg :long_areax
    :type cl:float
    :initform 0.0)
   (long_areay
    :reader long_areay
    :initarg :long_areay
    :type cl:float
    :initform 0.0)
   (zoneh0
    :reader zoneh0
    :initarg :zoneh0
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zoneh90
    :reader zoneh90
    :initarg :zoneh90
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zoneh180
    :reader zoneh180
    :initarg :zoneh180
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zoneh270
    :reader zoneh270
    :initarg :zoneh270
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zonec0
    :reader zonec0
    :initarg :zonec0
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zonec90
    :reader zonec90
    :initarg :zonec90
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zonec180
    :reader zonec180
    :initarg :zonec180
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (zonec270
    :reader zonec270
    :initarg :zonec270
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (path_tray0
    :reader path_tray0
    :initarg :path_tray0
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray)))
   (path_tray90
    :reader path_tray90
    :initarg :path_tray90
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray)))
   (path_tray180
    :reader path_tray180
    :initarg :path_tray180
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray)))
   (path_tray270
    :reader path_tray270
    :initarg :path_tray270
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray)))
   (zone_rot
    :reader zone_rot
    :initarg :zone_rot
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (defecto_i
    :reader defecto_i
    :initarg :defecto_i
    :type irobot_fcpp_simul-msg:defecto
    :initform (cl:make-instance 'irobot_fcpp_simul-msg:defecto))
   (poly_i
    :reader poly_i
    :initarg :poly_i
    :type geometry_msgs-msg:Polygon
    :initform (cl:make-instance 'geometry_msgs-msg:Polygon))
   (n_defectos
    :reader n_defectos
    :initarg :n_defectos
    :type cl:integer
    :initform 0)
   (defect_i_paths
    :reader defect_i_paths
    :initarg :defect_i_paths
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray)))
   (inspection_i_paths
    :reader inspection_i_paths
    :initarg :inspection_i_paths
    :type (cl:vector geometry_msgs-msg:PoseArray)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:PoseArray :initial-element (cl:make-instance 'geometry_msgs-msg:PoseArray))))
)

(cl:defclass IROBOT_ir_data-response (<IROBOT_ir_data-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <IROBOT_ir_data-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'IROBOT_ir_data-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_fcpp_simul-srv:<IROBOT_ir_data-response> is deprecated: use irobot_fcpp_simul-srv:IROBOT_ir_data-response instead.")))

(cl:ensure-generic-function 'long_robotx-val :lambda-list '(m))
(cl:defmethod long_robotx-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_robotx-val is deprecated.  Use irobot_fcpp_simul-srv:long_robotx instead.")
  (long_robotx m))

(cl:ensure-generic-function 'long_roboty-val :lambda-list '(m))
(cl:defmethod long_roboty-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_roboty-val is deprecated.  Use irobot_fcpp_simul-srv:long_roboty instead.")
  (long_roboty m))

(cl:ensure-generic-function 'long_herrx-val :lambda-list '(m))
(cl:defmethod long_herrx-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_herrx-val is deprecated.  Use irobot_fcpp_simul-srv:long_herrx instead.")
  (long_herrx m))

(cl:ensure-generic-function 'long_herry-val :lambda-list '(m))
(cl:defmethod long_herry-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_herry-val is deprecated.  Use irobot_fcpp_simul-srv:long_herry instead.")
  (long_herry m))

(cl:ensure-generic-function 'tras_herrx-val :lambda-list '(m))
(cl:defmethod tras_herrx-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herrx-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herrx instead.")
  (tras_herrx m))

(cl:ensure-generic-function 'tras_herry-val :lambda-list '(m))
(cl:defmethod tras_herry-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_herry-val is deprecated.  Use irobot_fcpp_simul-srv:tras_herry instead.")
  (tras_herry m))

(cl:ensure-generic-function 'long_camx-val :lambda-list '(m))
(cl:defmethod long_camx-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_camx-val is deprecated.  Use irobot_fcpp_simul-srv:long_camx instead.")
  (long_camx m))

(cl:ensure-generic-function 'long_camy-val :lambda-list '(m))
(cl:defmethod long_camy-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_camy-val is deprecated.  Use irobot_fcpp_simul-srv:long_camy instead.")
  (long_camy m))

(cl:ensure-generic-function 'tras_camx-val :lambda-list '(m))
(cl:defmethod tras_camx-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_camx-val is deprecated.  Use irobot_fcpp_simul-srv:tras_camx instead.")
  (tras_camx m))

(cl:ensure-generic-function 'tras_camy-val :lambda-list '(m))
(cl:defmethod tras_camy-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:tras_camy-val is deprecated.  Use irobot_fcpp_simul-srv:tras_camy instead.")
  (tras_camy m))

(cl:ensure-generic-function 'long_areax-val :lambda-list '(m))
(cl:defmethod long_areax-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_areax-val is deprecated.  Use irobot_fcpp_simul-srv:long_areax instead.")
  (long_areax m))

(cl:ensure-generic-function 'long_areay-val :lambda-list '(m))
(cl:defmethod long_areay-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:long_areay-val is deprecated.  Use irobot_fcpp_simul-srv:long_areay instead.")
  (long_areay m))

(cl:ensure-generic-function 'zoneh0-val :lambda-list '(m))
(cl:defmethod zoneh0-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zoneh0-val is deprecated.  Use irobot_fcpp_simul-srv:zoneh0 instead.")
  (zoneh0 m))

(cl:ensure-generic-function 'zoneh90-val :lambda-list '(m))
(cl:defmethod zoneh90-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zoneh90-val is deprecated.  Use irobot_fcpp_simul-srv:zoneh90 instead.")
  (zoneh90 m))

(cl:ensure-generic-function 'zoneh180-val :lambda-list '(m))
(cl:defmethod zoneh180-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zoneh180-val is deprecated.  Use irobot_fcpp_simul-srv:zoneh180 instead.")
  (zoneh180 m))

(cl:ensure-generic-function 'zoneh270-val :lambda-list '(m))
(cl:defmethod zoneh270-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zoneh270-val is deprecated.  Use irobot_fcpp_simul-srv:zoneh270 instead.")
  (zoneh270 m))

(cl:ensure-generic-function 'zonec0-val :lambda-list '(m))
(cl:defmethod zonec0-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zonec0-val is deprecated.  Use irobot_fcpp_simul-srv:zonec0 instead.")
  (zonec0 m))

(cl:ensure-generic-function 'zonec90-val :lambda-list '(m))
(cl:defmethod zonec90-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zonec90-val is deprecated.  Use irobot_fcpp_simul-srv:zonec90 instead.")
  (zonec90 m))

(cl:ensure-generic-function 'zonec180-val :lambda-list '(m))
(cl:defmethod zonec180-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zonec180-val is deprecated.  Use irobot_fcpp_simul-srv:zonec180 instead.")
  (zonec180 m))

(cl:ensure-generic-function 'zonec270-val :lambda-list '(m))
(cl:defmethod zonec270-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zonec270-val is deprecated.  Use irobot_fcpp_simul-srv:zonec270 instead.")
  (zonec270 m))

(cl:ensure-generic-function 'path_tray0-val :lambda-list '(m))
(cl:defmethod path_tray0-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:path_tray0-val is deprecated.  Use irobot_fcpp_simul-srv:path_tray0 instead.")
  (path_tray0 m))

(cl:ensure-generic-function 'path_tray90-val :lambda-list '(m))
(cl:defmethod path_tray90-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:path_tray90-val is deprecated.  Use irobot_fcpp_simul-srv:path_tray90 instead.")
  (path_tray90 m))

(cl:ensure-generic-function 'path_tray180-val :lambda-list '(m))
(cl:defmethod path_tray180-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:path_tray180-val is deprecated.  Use irobot_fcpp_simul-srv:path_tray180 instead.")
  (path_tray180 m))

(cl:ensure-generic-function 'path_tray270-val :lambda-list '(m))
(cl:defmethod path_tray270-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:path_tray270-val is deprecated.  Use irobot_fcpp_simul-srv:path_tray270 instead.")
  (path_tray270 m))

(cl:ensure-generic-function 'zone_rot-val :lambda-list '(m))
(cl:defmethod zone_rot-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:zone_rot-val is deprecated.  Use irobot_fcpp_simul-srv:zone_rot instead.")
  (zone_rot m))

(cl:ensure-generic-function 'defecto_i-val :lambda-list '(m))
(cl:defmethod defecto_i-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:defecto_i-val is deprecated.  Use irobot_fcpp_simul-srv:defecto_i instead.")
  (defecto_i m))

(cl:ensure-generic-function 'poly_i-val :lambda-list '(m))
(cl:defmethod poly_i-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:poly_i-val is deprecated.  Use irobot_fcpp_simul-srv:poly_i instead.")
  (poly_i m))

(cl:ensure-generic-function 'n_defectos-val :lambda-list '(m))
(cl:defmethod n_defectos-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:n_defectos-val is deprecated.  Use irobot_fcpp_simul-srv:n_defectos instead.")
  (n_defectos m))

(cl:ensure-generic-function 'defect_i_paths-val :lambda-list '(m))
(cl:defmethod defect_i_paths-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:defect_i_paths-val is deprecated.  Use irobot_fcpp_simul-srv:defect_i_paths instead.")
  (defect_i_paths m))

(cl:ensure-generic-function 'inspection_i_paths-val :lambda-list '(m))
(cl:defmethod inspection_i_paths-val ((m <IROBOT_ir_data-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader irobot_fcpp_simul-srv:inspection_i_paths-val is deprecated.  Use irobot_fcpp_simul-srv:inspection_i_paths instead.")
  (inspection_i_paths m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <IROBOT_ir_data-response>) ostream)
  "Serializes a message object of type '<IROBOT_ir_data-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_robotx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_roboty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_herrx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_herry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herrx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_herry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_camx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_camy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_camx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tras_camy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_areax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'long_areay))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zoneh0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zoneh90) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zoneh180) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zoneh270) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zonec0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zonec90) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zonec180) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zonec270) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_tray0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'path_tray0))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_tray90))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'path_tray90))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_tray180))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'path_tray180))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_tray270))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'path_tray270))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'zone_rot) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'defecto_i) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'poly_i) ostream)
  (cl:let* ((signed (cl:slot-value msg 'n_defectos)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'defect_i_paths))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'defect_i_paths))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'inspection_i_paths))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'inspection_i_paths))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <IROBOT_ir_data-response>) istream)
  "Deserializes a message object of type '<IROBOT_ir_data-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_robotx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_roboty) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_herrx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_herry) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herrx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_herry) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_camx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_camy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_camx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tras_camy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_areax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'long_areay) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zoneh0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zoneh90) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zoneh180) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zoneh270) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zonec0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zonec90) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zonec180) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zonec270) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'path_tray0) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_tray0)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'path_tray90) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_tray90)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'path_tray180) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_tray180)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'path_tray270) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_tray270)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'zone_rot) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'defecto_i) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'poly_i) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n_defectos) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'defect_i_paths) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'defect_i_paths)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'inspection_i_paths) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'inspection_i_paths)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:PoseArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<IROBOT_ir_data-response>)))
  "Returns string type for a service object of type '<IROBOT_ir_data-response>"
  "irobot_fcpp_simul/IROBOT_ir_dataResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IROBOT_ir_data-response)))
  "Returns string type for a service object of type 'IROBOT_ir_data-response"
  "irobot_fcpp_simul/IROBOT_ir_dataResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<IROBOT_ir_data-response>)))
  "Returns md5sum for a message object of type '<IROBOT_ir_data-response>"
  "ae9b2e14b3730f735edbdd6f2ac13cb8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'IROBOT_ir_data-response)))
  "Returns md5sum for a message object of type 'IROBOT_ir_data-response"
  "ae9b2e14b3730f735edbdd6f2ac13cb8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<IROBOT_ir_data-response>)))
  "Returns full string definition for message of type '<IROBOT_ir_data-response>"
  (cl:format cl:nil "~%~%float32 long_robotx~%float32 long_roboty~%~%~%float32 long_herrx~%float32 long_herry~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 long_camx~%float32 long_camy~%float32 tras_camx~%float32 tras_camy~%~%~%float32 long_areax~%float32 long_areay~%~%~%geometry_msgs/Polygon zoneh0~%geometry_msgs/Polygon zoneh90~%geometry_msgs/Polygon zoneh180~%geometry_msgs/Polygon zoneh270~%~%~%geometry_msgs/Polygon zonec0~%geometry_msgs/Polygon zonec90~%geometry_msgs/Polygon zonec180~%geometry_msgs/Polygon zonec270~%~%~%geometry_msgs/PoseArray[] path_tray0~%geometry_msgs/PoseArray[] path_tray90~%geometry_msgs/PoseArray[] path_tray180~%geometry_msgs/PoseArray[] path_tray270~%~%~%~%geometry_msgs/Polygon zone_rot~%~%~%defecto defecto_i~%geometry_msgs/Polygon poly_i~%int32 n_defectos~%~%geometry_msgs/PoseArray[] defect_i_paths~%geometry_msgs/PoseArray[] inspection_i_paths~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: geometry_msgs/PoseArray~%# An array of poses with a header for global reference.~%~%Header header~%~%Pose[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto~%geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'IROBOT_ir_data-response)))
  "Returns full string definition for message of type 'IROBOT_ir_data-response"
  (cl:format cl:nil "~%~%float32 long_robotx~%float32 long_roboty~%~%~%float32 long_herrx~%float32 long_herry~%float32 tras_herrx~%float32 tras_herry~%~%~%float32 long_camx~%float32 long_camy~%float32 tras_camx~%float32 tras_camy~%~%~%float32 long_areax~%float32 long_areay~%~%~%geometry_msgs/Polygon zoneh0~%geometry_msgs/Polygon zoneh90~%geometry_msgs/Polygon zoneh180~%geometry_msgs/Polygon zoneh270~%~%~%geometry_msgs/Polygon zonec0~%geometry_msgs/Polygon zonec90~%geometry_msgs/Polygon zonec180~%geometry_msgs/Polygon zonec270~%~%~%geometry_msgs/PoseArray[] path_tray0~%geometry_msgs/PoseArray[] path_tray90~%geometry_msgs/PoseArray[] path_tray180~%geometry_msgs/PoseArray[] path_tray270~%~%~%~%geometry_msgs/Polygon zone_rot~%~%~%defecto defecto_i~%geometry_msgs/Polygon poly_i~%int32 n_defectos~%~%geometry_msgs/PoseArray[] defect_i_paths~%geometry_msgs/PoseArray[] inspection_i_paths~%~%~%~%================================================================================~%MSG: geometry_msgs/Polygon~%#A specification of a polygon where the first and last points are assumed to be connected~%Point32[] points~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: geometry_msgs/PoseArray~%# An array of poses with a header for global reference.~%~%Header header~%~%Pose[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto~%geometry_msgs/Polygon ros_poly~%defecto_zona[] defecto_divpor_zonas~%~%bool reparado~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_zona~%geometry_msgs/Polygon ros_poly~%defecto_simple[] trap_vec~%~%int32 direccion_rep~%bool reparado~%int32 zona~%~%================================================================================~%MSG: irobot_fcpp_simul/defecto_simple~%geometry_msgs/Polygon ros_poly~%int32 direccion_rep~%bool reparado~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <IROBOT_ir_data-response>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zoneh0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zoneh90))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zoneh180))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zoneh270))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zonec0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zonec90))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zonec180))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zonec270))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_tray0) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_tray90) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_tray180) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_tray270) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'zone_rot))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'defecto_i))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'poly_i))
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'defect_i_paths) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'inspection_i_paths) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <IROBOT_ir_data-response>))
  "Converts a ROS message object to a list"
  (cl:list 'IROBOT_ir_data-response
    (cl:cons ':long_robotx (long_robotx msg))
    (cl:cons ':long_roboty (long_roboty msg))
    (cl:cons ':long_herrx (long_herrx msg))
    (cl:cons ':long_herry (long_herry msg))
    (cl:cons ':tras_herrx (tras_herrx msg))
    (cl:cons ':tras_herry (tras_herry msg))
    (cl:cons ':long_camx (long_camx msg))
    (cl:cons ':long_camy (long_camy msg))
    (cl:cons ':tras_camx (tras_camx msg))
    (cl:cons ':tras_camy (tras_camy msg))
    (cl:cons ':long_areax (long_areax msg))
    (cl:cons ':long_areay (long_areay msg))
    (cl:cons ':zoneh0 (zoneh0 msg))
    (cl:cons ':zoneh90 (zoneh90 msg))
    (cl:cons ':zoneh180 (zoneh180 msg))
    (cl:cons ':zoneh270 (zoneh270 msg))
    (cl:cons ':zonec0 (zonec0 msg))
    (cl:cons ':zonec90 (zonec90 msg))
    (cl:cons ':zonec180 (zonec180 msg))
    (cl:cons ':zonec270 (zonec270 msg))
    (cl:cons ':path_tray0 (path_tray0 msg))
    (cl:cons ':path_tray90 (path_tray90 msg))
    (cl:cons ':path_tray180 (path_tray180 msg))
    (cl:cons ':path_tray270 (path_tray270 msg))
    (cl:cons ':zone_rot (zone_rot msg))
    (cl:cons ':defecto_i (defecto_i msg))
    (cl:cons ':poly_i (poly_i msg))
    (cl:cons ':n_defectos (n_defectos msg))
    (cl:cons ':defect_i_paths (defect_i_paths msg))
    (cl:cons ':inspection_i_paths (inspection_i_paths msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'IROBOT_ir_data)))
  'IROBOT_ir_data-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'IROBOT_ir_data)))
  'IROBOT_ir_data-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IROBOT_ir_data)))
  "Returns string type for a service object of type '<IROBOT_ir_data>"
  "irobot_fcpp_simul/IROBOT_ir_data")