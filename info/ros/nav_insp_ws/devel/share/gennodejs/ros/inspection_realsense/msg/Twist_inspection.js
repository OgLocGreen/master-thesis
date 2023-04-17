// Auto-generated. Do not edit!

// (in-package inspection_realsense.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Twist_inspection {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.linear = null;
      this.angular = null;
      this.distance_left = null;
    }
    else {
      if (initObj.hasOwnProperty('linear')) {
        this.linear = initObj.linear
      }
      else {
        this.linear = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('angular')) {
        this.angular = initObj.angular
      }
      else {
        this.angular = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('distance_left')) {
        this.distance_left = initObj.distance_left
      }
      else {
        this.distance_left = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Twist_inspection
    // Serialize message field [linear]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.linear, buffer, bufferOffset);
    // Serialize message field [angular]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.angular, buffer, bufferOffset);
    // Serialize message field [distance_left]
    bufferOffset = _serializer.float32(obj.distance_left, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Twist_inspection
    let len;
    let data = new Twist_inspection(null);
    // Deserialize message field [linear]
    data.linear = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [angular]
    data.angular = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [distance_left]
    data.distance_left = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'inspection_realsense/Twist_inspection';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a6d97e5058c8a6d2a96e566db38def37';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # This expresses velocity in free space broken into it's linear and angular parts. Also, the distance left to leave the sheet
    geometry_msgs/Vector3  linear
    geometry_msgs/Vector3  angular
    float32  distance_left
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Twist_inspection(null);
    if (msg.linear !== undefined) {
      resolved.linear = geometry_msgs.msg.Vector3.Resolve(msg.linear)
    }
    else {
      resolved.linear = new geometry_msgs.msg.Vector3()
    }

    if (msg.angular !== undefined) {
      resolved.angular = geometry_msgs.msg.Vector3.Resolve(msg.angular)
    }
    else {
      resolved.angular = new geometry_msgs.msg.Vector3()
    }

    if (msg.distance_left !== undefined) {
      resolved.distance_left = msg.distance_left;
    }
    else {
      resolved.distance_left = 0.0
    }

    return resolved;
    }
};

module.exports = Twist_inspection;
