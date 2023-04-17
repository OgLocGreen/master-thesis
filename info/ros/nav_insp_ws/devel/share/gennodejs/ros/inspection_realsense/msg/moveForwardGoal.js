// Auto-generated. Do not edit!

// (in-package inspection_realsense.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class moveForwardGoal {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vel = null;
      this.n_pasadas_ant = null;
      this.n_imgs_ant = null;
    }
    else {
      if (initObj.hasOwnProperty('vel')) {
        this.vel = initObj.vel
      }
      else {
        this.vel = 0.0;
      }
      if (initObj.hasOwnProperty('n_pasadas_ant')) {
        this.n_pasadas_ant = initObj.n_pasadas_ant
      }
      else {
        this.n_pasadas_ant = 0;
      }
      if (initObj.hasOwnProperty('n_imgs_ant')) {
        this.n_imgs_ant = initObj.n_imgs_ant
      }
      else {
        this.n_imgs_ant = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type moveForwardGoal
    // Serialize message field [vel]
    bufferOffset = _serializer.float32(obj.vel, buffer, bufferOffset);
    // Serialize message field [n_pasadas_ant]
    bufferOffset = _serializer.int32(obj.n_pasadas_ant, buffer, bufferOffset);
    // Serialize message field [n_imgs_ant]
    bufferOffset = _serializer.int32(obj.n_imgs_ant, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type moveForwardGoal
    let len;
    let data = new moveForwardGoal(null);
    // Deserialize message field [vel]
    data.vel = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [n_pasadas_ant]
    data.n_pasadas_ant = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [n_imgs_ant]
    data.n_imgs_ant = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'inspection_realsense/moveForwardGoal';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '26095be20a715ca0a2049a176afb9bed';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    #goal definition
    float32 vel
    int32 n_pasadas_ant
    int32 n_imgs_ant
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new moveForwardGoal(null);
    if (msg.vel !== undefined) {
      resolved.vel = msg.vel;
    }
    else {
      resolved.vel = 0.0
    }

    if (msg.n_pasadas_ant !== undefined) {
      resolved.n_pasadas_ant = msg.n_pasadas_ant;
    }
    else {
      resolved.n_pasadas_ant = 0
    }

    if (msg.n_imgs_ant !== undefined) {
      resolved.n_imgs_ant = msg.n_imgs_ant;
    }
    else {
      resolved.n_imgs_ant = 0
    }

    return resolved;
    }
};

module.exports = moveForwardGoal;
