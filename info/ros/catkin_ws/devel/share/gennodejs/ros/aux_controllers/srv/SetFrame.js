// Auto-generated. Do not edit!

// (in-package aux_controllers.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetFrameRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ini = null;
      this.origin_x = null;
      this.origin_y = null;
      this.origin_z = null;
      this.rotation_roll = null;
      this.rotation_pitch = null;
      this.rotation_yaw = null;
    }
    else {
      if (initObj.hasOwnProperty('ini')) {
        this.ini = initObj.ini
      }
      else {
        this.ini = false;
      }
      if (initObj.hasOwnProperty('origin_x')) {
        this.origin_x = initObj.origin_x
      }
      else {
        this.origin_x = 0.0;
      }
      if (initObj.hasOwnProperty('origin_y')) {
        this.origin_y = initObj.origin_y
      }
      else {
        this.origin_y = 0.0;
      }
      if (initObj.hasOwnProperty('origin_z')) {
        this.origin_z = initObj.origin_z
      }
      else {
        this.origin_z = 0.0;
      }
      if (initObj.hasOwnProperty('rotation_roll')) {
        this.rotation_roll = initObj.rotation_roll
      }
      else {
        this.rotation_roll = 0.0;
      }
      if (initObj.hasOwnProperty('rotation_pitch')) {
        this.rotation_pitch = initObj.rotation_pitch
      }
      else {
        this.rotation_pitch = 0.0;
      }
      if (initObj.hasOwnProperty('rotation_yaw')) {
        this.rotation_yaw = initObj.rotation_yaw
      }
      else {
        this.rotation_yaw = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetFrameRequest
    // Serialize message field [ini]
    bufferOffset = _serializer.bool(obj.ini, buffer, bufferOffset);
    // Serialize message field [origin_x]
    bufferOffset = _serializer.float32(obj.origin_x, buffer, bufferOffset);
    // Serialize message field [origin_y]
    bufferOffset = _serializer.float32(obj.origin_y, buffer, bufferOffset);
    // Serialize message field [origin_z]
    bufferOffset = _serializer.float32(obj.origin_z, buffer, bufferOffset);
    // Serialize message field [rotation_roll]
    bufferOffset = _serializer.float32(obj.rotation_roll, buffer, bufferOffset);
    // Serialize message field [rotation_pitch]
    bufferOffset = _serializer.float32(obj.rotation_pitch, buffer, bufferOffset);
    // Serialize message field [rotation_yaw]
    bufferOffset = _serializer.float32(obj.rotation_yaw, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetFrameRequest
    let len;
    let data = new SetFrameRequest(null);
    // Deserialize message field [ini]
    data.ini = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [origin_x]
    data.origin_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [origin_y]
    data.origin_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [origin_z]
    data.origin_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rotation_roll]
    data.rotation_roll = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rotation_pitch]
    data.rotation_pitch = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rotation_yaw]
    data.rotation_yaw = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 25;
  }

  static datatype() {
    // Returns string type for a service object
    return 'aux_controllers/SetFrameRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd774e3446069c0f841b542eafae6a351';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool ini
    
    float32 origin_x
    float32 origin_y
    float32 origin_z
    
    float32 rotation_roll
    float32 rotation_pitch
    float32 rotation_yaw
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetFrameRequest(null);
    if (msg.ini !== undefined) {
      resolved.ini = msg.ini;
    }
    else {
      resolved.ini = false
    }

    if (msg.origin_x !== undefined) {
      resolved.origin_x = msg.origin_x;
    }
    else {
      resolved.origin_x = 0.0
    }

    if (msg.origin_y !== undefined) {
      resolved.origin_y = msg.origin_y;
    }
    else {
      resolved.origin_y = 0.0
    }

    if (msg.origin_z !== undefined) {
      resolved.origin_z = msg.origin_z;
    }
    else {
      resolved.origin_z = 0.0
    }

    if (msg.rotation_roll !== undefined) {
      resolved.rotation_roll = msg.rotation_roll;
    }
    else {
      resolved.rotation_roll = 0.0
    }

    if (msg.rotation_pitch !== undefined) {
      resolved.rotation_pitch = msg.rotation_pitch;
    }
    else {
      resolved.rotation_pitch = 0.0
    }

    if (msg.rotation_yaw !== undefined) {
      resolved.rotation_yaw = msg.rotation_yaw;
    }
    else {
      resolved.rotation_yaw = 0.0
    }

    return resolved;
    }
};

class SetFrameResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.respond = null;
    }
    else {
      if (initObj.hasOwnProperty('respond')) {
        this.respond = initObj.respond
      }
      else {
        this.respond = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetFrameResponse
    // Serialize message field [respond]
    bufferOffset = _serializer.bool(obj.respond, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetFrameResponse
    let len;
    let data = new SetFrameResponse(null);
    // Deserialize message field [respond]
    data.respond = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'aux_controllers/SetFrameResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f386576e317fabd22f70a14e46dc82ae';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool respond
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetFrameResponse(null);
    if (msg.respond !== undefined) {
      resolved.respond = msg.respond;
    }
    else {
      resolved.respond = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SetFrameRequest,
  Response: SetFrameResponse,
  md5sum() { return 'fc7b3836a679f38a5c6b9328b643f1e8'; },
  datatype() { return 'aux_controllers/SetFrame'; }
};
