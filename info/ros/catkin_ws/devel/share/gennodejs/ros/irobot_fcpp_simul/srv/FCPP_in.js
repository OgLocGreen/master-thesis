// Auto-generated. Do not edit!

// (in-package irobot_fcpp_simul.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class FCPP_inRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id_input = null;
      this.get_working_zones = null;
      this.get_inspection_zones = null;
      this.get_rot_zone = null;
    }
    else {
      if (initObj.hasOwnProperty('id_input')) {
        this.id_input = initObj.id_input
      }
      else {
        this.id_input = 0;
      }
      if (initObj.hasOwnProperty('get_working_zones')) {
        this.get_working_zones = initObj.get_working_zones
      }
      else {
        this.get_working_zones = false;
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
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_inRequest
    // Serialize message field [id_input]
    bufferOffset = _serializer.int32(obj.id_input, buffer, bufferOffset);
    // Serialize message field [get_working_zones]
    bufferOffset = _serializer.bool(obj.get_working_zones, buffer, bufferOffset);
    // Serialize message field [get_inspection_zones]
    bufferOffset = _serializer.bool(obj.get_inspection_zones, buffer, bufferOffset);
    // Serialize message field [get_rot_zone]
    bufferOffset = _serializer.bool(obj.get_rot_zone, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_inRequest
    let len;
    let data = new FCPP_inRequest(null);
    // Deserialize message field [id_input]
    data.id_input = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [get_working_zones]
    data.get_working_zones = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_inspection_zones]
    data.get_inspection_zones = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [get_rot_zone]
    data.get_rot_zone = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 7;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/FCPP_inRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ab3c84f8b5d4cbb9d71b6a57611e603a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 id_input
    bool get_working_zones
    bool get_inspection_zones
    bool get_rot_zone
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FCPP_inRequest(null);
    if (msg.id_input !== undefined) {
      resolved.id_input = msg.id_input;
    }
    else {
      resolved.id_input = 0
    }

    if (msg.get_working_zones !== undefined) {
      resolved.get_working_zones = msg.get_working_zones;
    }
    else {
      resolved.get_working_zones = false
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

    return resolved;
    }
};

class FCPP_inResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.n_defects = null;
      this.herr_lat = null;
      this.herr_proa = null;
      this.herr_popa = null;
      this.long_robotx = null;
      this.long_roboty = null;
      this.tras_herrx = null;
      this.tras_herry = null;
      this.xmin_chapa = null;
      this.xmax_chapa = null;
      this.ymin_chapa = null;
      this.ymax_chapa = null;
      this.poly_i = null;
      this.zone0 = null;
      this.zone90 = null;
      this.zone180 = null;
      this.zone270 = null;
      this.zone_rot = null;
    }
    else {
      if (initObj.hasOwnProperty('n_defects')) {
        this.n_defects = initObj.n_defects
      }
      else {
        this.n_defects = 0;
      }
      if (initObj.hasOwnProperty('herr_lat')) {
        this.herr_lat = initObj.herr_lat
      }
      else {
        this.herr_lat = 0.0;
      }
      if (initObj.hasOwnProperty('herr_proa')) {
        this.herr_proa = initObj.herr_proa
      }
      else {
        this.herr_proa = 0.0;
      }
      if (initObj.hasOwnProperty('herr_popa')) {
        this.herr_popa = initObj.herr_popa
      }
      else {
        this.herr_popa = 0.0;
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
      if (initObj.hasOwnProperty('xmin_chapa')) {
        this.xmin_chapa = initObj.xmin_chapa
      }
      else {
        this.xmin_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('xmax_chapa')) {
        this.xmax_chapa = initObj.xmax_chapa
      }
      else {
        this.xmax_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('ymin_chapa')) {
        this.ymin_chapa = initObj.ymin_chapa
      }
      else {
        this.ymin_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('ymax_chapa')) {
        this.ymax_chapa = initObj.ymax_chapa
      }
      else {
        this.ymax_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('poly_i')) {
        this.poly_i = initObj.poly_i
      }
      else {
        this.poly_i = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zone0')) {
        this.zone0 = initObj.zone0
      }
      else {
        this.zone0 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zone90')) {
        this.zone90 = initObj.zone90
      }
      else {
        this.zone90 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zone180')) {
        this.zone180 = initObj.zone180
      }
      else {
        this.zone180 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zone270')) {
        this.zone270 = initObj.zone270
      }
      else {
        this.zone270 = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('zone_rot')) {
        this.zone_rot = initObj.zone_rot
      }
      else {
        this.zone_rot = new geometry_msgs.msg.Polygon();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_inResponse
    // Serialize message field [n_defects]
    bufferOffset = _serializer.int32(obj.n_defects, buffer, bufferOffset);
    // Serialize message field [herr_lat]
    bufferOffset = _serializer.float32(obj.herr_lat, buffer, bufferOffset);
    // Serialize message field [herr_proa]
    bufferOffset = _serializer.float32(obj.herr_proa, buffer, bufferOffset);
    // Serialize message field [herr_popa]
    bufferOffset = _serializer.float32(obj.herr_popa, buffer, bufferOffset);
    // Serialize message field [long_robotx]
    bufferOffset = _serializer.float32(obj.long_robotx, buffer, bufferOffset);
    // Serialize message field [long_roboty]
    bufferOffset = _serializer.float32(obj.long_roboty, buffer, bufferOffset);
    // Serialize message field [tras_herrx]
    bufferOffset = _serializer.float32(obj.tras_herrx, buffer, bufferOffset);
    // Serialize message field [tras_herry]
    bufferOffset = _serializer.float32(obj.tras_herry, buffer, bufferOffset);
    // Serialize message field [xmin_chapa]
    bufferOffset = _serializer.float32(obj.xmin_chapa, buffer, bufferOffset);
    // Serialize message field [xmax_chapa]
    bufferOffset = _serializer.float32(obj.xmax_chapa, buffer, bufferOffset);
    // Serialize message field [ymin_chapa]
    bufferOffset = _serializer.float32(obj.ymin_chapa, buffer, bufferOffset);
    // Serialize message field [ymax_chapa]
    bufferOffset = _serializer.float32(obj.ymax_chapa, buffer, bufferOffset);
    // Serialize message field [poly_i]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.poly_i, buffer, bufferOffset);
    // Serialize message field [zone0]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone0, buffer, bufferOffset);
    // Serialize message field [zone90]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone90, buffer, bufferOffset);
    // Serialize message field [zone180]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone180, buffer, bufferOffset);
    // Serialize message field [zone270]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone270, buffer, bufferOffset);
    // Serialize message field [zone_rot]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone_rot, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_inResponse
    let len;
    let data = new FCPP_inResponse(null);
    // Deserialize message field [n_defects]
    data.n_defects = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [herr_lat]
    data.herr_lat = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [herr_proa]
    data.herr_proa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [herr_popa]
    data.herr_popa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_robotx]
    data.long_robotx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [long_roboty]
    data.long_roboty = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herrx]
    data.tras_herrx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tras_herry]
    data.tras_herry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [xmin_chapa]
    data.xmin_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [xmax_chapa]
    data.xmax_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ymin_chapa]
    data.ymin_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ymax_chapa]
    data.ymax_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [poly_i]
    data.poly_i = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone0]
    data.zone0 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone90]
    data.zone90 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone180]
    data.zone180 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone270]
    data.zone270 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone_rot]
    data.zone_rot = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.poly_i);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone0);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone90);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone180);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone270);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone_rot);
    return length + 48;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/FCPP_inResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4a6d5622fc972a91f6327482e4705f63';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
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
    float32 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FCPP_inResponse(null);
    if (msg.n_defects !== undefined) {
      resolved.n_defects = msg.n_defects;
    }
    else {
      resolved.n_defects = 0
    }

    if (msg.herr_lat !== undefined) {
      resolved.herr_lat = msg.herr_lat;
    }
    else {
      resolved.herr_lat = 0.0
    }

    if (msg.herr_proa !== undefined) {
      resolved.herr_proa = msg.herr_proa;
    }
    else {
      resolved.herr_proa = 0.0
    }

    if (msg.herr_popa !== undefined) {
      resolved.herr_popa = msg.herr_popa;
    }
    else {
      resolved.herr_popa = 0.0
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

    if (msg.xmin_chapa !== undefined) {
      resolved.xmin_chapa = msg.xmin_chapa;
    }
    else {
      resolved.xmin_chapa = 0.0
    }

    if (msg.xmax_chapa !== undefined) {
      resolved.xmax_chapa = msg.xmax_chapa;
    }
    else {
      resolved.xmax_chapa = 0.0
    }

    if (msg.ymin_chapa !== undefined) {
      resolved.ymin_chapa = msg.ymin_chapa;
    }
    else {
      resolved.ymin_chapa = 0.0
    }

    if (msg.ymax_chapa !== undefined) {
      resolved.ymax_chapa = msg.ymax_chapa;
    }
    else {
      resolved.ymax_chapa = 0.0
    }

    if (msg.poly_i !== undefined) {
      resolved.poly_i = geometry_msgs.msg.Polygon.Resolve(msg.poly_i)
    }
    else {
      resolved.poly_i = new geometry_msgs.msg.Polygon()
    }

    if (msg.zone0 !== undefined) {
      resolved.zone0 = geometry_msgs.msg.Polygon.Resolve(msg.zone0)
    }
    else {
      resolved.zone0 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zone90 !== undefined) {
      resolved.zone90 = geometry_msgs.msg.Polygon.Resolve(msg.zone90)
    }
    else {
      resolved.zone90 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zone180 !== undefined) {
      resolved.zone180 = geometry_msgs.msg.Polygon.Resolve(msg.zone180)
    }
    else {
      resolved.zone180 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zone270 !== undefined) {
      resolved.zone270 = geometry_msgs.msg.Polygon.Resolve(msg.zone270)
    }
    else {
      resolved.zone270 = new geometry_msgs.msg.Polygon()
    }

    if (msg.zone_rot !== undefined) {
      resolved.zone_rot = geometry_msgs.msg.Polygon.Resolve(msg.zone_rot)
    }
    else {
      resolved.zone_rot = new geometry_msgs.msg.Polygon()
    }

    return resolved;
    }
};

module.exports = {
  Request: FCPP_inRequest,
  Response: FCPP_inResponse,
  md5sum() { return '26aa20be26a641c44400aa9da8ffcd13'; },
  datatype() { return 'irobot_fcpp_simul/FCPP_in'; }
};
