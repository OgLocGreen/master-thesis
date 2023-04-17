// Auto-generated. Do not edit!

// (in-package irobot_fcpp_simul.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let defecto_zona = require('./defecto_zona.js');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class defecto {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ros_poly = null;
      this.defecto_divpor_zonas = null;
      this.reparado = null;
    }
    else {
      if (initObj.hasOwnProperty('ros_poly')) {
        this.ros_poly = initObj.ros_poly
      }
      else {
        this.ros_poly = new geometry_msgs.msg.Polygon();
      }
      if (initObj.hasOwnProperty('defecto_divpor_zonas')) {
        this.defecto_divpor_zonas = initObj.defecto_divpor_zonas
      }
      else {
        this.defecto_divpor_zonas = [];
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
    // Serializes a message object of type defecto
    // Serialize message field [ros_poly]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.ros_poly, buffer, bufferOffset);
    // Serialize message field [defecto_divpor_zonas]
    // Serialize the length for message field [defecto_divpor_zonas]
    bufferOffset = _serializer.uint32(obj.defecto_divpor_zonas.length, buffer, bufferOffset);
    obj.defecto_divpor_zonas.forEach((val) => {
      bufferOffset = defecto_zona.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [reparado]
    bufferOffset = _serializer.bool(obj.reparado, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type defecto
    let len;
    let data = new defecto(null);
    // Deserialize message field [ros_poly]
    data.ros_poly = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [defecto_divpor_zonas]
    // Deserialize array length for message field [defecto_divpor_zonas]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.defecto_divpor_zonas = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.defecto_divpor_zonas[i] = defecto_zona.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [reparado]
    data.reparado = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.ros_poly);
    object.defecto_divpor_zonas.forEach((val) => {
      length += defecto_zona.getMessageSize(val);
    });
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'irobot_fcpp_simul/defecto';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6f4dca0cbac38a321305ee29edd2c608';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new defecto(null);
    if (msg.ros_poly !== undefined) {
      resolved.ros_poly = geometry_msgs.msg.Polygon.Resolve(msg.ros_poly)
    }
    else {
      resolved.ros_poly = new geometry_msgs.msg.Polygon()
    }

    if (msg.defecto_divpor_zonas !== undefined) {
      resolved.defecto_divpor_zonas = new Array(msg.defecto_divpor_zonas.length);
      for (let i = 0; i < resolved.defecto_divpor_zonas.length; ++i) {
        resolved.defecto_divpor_zonas[i] = defecto_zona.Resolve(msg.defecto_divpor_zonas[i]);
      }
    }
    else {
      resolved.defecto_divpor_zonas = []
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

module.exports = defecto;
