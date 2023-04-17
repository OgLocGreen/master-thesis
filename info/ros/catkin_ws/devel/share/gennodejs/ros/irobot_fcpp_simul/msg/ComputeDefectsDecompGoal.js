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

class ComputeDefectsDecompGoal {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.chapa_id = null;
      this.poly_defect = null;
      this.zone0 = null;
      this.zone90 = null;
      this.zone180 = null;
      this.zone270 = null;
      this.xmax = null;
      this.ymax = null;
    }
    else {
      if (initObj.hasOwnProperty('chapa_id')) {
        this.chapa_id = initObj.chapa_id
      }
      else {
        this.chapa_id = 0;
      }
      if (initObj.hasOwnProperty('poly_defect')) {
        this.poly_defect = initObj.poly_defect
      }
      else {
        this.poly_defect = new geometry_msgs.msg.Polygon();
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
      if (initObj.hasOwnProperty('xmax')) {
        this.xmax = initObj.xmax
      }
      else {
        this.xmax = 0.0;
      }
      if (initObj.hasOwnProperty('ymax')) {
        this.ymax = initObj.ymax
      }
      else {
        this.ymax = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ComputeDefectsDecompGoal
    // Serialize message field [chapa_id]
    bufferOffset = _serializer.int32(obj.chapa_id, buffer, bufferOffset);
    // Serialize message field [poly_defect]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.poly_defect, buffer, bufferOffset);
    // Serialize message field [zone0]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone0, buffer, bufferOffset);
    // Serialize message field [zone90]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone90, buffer, bufferOffset);
    // Serialize message field [zone180]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone180, buffer, bufferOffset);
    // Serialize message field [zone270]
    bufferOffset = geometry_msgs.msg.Polygon.serialize(obj.zone270, buffer, bufferOffset);
    // Serialize message field [xmax]
    bufferOffset = _serializer.float32(obj.xmax, buffer, bufferOffset);
    // Serialize message field [ymax]
    bufferOffset = _serializer.float32(obj.ymax, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ComputeDefectsDecompGoal
    let len;
    let data = new ComputeDefectsDecompGoal(null);
    // Deserialize message field [chapa_id]
    data.chapa_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [poly_defect]
    data.poly_defect = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone0]
    data.zone0 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone90]
    data.zone90 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone180]
    data.zone180 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [zone270]
    data.zone270 = geometry_msgs.msg.Polygon.deserialize(buffer, bufferOffset);
    // Deserialize message field [xmax]
    data.xmax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ymax]
    data.ymax = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.Polygon.getMessageSize(object.poly_defect);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone0);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone90);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone180);
    length += geometry_msgs.msg.Polygon.getMessageSize(object.zone270);
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'irobot_fcpp_simul/ComputeDefectsDecompGoal';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '100a9f9d0c5c91d1ec171cccc3fdc2c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    # Define the goal
    int32 chapa_id
    
    geometry_msgs/Polygon poly_defect
    
    
    geometry_msgs/Polygon zone0
    geometry_msgs/Polygon zone90
    geometry_msgs/Polygon zone180
    geometry_msgs/Polygon zone270
    
    float32 xmax
    float32 ymax
    
    
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
    const resolved = new ComputeDefectsDecompGoal(null);
    if (msg.chapa_id !== undefined) {
      resolved.chapa_id = msg.chapa_id;
    }
    else {
      resolved.chapa_id = 0
    }

    if (msg.poly_defect !== undefined) {
      resolved.poly_defect = geometry_msgs.msg.Polygon.Resolve(msg.poly_defect)
    }
    else {
      resolved.poly_defect = new geometry_msgs.msg.Polygon()
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

    if (msg.xmax !== undefined) {
      resolved.xmax = msg.xmax;
    }
    else {
      resolved.xmax = 0.0
    }

    if (msg.ymax !== undefined) {
      resolved.ymax = msg.ymax;
    }
    else {
      resolved.ymax = 0.0
    }

    return resolved;
    }
};

module.exports = ComputeDefectsDecompGoal;
