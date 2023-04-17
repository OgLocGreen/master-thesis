// Auto-generated. Do not edit!

// (in-package action_server_package.srv)


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
    }
    else {
      if (initObj.hasOwnProperty('id_input')) {
        this.id_input = initObj.id_input
      }
      else {
        this.id_input = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_inRequest
    // Serialize message field [id_input]
    bufferOffset = _serializer.int32(obj.id_input, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_inRequest
    let len;
    let data = new FCPP_inRequest(null);
    // Deserialize message field [id_input]
    data.id_input = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'action_server_package/FCPP_inRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '18c8679e6d3855a24222ca635f731460';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 id_input
    
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

    return resolved;
    }
};

class FCPP_inResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.n_defects = null;
      this.xmin_chapa = null;
      this.xmax_chapa = null;
      this.ymin_chapa = null;
      this.ymax_chapa = null;
      this.poly_i = null;
      this.number_of_chapas = null;
    }
    else {
      if (initObj.hasOwnProperty('n_defects')) {
        this.n_defects = initObj.n_defects
      }
      else {
        this.n_defects = 0;
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
      if (initObj.hasOwnProperty('number_of_chapas')) {
        this.number_of_chapas = initObj.number_of_chapas
      }
      else {
        this.number_of_chapas = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_inResponse
    // Serialize message field [n_defects]
    bufferOffset = _serializer.int32(obj.n_defects, buffer, bufferOffset);
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
    // Serialize message field [number_of_chapas]
    bufferOffset = _serializer.int32(obj.number_of_chapas, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_inResponse
    let len;
    let data = new FCPP_inResponse(null);
    // Deserialize message field [n_defects]
    data.n_defects = _deserializer.int32(buffer, bufferOffset);
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
    // Deserialize message field [number_of_chapas]
    data.number_of_chapas = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.poly_i);
    return length + 24;
  }

  static datatype() {
    // Returns string type for a service object
    return 'action_server_package/FCPP_inResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '92057b47e7ea13416595ec12aecf76a5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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

    if (msg.number_of_chapas !== undefined) {
      resolved.number_of_chapas = msg.number_of_chapas;
    }
    else {
      resolved.number_of_chapas = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: FCPP_inRequest,
  Response: FCPP_inResponse,
  md5sum() { return '3a9946ec5195dc8fb4f14eeb6ec2e339'; },
  datatype() { return 'action_server_package/FCPP_in'; }
};
