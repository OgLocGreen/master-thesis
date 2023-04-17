// Auto-generated. Do not edit!

// (in-package irobot_fcpp_simul.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

let defecto = require('../msg/defecto.js');

//-----------------------------------------------------------

class IROBOT_ir_dataRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.load_inputdata = null;
      this.load_polygon = null;
      this.get_input_data = null;
      this.get_working_zonesh = null;
      this.get_working_zonesc = null;
      this.get_inspection_zones = null;
      this.get_rot_zone = null;
      this.compute_adquireimgs = null;
      this.compute_panorama = null;
      this.merge_panoramas = null;
      this.compute_detectpolys = null;
      this.compute_fcpp_defect_i = null;
      this.compute_fcpp_zone_i = null;
      this.compute_fcpp_inspection_zone_i = null;
      this.execute_fcpp_defect_i = null;
      this.execute_fcpp_zone_i = null;
      this.change_defect_reparation_goal = null;
      this.change_inspection_goal = null;
      this.get_poly_i = null;
      this.get_defect_i = null;
      this.get_defect_path = null;
      this.get_inspection_i = null;
      this.get_inspection_path = null;
      this.activate_vizs = null;
      this.long_robotx = null;
      this.long_roboty = null;
      this.long_herrx = null;
      this.long_herry = null;
      this.tras_herrx = null;
      this.tras_herry = null;
      this.long_camx = null;
      this.long_camy = null;
      this.tras_camx = null;
      this.tras_camy = null;
      this.long_areax = null;
      this.long_areay = null;
      this.input_poly = null;
      this.id_poly = null;
      this.id_defecto = null;
      this.id_defect_repair = null;
      this.id_zona = null;
      this.path_panorama = null;
    }
    else {
      if (initObj.hasOwnProperty('load_inputdata')) {
        this.load_inputdata = initObj.load_inputdata
      }
      else {
        this.load_inputdata = false;
      }
      if (initObj.hasOwnProperty('load_polygon')) {
        this.load_polygon = initObj.load_polygon
      }
      else {
        this.load_polygon = false;
      }
      if (initObj.hasOwnProperty('get_input_data')) {
        this.get_input_data = initObj.get_input_data
      }
      else {
        this.get_input_data = false;
      }
      if (initObj.hasOwnProperty('get_working_zonesh')) {
        this.get_working_zonesh = initObj.get_working_zonesh
      }
      else {
        this.get_working_zonesh = false;
      }
      if (initObj.hasOwnProperty('get_working_zonesc')) {
        this.get_working_zonesc = initObj.get_working_zonesc
      }
      else {
        this.get_working_zonesc = false;
      }
      if (initObj.hasOwnProperty('get_inspection_zones')) {
        this.get_inspection_zones = initObj.get_inspection_zones
      }
      else {
        this.get_inspection_zones = false;
      }
      if (initObj.hasOwnProperty('get_rot_zone')) {
        this.get_rot_zone = initObj.get_rot_zone
      }
      else {
        this.get_rot_zone = false;
      }
      if (initObj.hasOwnProperty('compute_adquireimgs')) {
        this.compute_adquireimgs = initObj.compute_adquireimgs
      }
      else {
        this.compute_adquireimgs = false;
      }
      if (initObj.hasOwnProperty('compute_panorama')) {
        this.compute_panorama = initObj.compute_panorama
      }
      else {
        this.compute_panorama = false;
      }
      if (initObj.hasOwnProperty('merge_panoramas')) {
        this.merge_panoramas = initObj.merge_panoramas
      }
      else {
        this.merge_panoramas = false;
      }
      if (initObj.hasOwnProperty('compute_detectpolys')) {
        this.compute_detectpolys = initObj.compute_detectpolys
      }
      else {
        this.compute_detectpolys = false;
      }
      if (initObj.hasOwnProperty('compute_fcpp_defect_i')) {
        this.compute_fcpp_defect_i = initObj.compute_fcpp_defect_i
      }
      else {
        this.compute_fcpp_defect_i = false;
      }
      if (initObj.hasOwnProperty('compute_fcpp_zone_i')) {
        this.compute_fcpp_zone_i = initObj.compute_fcpp_zone_i
      }
      else {
        this.compute_fcpp_zone_i = false;
      }
      if (initObj.hasOwnProperty('compute_fcpp_inspection_zone_i')) {
        this.compute_fcpp_inspection_zone_i = initObj.compute_fcpp_inspection_zone_i
      }
      else {
        this.compute_fcpp_inspection_zone_i = false;
      }
      if (initObj.hasOwnProperty('execute_fcpp_defect_i')) {
        this.execute_fcpp_defect_i = initObj.execute_fcpp_defect_i
      }
      else {
        this.execute_fcpp_defect_i = false;
      }
      if (initObj.hasOwnProperty('execute_fcpp_zone_i')) {
        this.execute_fcpp_zone_i = initObj.execute_fcpp_zone_i
      }
      else {
        this.execute_fcpp_zone_i = false;
      }
      if (initObj.hasOwnProperty('change_defect_reparation_goal')) {
        this.change_defect_reparation_goal = initObj.change_defect_reparation_goal
      }
      else {
        this.change_defect_reparation_goal = false;
      }
      if (initObj.hasOwnProperty('change_inspection_goal')) {
        this.change_inspection_goal = initObj.change_inspection_goal
      }
      else {
        this.change_inspection_goal = false;
      }
      if (initObj.hasOwnProperty('get_poly_i')) {
        this.get_poly_i = initObj.get_poly_i
      }
      else {
        this.get_poly_i = false;
      }
      if (initObj.hasOwnProperty('get_defect_i')) {
        this.get_defect_i = initObj.get_defect_i
      }
      else {
        this.get_defect_i = false;
      }
      if (initObj.hasOwnProperty('get_defect_path')) {
        this.get_defect_path = initObj.get_defect_path
      }
      else {
        this.get_defect_path = false;
      }
      if (initObj.hasOwnProperty('get_inspection_i')) {
        this.get_inspection_i = initObj.get_inspection_i
      }
      else {
        this.get_inspection_i = false;
      }
      if (initObj.hasOwnProperty('get_inspection_path')) {
        this.get_inspection_path = initObj.get_inspection_path
      }
      else {
        this.get_inspection_path = false;
      }
      if (initObj.hasOwnProperty('activate_vizs')) {
        this.activate_vizs = initObj.activate_vizs
      }
      else {
        this.activate_vizs = false;
      }
      if (initObj.hasOwnProperty('long_robotx')) {
        this.long_robotx = initObj.long_robotx
      }
      else {
        this.long_robotx = 0.0;
      }
      if (initObj.hasOwnProperty('long_roboty')) {
        this.long_roboty = initObj.long_roboty
      }
      else {
        this.long_roboty = 0.0;
      }
      if (initObj.hasOwnProperty('long_herrx')) {
        this.long_herrx = initObj.long_herrx
      }
      else {
        this.long_herrx = 0.0;
      }
      if (initObj.hasOwnProperty('long_herry')) {
        this.long_herry = initObj.long_herry
      }
      else {
        this.long_herry = 0.0;
      }
      if (initObj.hasOwnProperty('tras_herrx')) {
        this.tras_herrx = initObj.tras_herrx
      }
      else {
        this.tras_herrx = 0.0;
      }
      if (initObj.hasOwnProperty('tras_herry')) {
        this.tras_herry = initObj.tras_herry
      }
      else {
        this.tras_herry = 0.0;
      }
      if (initObj.hasOwnProperty('long_camx')) {
        this.long_camx = initObj.long_camx
      }
      else {
        this.long_camx = 0.0;
      }
      if (initObj.hasOwnProperty('long_camy')) {
        this.long_camy = initObj.long_camy
      }
      else {
        this.long_camy = 0.0;
      }
      if (initObj.hasOwnProperty('tras_camx')) {
        this.tras_camx = initObj.tras_camx
      }
      else {
        this.tras_camx = 0.0;
      }
      if (initObj.hasOwnProperty('tras_camy')) {
        this.tras_camy = initObj.tras_camy
      }
      else {
        this.tras_camy = 0.0;
      }
      if (initObj.hasOwnProperty('long_areax')) {
        this.long_areax = initObj.long_areax
      }
      else {
        this.long_areax = 0.0;
      }
      if (initObj.hasOwnProperty('long_areay')) {
        this.long_areay = initObj.long_areay
      }
      else {
        this.long_areay = 0.0;
      }
      if (initObj.hasOwnProperty('input_poly')) {
        this.input_poly = initObj.input_poly
      }
      else {
        this.input_poly = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('id_poly')) {
        this.id_poly = initObj.id_poly
      }
      else {
        this.id_poly = 0;
      }
      if (initObj.hasOwnProperty('id_defecto')) {
        this.id_defecto = initObj.id_defecto
      }
      else {
        this.id_defecto = 0;
      }
      if (initObj.hasOwnProperty('id_defect_repair')) {
        this.id_defect_repair = initObj.id_defect_repair
      }
      else {
        this.id_defect_repair = 0;
      }
      if (initObj.hasOwnProperty('id_zona')) {
        this.id_zona = initObj.id_zona
      }
      else {
        this.id_zona = 0;
      }
      if (initObj.hasOwnProperty('path_panorama')) {
        this.path_panorama = initObj.path_panorama
      }
      else {
        this.path_panorama = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type IROBOT_ir_dataRequest
    // Serialize message field [load_inputdata]
    bufferOffset = _serializer.bool(obj.load_inputdata, buffer, bufferOffset);
    // Serialize message field [load_polygon]
    bufferOffset = _serializer.bool(obj.load_polygon, buffer, bufferOffset);
    // Serialize message field [get_input_data]
    bufferOffset = _serializer.bool(obj.get_input_data, buffer, bufferOffset);
    // Serialize message field [get_working_zonesh]
    bufferOffset = _serializer.bool(obj.get_working_zonesh, buffer, bufferOffset);
    // Serialize message field [get_working_zonesc]
    bufferOffset = _serializer.bool(obj.get_working_zonesc, buffer, bufferOffset);
    // Serialize message field [get_inspection_zones]
    bufferOffset = _serializer.bool(obj.get_inspection_zones, buffer, bufferOffset);
    // Serialize message field [get_rot_zone]
    bufferOffset = _serializer.bool(obj.get_rot_zone, buffer, bufferOffset);
    // Serialize message field [compute_adquireimgs]
    bufferOffset = _serializer.bool(obj.compute_adquireimgs, buffer, bufferOffset);
    // Serialize message field [compute_panorama]
    bufferOffset = _serializer.bool(obj.compute_panorama, buffer, bufferOffset);
    // Serialize message field [merge_panoramas]
    bufferOffset = _serializer.bool(obj.merge_panoramas, buffer, bufferOffset);
    // Serialize message field [compute_detectpolys]
    bufferOffset = _serializer.bool(obj.compute_detectpolys, buffer, bufferOffset);
    // Serialize message field [compute_fcpp_defect_i]
    bufferOffset = _serializer.bool(obj.compute_fcpp_defect_i, buffer, bufferOffset);
    // Serialize message field [compute_fcpp_zone_i]
    bufferOffset = _serializer.bool(obj.compute_fcpp_zone_i, buffer, bufferOffset);
    // Serialize message field [compute_fcpp_inspection_zone_i]
    bufferOffset = _serializer.bool(obj.compute_fcpp_inspection_zone_i, buffer, bufferOffset);
    // Serialize message field [execute_fcpp_defect_i]
    bufferOffset = _serializer.bool(obj.execute_fcpp_defect_i, buffer, bufferOffset);
    // Serialize message field [execute_fcpp_zone_i]
    bufferOffset = _serializer.bool(obj.execute_fcpp_zone_i, buffer, bufferOffset);
    // Serialize message field [change_defect_reparation_goal]
    bufferOffset = _serializer.bool(obj.change_defect_reparation_goal, buffer, bufferOffset);
    // Serialize message field [change_inspection_goal]
    bufferOffset = _serializer.bool(obj.change_inspection_goal, buffer, bufferOffset);
    // Serialize message field [get_poly_i]
    bufferOffset = _serializer.bool(obj.get_poly_i, buffer, bufferOffset);
    // Serialize message field [get_defect_i]
    bufferOffset = _serializer.bool(obj.get_defect_i, buffer, bufferOffset);
    // Serialize message field [get_defect_path]
    bufferOffset = _serializer.bool(obj.get_defect_path, buffer, bufferOffset);
    // Serialize message field [get_inspection_i]
    bufferOffset = _serializer.bool(obj.get_inspection_i, buffer, bufferOffset);
    // Serialize message field [get_inspection_path]
    bufferOffset = _serializer.bool(obj.get_inspection_path, buffer, bufferOffset);
    // Serialize message field [activate_vizs]
    bufferOffset = _serializer.bool(obj.activate_vizs, buffer, bufferOffset);
    // Serialize message field [long_robotx]
    bufferOffset = _serializer.float32(obj.long_robotx, buffer, bufferOffset);
    // Serialize message field [long_roboty]
    bufferOffset = _serializer.float32(obj.long_roboty, buffer, bufferOffset);
    // Serialize message field [long_herrx]
    bufferOffset = _serializer.float32(obj.long_herrx, buffer, bufferOffset);
    // Serialize message field [long_herry]
    bufferOffset = _serializer.float32(obj.long_herry, buffer, bufferOffset);
    // Serialize message field [tras_herrx]
    bufferOffset = _serializer.float32(obj.tras_herrx, buffer, bufferOffset);
    // Serialize message field [tras_herry]
    bufferOffset = _serializer.float32(obj.tras_herry, buffer, bufferOffset);
    // Serialize message field [long_camx]
    bufferOffset = _serializer.float32(obj.long_camx, buffer, bufferOffset);
    // Serialize message field [long_camy]
    bufferOffset = _serializer.float32(obj.long_camy, buffer, bufferOffset);
    // Serialize message field [tras_camx]
    bufferOffset = _serializer.float32(obj.tras_camx, buffer, bufferOffset);
    // Serialize message field [tras_camy]
    bufferOffset = _serializer.float32(obj.tras_camy, buffer, bufferOffset);
    // Serialize message field [long_areax]
    bufferOffset = _serializer.float32(obj.long_areax, buffer, bufferOffset);
    // Serialize message field [long_areay]
    bufferOffset = _serializer.float32(obj.long_areay, buffer, bufferOffset);
    // Serialize message field [input_poly]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.input_poly, buffer, bufferOffset);
    // Serialize message field [id_poly]
    bufferOffset = _serializer.int32(obj.id_poly, buffer, bufferOffset);
    // Serialize message field [id_defecto]
    bufferOffset = _serializer.int32(obj.id_defecto, buffer, bufferOffset);
    // Serialize message field [id_defect_repair]
    bufferOffset = _serializer.int32(obj.id_defect_repair, buffer, bufferOffset);
    // Serialize message field [id_zona]
    bufferOffset = _serializer.int32(obj.id_zona, buffer, bufferOffset);
    // Serialize message field [path_panorama]
    bufferOffset = _serializer.string(obj.path_panorama, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type IROBOT_ir_dataRequest
    let len;
    let data = new IROBOT_ir_dataRequest(null);
    // Deserialize message field [load_inputdata]
    data.load_inputdata = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [load_polygon]
    data.load_polygon = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_input_data]
    data.get_input_data = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_working_zonesh]
    data.get_working_zonesh = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_working_zonesc]
    data.get_working_zonesc = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_inspection_zones]
    data.get_inspection_zones = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_rot_zone]
    data.get_rot_zone = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_adquireimgs]
    data.compute_adquireimgs = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_panorama]
    data.compute_panorama = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [merge_panoramas]
    data.merge_panoramas = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_detectpolys]
    data.compute_detectpolys = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_fcpp_defect_i]
    data.compute_fcpp_defect_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_fcpp_zone_i]
    data.compute_fcpp_zone_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [compute_fcpp_inspection_zone_i]
    data.compute_fcpp_inspection_zone_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [execute_fcpp_defect_i]
    data.execute_fcpp_defect_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [execute_fcpp_zone_i]
    data.execute_fcpp_zone_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [change_defect_reparation_goal]
    data.change_defect_reparation_goal = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [change_inspection_goal]
    data.change_inspection_goal = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_poly_i]
    data.get_poly_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_defect_i]
    data.get_defect_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_defect_path]
    data.get_defect_path = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_inspection_i]
    data.get_inspection_i = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_inspection_path]
    data.get_inspection_path = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [activate_vizs]
    data.activate_vizs = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [long_robotx]
    data.long_robotx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_roboty]
    data.long_roboty = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_herrx]
    data.long_herrx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_herry]
    data.long_herry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herrx]
    data.tras_herrx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herry]
    data.tras_herry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_camx]
    data.long_camx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_camy]
    data.long_camy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_camx]
    data.tras_camx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_camy]
    data.tras_camy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_areax]
    data.long_areax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_areay]
    data.long_areay = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [input_poly]
    data.input_poly = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [id_poly]
    data.id_poly = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [id_defecto]
    data.id_defecto = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [id_defect_repair]
    data.id_defect_repair = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [id_zona]
    data.id_zona = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [path_panorama]
    data.path_panorama = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.input_poly);
    length += object.path_panorama.length;
    return length + 92;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/IROBOT_ir_dataRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '910dac130eb554fea27a7f95622859e6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool load_inputdata
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
    int32 id_defect_repair
    
    
    int32 id_zona
    
    
    string path_panorama
    
    
    
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new IROBOT_ir_dataRequest(null);
    if (msg.load_inputdata !== undefined) {
      resolved.load_inputdata = msg.load_inputdata;
    }
    else {
      resolved.load_inputdata = false
    }

    if (msg.load_polygon !== undefined) {
      resolved.load_polygon = msg.load_polygon;
    }
    else {
      resolved.load_polygon = false
    }

    if (msg.get_input_data !== undefined) {
      resolved.get_input_data = msg.get_input_data;
    }
    else {
      resolved.get_input_data = false
    }

    if (msg.get_working_zonesh !== undefined) {
      resolved.get_working_zonesh = msg.get_working_zonesh;
    }
    else {
      resolved.get_working_zonesh = false
    }

    if (msg.get_working_zonesc !== undefined) {
      resolved.get_working_zonesc = msg.get_working_zonesc;
    }
    else {
      resolved.get_working_zonesc = false
    }

    if (msg.get_inspection_zones !== undefined) {
      resolved.get_inspection_zones = msg.get_inspection_zones;
    }
    else {
      resolved.get_inspection_zones = false
    }

    if (msg.get_rot_zone !== undefined) {
      resolved.get_rot_zone = msg.get_rot_zone;
    }
    else {
      resolved.get_rot_zone = false
    }

    if (msg.compute_adquireimgs !== undefined) {
      resolved.compute_adquireimgs = msg.compute_adquireimgs;
    }
    else {
      resolved.compute_adquireimgs = false
    }

    if (msg.compute_panorama !== undefined) {
      resolved.compute_panorama = msg.compute_panorama;
    }
    else {
      resolved.compute_panorama = false
    }

    if (msg.merge_panoramas !== undefined) {
      resolved.merge_panoramas = msg.merge_panoramas;
    }
    else {
      resolved.merge_panoramas = false
    }

    if (msg.compute_detectpolys !== undefined) {
      resolved.compute_detectpolys = msg.compute_detectpolys;
    }
    else {
      resolved.compute_detectpolys = false
    }

    if (msg.compute_fcpp_defect_i !== undefined) {
      resolved.compute_fcpp_defect_i = msg.compute_fcpp_defect_i;
    }
    else {
      resolved.compute_fcpp_defect_i = false
    }

    if (msg.compute_fcpp_zone_i !== undefined) {
      resolved.compute_fcpp_zone_i = msg.compute_fcpp_zone_i;
    }
    else {
      resolved.compute_fcpp_zone_i = false
    }

    if (msg.compute_fcpp_inspection_zone_i !== undefined) {
      resolved.compute_fcpp_inspection_zone_i = msg.compute_fcpp_inspection_zone_i;
    }
    else {
      resolved.compute_fcpp_inspection_zone_i = false
    }

    if (msg.execute_fcpp_defect_i !== undefined) {
      resolved.execute_fcpp_defect_i = msg.execute_fcpp_defect_i;
    }
    else {
      resolved.execute_fcpp_defect_i = false
    }

    if (msg.execute_fcpp_zone_i !== undefined) {
      resolved.execute_fcpp_zone_i = msg.execute_fcpp_zone_i;
    }
    else {
      resolved.execute_fcpp_zone_i = false
    }

    if (msg.change_defect_reparation_goal !== undefined) {
      resolved.change_defect_reparation_goal = msg.change_defect_reparation_goal;
    }
    else {
      resolved.change_defect_reparation_goal = false
    }

    if (msg.change_inspection_goal !== undefined) {
      resolved.change_inspection_goal = msg.change_inspection_goal;
    }
    else {
      resolved.change_inspection_goal = false
    }

    if (msg.get_poly_i !== undefined) {
      resolved.get_poly_i = msg.get_poly_i;
    }
    else {
      resolved.get_poly_i = false
    }

    if (msg.get_defect_i !== undefined) {
      resolved.get_defect_i = msg.get_defect_i;
    }
    else {
      resolved.get_defect_i = false
    }

    if (msg.get_defect_path !== undefined) {
      resolved.get_defect_path = msg.get_defect_path;
    }
    else {
      resolved.get_defect_path = false
    }

    if (msg.get_inspection_i !== undefined) {
      resolved.get_inspection_i = msg.get_inspection_i;
    }
    else {
      resolved.get_inspection_i = false
    }

    if (msg.get_inspection_path !== undefined) {
      resolved.get_inspection_path = msg.get_inspection_path;
    }
    else {
      resolved.get_inspection_path = false
    }

    if (msg.activate_vizs !== undefined) {
      resolved.activate_vizs = msg.activate_vizs;
    }
    else {
      resolved.activate_vizs = false
    }

    if (msg.long_robotx !== undefined) {
      resolved.long_robotx = msg.long_robotx;
    }
    else {
      resolved.long_robotx = 0.0
    }

    if (msg.long_roboty !== undefined) {
      resolved.long_roboty = msg.long_roboty;
    }
    else {
      resolved.long_roboty = 0.0
    }

    if (msg.long_herrx !== undefined) {
      resolved.long_herrx = msg.long_herrx;
    }
    else {
      resolved.long_herrx = 0.0
    }

    if (msg.long_herry !== undefined) {
      resolved.long_herry = msg.long_herry;
    }
    else {
      resolved.long_herry = 0.0
    }

    if (msg.tras_herrx !== undefined) {
      resolved.tras_herrx = msg.tras_herrx;
    }
    else {
      resolved.tras_herrx = 0.0
    }

    if (msg.tras_herry !== undefined) {
      resolved.tras_herry = msg.tras_herry;
    }
    else {
      resolved.tras_herry = 0.0
    }

    if (msg.long_camx !== undefined) {
      resolved.long_camx = msg.long_camx;
    }
    else {
      resolved.long_camx = 0.0
    }

    if (msg.long_camy !== undefined) {
      resolved.long_camy = msg.long_camy;
    }
    else {
      resolved.long_camy = 0.0
    }

    if (msg.tras_camx !== undefined) {
      resolved.tras_camx = msg.tras_camx;
    }
    else {
      resolved.tras_camx = 0.0
    }

    if (msg.tras_camy !== undefined) {
      resolved.tras_camy = msg.tras_camy;
    }
    else {
      resolved.tras_camy = 0.0
    }

    if (msg.long_areax !== undefined) {
      resolved.long_areax = msg.long_areax;
    }
    else {
      resolved.long_areax = 0.0
    }

    if (msg.long_areay !== undefined) {
      resolved.long_areay = msg.long_areay;
    }
    else {
      resolved.long_areay = 0.0
    }

    if (msg.input_poly !== undefined) {
      resolved.input_poly = geometry_msgs.msg.Polygon.Resolve(msg.input_poly)
    }
    else {
      resolved.input_poly = new geometry_msgs.msg.Polygon()
    }

    if (msg.id_poly !== undefined) {
      resolved.id_poly = msg.id_poly;
    }
    else {
      resolved.id_poly = 0
    }

    if (msg.id_defecto !== undefined) {
      resolved.id_defecto = msg.id_defecto;
    }
    else {
      resolved.id_defecto = 0
    }

    if (msg.id_defect_repair !== undefined) {
      resolved.id_defect_repair = msg.id_defect_repair;
    }
    else {
      resolved.id_defect_repair = 0
    }

    if (msg.id_zona !== undefined) {
      resolved.id_zona = msg.id_zona;
    }
    else {
      resolved.id_zona = 0
    }

    if (msg.path_panorama !== undefined) {
      resolved.path_panorama = msg.path_panorama;
    }
    else {
      resolved.path_panorama = ''
    }

    return resolved;
    }
};

