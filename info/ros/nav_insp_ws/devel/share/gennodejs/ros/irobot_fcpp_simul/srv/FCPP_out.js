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

let defecto = require('../msg/defecto.js');

//-----------------------------------------------------------

class FCPP_outRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_outRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_outRequest
    let len;
    let data = new FCPP_outRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/FCPP_outRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FCPP_outRequest(null);
    return resolved;
    }
};

class FCPP_outResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.defecto_out = null;
    }
    else {
      if (initObj.hasOwnProperty('defecto_out')) {
        this.defecto_out = initObj.defecto_out
      }
      else {
        this.defecto_out = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FCPP_outResponse
    // Serialize message field [defecto_out]
    // Serialize the length for message field [defecto_out]
    bufferOffset = _serializer.uint32(obj.defecto_out.length, buffer, bufferOffset);
    obj.defecto_out.forEach((val) => {
      bufferOffset = defecto.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FCPP_outResponse
    let len;
    let data = new FCPP_outResponse(null);
    // Deserialize message field [defecto_out]
    // Deserialize array length for message field [defecto_out]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.defecto_out = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.defecto_out[i] = defecto.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.defecto_out.forEach((val) => {
      length += defecto.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'irobot_fcpp_simul/FCPP_outResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '30c6047a6867f6dfad71ccb5b3d8e613';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    defecto[] defecto_out
    
    
    ================================================================================
    MSG: irobot_fcpp_simul/defecto
    geometry_msgs/Polygon ros_poly
    defecto_zona[] defecto_divpor_zonas
    
    bool reparado
    
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
    const resolved = new FCPP_outResponse(null);
    if (msg.defecto_out !== undefined) {
      resolved.defecto_out = new Array(msg.defecto_out.length);
      for (let i = 0; i < resolved.defecto_out.length; ++i) {
        resolved.defecto_out[i] = defecto.Resolve(msg.defecto_out[i]);
      }
    }
    else {
      resolved.defecto_out = []
    }

    return resolved;
    }
};

module.exports = {
  Request: FCPP_outRequest,
  Response: FCPP_outResponse,
  md5sum() { return '30c6047a6867f6dfad71ccb5b3d8e613'; },
  datatype() { return 'irobot_fcpp_simul/FCPP_out'; }
};
