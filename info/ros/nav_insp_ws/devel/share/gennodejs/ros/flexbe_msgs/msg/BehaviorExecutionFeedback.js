// Auto-generated. Do not edit!

// (in-package flexbe_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class BehaviorExecutionFeedback {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.current_state = null;
    }
    else {
      if (initObj.hasOwnProperty('current_state')) {
        this.current_state = initObj.current_state
      }
      else {
        this.current_state = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BehaviorExecutionFeedback
    // Serialize message field [current_state]
    bufferOffset = _serializer.string(obj.current_state, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BehaviorExecutionFeedback
    let len;
    let data = new BehaviorExecutionFeedback(null);
    // Deserialize message field [current_state]
    data.current_state = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.current_state.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'flexbe_msgs/BehaviorExecutionFeedback';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6b3c1b68b57cc9263bf79fc4ad6ec8c7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    
    # path of the current state
    string current_state
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BehaviorExecutionFeedback(null);
    if (msg.current_state !== undefined) {
      resolved.current_state = msg.current_state;
    }
    else {
      resolved.current_state = ''
    }

    return resolved;
    }
};

module.exports = BehaviorExecutionFeedback;