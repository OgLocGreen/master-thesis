// Auto-generated. Do not edit!

// (in-package irobot_fcpp_simul.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let defecto_simple = require('./defecto_simple.js');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class defecto_zona {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ros_poly = null;
      this.trap_vec = null;
      this.direccion_rep = null;
      this.reparado = null;
      this.zona = null;
    }
    else {
      if (initObj.hasOwnProperty('ros_poly')) {
        this.ros_poly = initObj.ros_poly
      }
      else {
        this.ros_poly = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('trap_vec')) {
        this.trap_vec = initObj.trap_vec
      }
      else {
        this.trap_vec = [];
      }
      if (initObj.hasOwnProperty('direccion_rep')) {
        this.direccion_rep = initObj.direccion_rep
      }
      else {
        this.direccion_rep = 0;
      }
      if (initObj.hasOwnProperty('reparado')) {
        this.reparado = initObj.reparado
      }
      else {
        this.reparado = false;
      }
      if (initObj.hasOwnProperty('zona')) {
        this.zona = initObj.zona
      }
      else {
        this.zona = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type defecto_zona
    // Serialize message field [ros_poly]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.ros_poly, buffer, bufferOffset);
    // Serialize message field [trap_vec]
    // Serialize the length for message field [trap_vec]
    bufferOffset = _serializer.uint32(obj.trap_vec.length, buffer, bufferOffset);
    obj.trap_vec.forEach((val) => {
      bufferOffset = defecto_simple.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [direccion_rep]
    bufferOffset = _serializer.int32(obj.direccion_rep, buffer, bufferOffset);
    // Serialize message field [reparado]
    bufferOffset = _serializer.bool(obj.reparado, buffer, bufferOffset);
    // Serialize message field [zona]
    bufferOffset = _serializer.int32(obj.zona, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type defecto_zona
    let len;
    let data = new defecto_zona(null);
    // Deserialize message field [ros_poly]
    data.ros_poly = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [trap_vec]
    // Deserialize array length for message field [trap_vec]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trap_vec = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trap_vec[i] = defecto_simple.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [direccion_rep]
    data.direccion_rep = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [reparado]
    data.reparado = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [zona]
    data.zona = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.ros_poly);
    object.trap_vec.forEach((val) => {
      length += defecto_simple.getMessageSize(val);
    });
    return length + 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'irobot_fcpp_simul/defecto_zona';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '66d6ef707c05e8c8eaa69b175e897e44';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Polygon ros_poly
    defecto_simple[] trap_vec
    
    int32 direccion_rep
    bool reparado
    int32 zona
    
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
    const resolved = new defecto_zona(null);
    if (msg.ros_poly !== undefined) {
      resolved.ros_poly = geometry_msgs.msg.Polygon.Resolve(msg.ros_poly)
    }
    else {
      resolved.ros_poly = new geometry_msgs.msg.Polygon()
    }

    if (msg.trap_vec !== undefined) {
      resolved.trap_vec = new Array(msg.trap_vec.length);
      for (let i = 0; i < resolved.trap_vec.length; ++i) {
        resolved.trap_vec[i] = defecto_simple.Resolve(msg.trap_vec[i]);
      }
    }
    else {
      resolved.trap_vec = []
    }

    if (msg.direccion_rep !== undefined) {
      resolved.direccion_rep = msg.direccion_rep;
    }
    else {
      resolved.direccion_rep = 0
    }

    if (msg.reparado !== undefined) {
      resolved.reparado = msg.reparado;
    }
    else {
      resolved.reparado = false
    }

    if (msg.zona !== undefined) {
      resolved.zona = msg.zona;
    }
    else {
      resolved.zona = 0
    }

    return resolved;
    }
};

module.exports = defecto_zona;