class IROBOT_ir_dataResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.long_robotx = null;
      this.long_roboty = null;
      this.long_herrx = null;
      this.long_herry = null;
      this.tras_herrx = null;
      this.tras_herry = null;
      this.long_camx = null;
      this.long_camy = null;
      this.tras_camx = null;
      this.tras_camy = null;
      this.long_areax = null;
      this.long_areay = null;
      this.zoneh0 = null;
      this.zoneh90 = null;
      this.zoneh180 = null;
      this.zoneh270 = null;
      this.zonec0 = null;
      this.zonec90 = null;
      this.zonec180 = null;
      this.zonec270 = null;
      this.path_tray0 = null;
      this.path_tray90 = null;
      this.path_tray180 = null;
      this.path_tray270 = null;
      this.zone_rot = null;
      this.defecto_i = null;
      this.poly_i = null;
      this.n_defectos = null;
      this.defect_i_paths = null;
      this.inspection_i_paths = null;
    }
    else {
      if (initObj.hasOwnProperty('long_robotx')) {
        this.long_robotx = initObj.long_robotx
      }
      else {
        this.long_robotx = 0.0;
      }
      if (initObj.hasOwnProperty('long_roboty')) {
        this.long_roboty = initObj.long_roboty
      }
      else {
        this.long_roboty = 0.0;
      }
      if (initObj.hasOwnProperty('long_herrx')) {
        this.long_herrx = initObj.long_herrx
      }
      else {
        this.long_herrx = 0.0;
      }
      if (initObj.hasOwnProperty('long_herry')) {
        this.long_herry = initObj.long_herry
      }
      else {
        this.long_herry = 0.0;
      }
      if (initObj.hasOwnProperty('tras_herrx')) {
        this.tras_herrx = initObj.tras_herrx
      }
      else {
        this.tras_herrx = 0.0;
      }
      if (initObj.hasOwnProperty('tras_herry')) {
        this.tras_herry = initObj.tras_herry
      }
      else {
        this.tras_herry = 0.0;
      }
      if (initObj.hasOwnProperty('long_camx')) {
        this.long_camx = initObj.long_camx
      }
      else {
        this.long_camx = 0.0;
      }
      if (initObj.hasOwnProperty('long_camy')) {
        this.long_camy = initObj.long_camy
      }
      else {
        this.long_camy = 0.0;
      }
      if (initObj.hasOwnProperty('tras_camx')) {
        this.tras_camx = initObj.tras_camx
      }
      else {
        this.tras_camx = 0.0;
      }
      if (initObj.hasOwnProperty('tras_camy')) {
        this.tras_camy = initObj.tras_camy
      }
      else {
        this.tras_camy = 0.0;
      }
      if (initObj.hasOwnProperty('long_areax')) {
        this.long_areax = initObj.long_areax
      }
      else {
        this.long_areax = 0.0;
      }
      if (initObj.hasOwnProperty('long_areay')) {
        this.long_areay = initObj.long_areay
      }
      else {
        this.long_areay = 0.0;
      }
      if (initObj.hasOwnProperty('zoneh0')) {
        this.zoneh0 = initObj.zoneh0
      }
      else {
        this.zoneh0 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zoneh90')) {
        this.zoneh90 = initObj.zoneh90
      }
      else {
        this.zoneh90 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zoneh180')) {
        this.zoneh180 = initObj.zoneh180
      }
      else {
        this.zoneh180 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zoneh270')) {
        this.zoneh270 = initObj.zoneh270
      }
      else {
        this.zoneh270 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zonec0')) {
        this.zonec0 = initObj.zonec0
      }
      else {
        this.zonec0 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zonec90')) {
        this.zonec90 = initObj.zonec90
      }
      else {
        this.zonec90 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zonec180')) {
        this.zonec180 = initObj.zonec180
      }
      else {
        this.zonec180 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zonec270')) {
        this.zonec270 = initObj.zonec270
      }
      else {
        this.zonec270 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('path_tray0')) {
        this.path_tray0 = initObj.path_tray0
      }
      else {
        this.path_tray0 = [];
      }
      if (initObj.hasOwnProperty('path_tray90')) {
        this.path_tray90 = initObj.path_tray90
      }
      else {
        this.path_tray90 = [];
      }
      if (initObj.hasOwnProperty('path_tray180')) {
        this.path_tray180 = initObj.path_tray180
      }
      else {
        this.path_tray180 = [];
      }
      if (initObj.hasOwnProperty('path_tray270')) {
        this.path_tray270 = initObj.path_tray270
      }
      else {
        this.path_tray270 = [];
      }
      if (initObj.hasOwnProperty('zone_rot')) {
        this.zone_rot = initObj.zone_rot
      }
      else {
        this.zone_rot = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('defecto_i')) {
        this.defecto_i = initObj.defecto_i
      }
      else {
        this.defecto_i = new defecto();
      }
      if (initObj.hasOwnProperty('poly_i')) {
        this.poly_i = initObj.poly_i
      }
      else {
        this.poly_i = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('n_defectos')) {
        this.n_defectos = initObj.n_defectos
      }
      else {
        this.n_defectos = 0;
      }
      if (initObj.hasOwnProperty('defect_i_paths')) {
        this.defect_i_paths = initObj.defect_i_paths
      }
      else {
        this.defect_i_paths = [];
      }
      if (initObj.hasOwnProperty('inspection_i_paths')) {
        this.inspection_i_paths = initObj.inspection_i_paths
      }
      else {
        this.inspection_i_paths = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type IROBOT_ir_dataResponse
    // Serialize message field [long_robotx]
    bufferOffset = _serializer.float32(obj.long_robotx, buffer, bufferOffset);
    // Serialize message field [long_roboty]
    bufferOffset = _serializer.float32(obj.long_roboty, buffer, bufferOffset);
    // Serialize message field [long_herrx]
    bufferOffset = _serializer.float32(obj.long_herrx, buffer, bufferOffset);
    // Serialize message field [long_herry]
    bufferOffset = _serializer.float32(obj.long_herry, buffer, bufferOffset);
    // Serialize message field [tras_herrx]
    bufferOffset = _serializer.float32(obj.tras_herrx, buffer, bufferOffset);
    // Serialize message field [tras_herry]
    bufferOffset = _serializer.float32(obj.tras_herry, buffer, bufferOffset);
    // Serialize message field [long_camx]
    bufferOffset = _serializer.float32(obj.long_camx, buffer, bufferOffset);
    // Serialize message field [long_camy]
    bufferOffset = _serializer.float32(obj.long_camy, buffer, bufferOffset);
    // Serialize message field [tras_camx]
    bufferOffset = _serializer.float32(obj.tras_camx, buffer, bufferOffset);
    // Serialize message field [tras_camy]
    bufferOffset = _serializer.float32(obj.tras_camy, buffer, bufferOffset);
    // Serialize message field [long_areax]
    bufferOffset = _serializer.float32(obj.long_areax, buffer, bufferOffset);
    // Serialize message field [long_areay]
    bufferOffset = _serializer.float32(obj.long_areay, buffer, bufferOffset);
    // Serialize message field [zoneh0]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zoneh0, buffer, bufferOffset);
    // Serialize message field [zoneh90]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zoneh90, buffer, bufferOffset);
    // Serialize message field [zoneh180]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zoneh180, buffer, bufferOffset);
    // Serialize message field [zoneh270]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zoneh270, buffer, bufferOffset);
    // Serialize message field [zonec0]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zonec0, buffer, bufferOffset);
    // Serialize message field [zonec90]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zonec90, buffer, bufferOffset);
    // Serialize message field [zonec180]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zonec180, buffer, bufferOffset);
    // Serialize message field [zonec270]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zonec270, buffer, bufferOffset);
    // Serialize message field [path_tray0]
    // Serialize the length for message field [path_tray0]
    bufferOffset = _serializer.uint32(obj.path_tray0.length, buffer, bufferOffset);
    obj.path_tray0.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [path_tray90]
    // Serialize the length for message field [path_tray90]
    bufferOffset = _serializer.uint32(obj.path_tray90.length, buffer, bufferOffset);
    obj.path_tray90.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [path_tray180]
    // Serialize the length for message field [path_tray180]
    bufferOffset = _serializer.uint32(obj.path_tray180.length, buffer, bufferOffset);
    obj.path_tray180.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [path_tray270]
    // Serialize the length for message field [path_tray270]
    bufferOffset = _serializer.uint32(obj.path_tray270.length, buffer, bufferOffset);
    obj.path_tray270.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [zone_rot]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone_rot, buffer, bufferOffset);
    // Serialize message field [defecto_i]
    bufferOffset = defecto.serialize(obj.defecto_i, buffer, bufferOffset);
    // Serialize message field [poly_i]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.poly_i, buffer, bufferOffset);
    // Serialize message field [n_defectos]
    bufferOffset = _serializer.int32(obj.n_defectos, buffer, bufferOffset);
    // Serialize message field [defect_i_paths]
    // Serialize the length for message field [defect_i_paths]
    bufferOffset = _serializer.uint32(obj.defect_i_paths.length, buffer, bufferOffset);
    obj.defect_i_paths.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [inspection_i_paths]
    // Serialize the length for message field [inspection_i_paths]
    bufferOffset = _serializer.uint32(obj.inspection_i_paths.length, buffer, bufferOffset);
    obj.inspection_i_paths.forEach((val) => {
      bufferOffset = geometry_msgs.msg.PoseArray.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type IROBOT_ir_dataResponse
    let len;
    let data = new IROBOT_ir_dataResponse(null);
    // Deserialize message field [long_robotx]
    data.long_robotx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_roboty]
    data.long_roboty = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_herrx]
    data.long_herrx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_herry]
    data.long_herry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herrx]
    data.tras_herrx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herry]
    data.tras_herry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_camx]
    data.long_camx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_camy]
    data.long_camy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_camx]
    data.tras_camx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_camy]
    data.tras_camy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_areax]
    data.long_areax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_areay]
    data.long_areay = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zoneh0]
    data.zoneh0 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zoneh90]
    data.zoneh90 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zoneh180]
    data.zoneh180 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zoneh270]
    data.zoneh270 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zonec0]
    data.zonec0 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zonec90]
    data.zonec90 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zonec180]
    data.zonec180 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zonec270]
    data.zonec270 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [path_tray0]
    // Deserialize array length for message field [path_tray0]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.path_tray0 = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.path_tray0[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [path_tray90]
    // Deserialize array length for message field [path_tray90]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.path_tray90 = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.path_tray90[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [path_tray180]
    // Deserialize array length for message field [path_tray180]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.path_tray180 = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.path_tray180[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [path_tray270]
    // Deserialize array length for message field [path_tray270]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.path_tray270 = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.path_tray270[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [zone_rot]
    data.zone_rot = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [defecto_i]
    data.defecto_i = defecto.deserialize(buffer, bufferOffset);
    // Deserialize message field [poly_i]
    data.poly_i = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [n_defectos]
    data.n_defectos = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [defect_i_paths]
    // Deserialize array length for message field [defect_i_paths]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.defect_i_paths = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.defect_i_paths[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [inspection_i_paths]
    // Deserialize array length for message field [inspection_i_paths]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.inspection_i_paths = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.inspection_i_paths[i] = geometry_msgs.msg.PoseArray.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zoneh0);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zoneh90);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zoneh180);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zoneh270);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zonec0);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zonec90);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zonec180);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zonec270);
    object.path_tray0.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    object.path_tray90.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    object.path_tray180.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    object.path_tray270.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone_rot);
    length += defecto.getMessageSize(object.defecto_i);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.poly_i);
    object.defect_i_paths.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    object.inspection_i_paths.forEach((val) => {
      length += geometry_msgs.msg.PoseArray.getMessageSize(val);
    });
    return length + 76;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/IROBOT_ir_dataResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '500195b88b41473a35b10da448885a4f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new IROBOT_ir_dataResponse(null);
    if (msg.long_robotx !== undefined) {
      resolved.long_robotx = msg.long_robotx;
    }
    else {
      resolved.long_robotx = 0.0
    }

    if (msg.long_roboty !== undefined) {
      resolved.long_roboty = msg.long_roboty;
    }
    else {
      resolved.long_roboty = 0.0
    }

    if (msg.long_herrx !== undefined) {
      resolved.long_herrx = msg.long_herrx;
    }
    else {
      resolved.long_herrx = 0.0
    }

    if (msg.long_herry !== undefined) {
      resolved.long_herry = msg.long_herry;
    }
    else {
      resolved.long_herry = 0.0
    }

    if (msg.tras_herrx !== undefined) {
      resolved.tras_herrx = msg.tras_herrx;
    }
    else {
      resolved.tras_herrx = 0.0
    }

    if (msg.tras_herry !== undefined) {
      resolved.tras_herry = msg.tras_herry;
    }
    else {
      resolved.tras_herry = 0.0
    }

    if (msg.long_camx !== undefined) {
      resolved.long_camx = msg.long_camx;
    }
    else {
      resolved.long_camx = 0.0
    }

    if (msg.long_camy !== undefined) {
      resolved.long_camy = msg.long_camy;
    }
    else {
      resolved.long_camy = 0.0
    }

    if (msg.tras_camx !== undefined) {
      resolved.tras_camx = msg.tras_camx;
    }
    else {
      resolved.tras_camx = 0.0
    }

    if (msg.tras_camy !== undefined) {
      resolved.tras_camy = msg.tras_camy;
    }
    else {
      resolved.tras_camy = 0.0
    }

    if (msg.long_areax !== undefined) {
      resolved.long_areax = msg.long_areax;
    }
    else {
      resolved.long_areax = 0.0
    }

    if (msg.long_areay !== undefined) {
      resolved.long_areay = msg.long_areay;
    }
    else {
      resolved.long_areay = 0.0
    }

    if (msg.zoneh0 !== undefined) {
      resolved.zoneh0 = geometry_msgs.msg.Polygon.Resolve(msg.zoneh0)
    }
    else {
      resolved.zoneh0 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zoneh90 !== undefined) {
      resolved.zoneh90 = geometry_msgs.msg.Polygon.Resolve(msg.zoneh90)
    }
    else {
      resolved.zoneh90 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zoneh180 !== undefined) {
      resolved.zoneh180 = geometry_msgs.msg.Polygon.Resolve(msg.zoneh180)
    }
    else {
      resolved.zoneh180 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zoneh270 !== undefined) {
      resolved.zoneh270 = geometry_msgs.msg.Polygon.Resolve(msg.zoneh270)
    }
    else {
      resolved.zoneh270 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zonec0 !== undefined) {
      resolved.zonec0 = geometry_msgs.msg.Polygon.Resolve(msg.zonec0)
    }
    else {
      resolved.zonec0 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zonec90 !== undefined) {
      resolved.zonec90 = geometry_msgs.msg.Polygon.Resolve(msg.zonec90)
    }
    else {
      resolved.zonec90 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zonec180 !== undefined) {
      resolved.zonec180 = geometry_msgs.msg.Polygon.Resolve(msg.zonec180)
    }
    else {
      resolved.zonec180 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zonec270 !== undefined) {
      resolved.zonec270 = geometry_msgs.msg.Polygon.Resolve(msg.zonec270)
    }
    else {
      resolved.zonec270 = new geometry_msgs.msg.Polygon()
    }

    if (msg.path_tray0 !== undefined) {
      resolved.path_tray0 = new Array(msg.path_tray0.length);
      for (let i = 0; i < resolved.path_tray0.length; ++i) {
        resolved.path_tray0[i] = geometry_msgs.msg.PoseArray.Resolve(msg.path_tray0[i]);
      }
    }
    else {
      resolved.path_tray0 = []
    }

    if (msg.path_tray90 !== undefined) {
      resolved.path_tray90 = new Array(msg.path_tray90.length);
      for (let i = 0; i < resolved.path_tray90.length; ++i) {
        resolved.path_tray90[i] = geometry_msgs.msg.PoseArray.Resolve(msg.path_tray90[i]);
      }
    }
    else {
      resolved.path_tray90 = []
    }

    if (msg.path_tray180 !== undefined) {
      resolved.path_tray180 = new Array(msg.path_tray180.length);
      for (let i = 0; i < resolved.path_tray180.length; ++i) {
        resolved.path_tray180[i] = geometry_msgs.msg.PoseArray.Resolve(msg.path_tray180[i]);
      }
    }
    else {
      resolved.path_tray180 = []
    }

    if (msg.path_tray270 !== undefined) {
      resolved.path_tray270 = new Array(msg.path_tray270.length);
      for (let i = 0; i < resolved.path_tray270.length; ++i) {
        resolved.path_tray270[i] = geometry_msgs.msg.PoseArray.Resolve(msg.path_tray270[i]);
      }
    }
    else {
      resolved.path_tray270 = []
    }

    if (msg.zone_rot !== undefined) {
      resolved.zone_rot = geometry_msgs.msg.Polygon.Resolve(msg.zone_rot)
    }
    else {
      resolved.zone_rot = new geometry_msgs.msg.Polygon()
    }

    if (msg.defecto_i !== undefined) {
      resolved.defecto_i = defecto.Resolve(msg.defecto_i)
    }
    else {
      resolved.defecto_i = new defecto()
    }

    if (msg.poly_i !== undefined) {
      resolved.poly_i = geometry_msgs.msg.Polygon.Resolve(msg.poly_i)
    }
    else {
      resolved.poly_i = new geometry_msgs.msg.Polygon()
    }

    if (msg.n_defectos !== undefined) {
      resolved.n_defectos = msg.n_defectos;
    }
    else {
      resolved.n_defectos = 0
    }

    if (msg.defect_i_paths !== undefined) {
      resolved.defect_i_paths = new Array(msg.defect_i_paths.length);
      for (let i = 0; i < resolved.defect_i_paths.length; ++i) {
        resolved.defect_i_paths[i] = geometry_msgs.msg.PoseArray.Resolve(msg.defect_i_paths[i]);
      }
    }
    else {
      resolved.defect_i_paths = []
    }

    if (msg.inspection_i_paths !== undefined) {
      resolved.inspection_i_paths = new Array(msg.inspection_i_paths.length);
      for (let i = 0; i < resolved.inspection_i_paths.length; ++i) {
        resolved.inspection_i_paths[i] = geometry_msgs.msg.PoseArray.Resolve(msg.inspection_i_paths[i]);
      }
    }
    else {
      resolved.inspection_i_paths = []
    }

    return resolved;
    }
};

module.exports = {
  Request: IROBOT_ir_dataRequest,
  Response: IROBOT_ir_dataResponse,
  md5sum() { return 'ae9b2e14b3730f735edbdd6f2ac13cb8'; },
  datatype() { return 'irobot_fcpp_simul/IROBOT_ir_data'; }
};
