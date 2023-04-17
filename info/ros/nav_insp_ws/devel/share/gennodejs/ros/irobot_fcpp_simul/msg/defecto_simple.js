// Auto-generated. Do not edit!

// (in-package irobot_fcpp_simul.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class defecto_simple {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ros_poly = null;
      this.direccion_rep = null;
      this.reparado = null;
    }
    else {
      if (initObj.hasOwnProperty('ros_poly')) {
        this.ros_poly = initObj.ros_poly
      }
      else {
        this.ros_poly = new geometry_msgs.msg.Polygon();
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
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type defecto_simple
    // Serialize message field [ros_poly]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.ros_poly, buffer, bufferOffset);
    // Serialize message field [direccion_rep]
    bufferOffset = _serializer.int32(obj.direccion_rep, buffer, bufferOffset);
    // Serialize message field [reparado]
    bufferOffset = _serializer.bool(obj.reparado, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type defecto_simple
    let len;
    let data = new defecto_simple(null);
    // Deserialize message field [ros_poly]
    data.ros_poly = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [direccion_rep]
    data.direccion_rep = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [reparado]
    data.reparado = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.ros_poly);
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'irobot_fcpp_simul/defecto_simple';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9e9103e825e653e77fe6292f6a6f8a76';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Polygon ros_poly
    int32 direccion_rep
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new defecto_simple(null);
    if (msg.ros_poly !== undefined) {
      resolved.ros_poly = geometry_msgs.msg.Polygon.Resolve(msg.ros_poly)
    }
    else {
      resolved.ros_poly = new geometry_msgs.msg.Polygon()
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

    return resolved;
    }
};

module.exports = defecto_simple;
