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

class ChapaStorageRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id_chapa = null;
    }
    else {
      if (initObj.hasOwnProperty('id_chapa')) {
        this.id_chapa = initObj.id_chapa
      }
      else {
        this.id_chapa = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ChapaStorageRequest
    // Serialize message field [id_chapa]
    bufferOffset = _serializer.int32(obj.id_chapa, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ChapaStorageRequest
    let len;
    let data = new ChapaStorageRequest(null);
    // Deserialize message field [id_chapa]
    data.id_chapa = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'action_server_package/ChapaStorageRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '747a0498f8850f71ea5801b4c738596f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 id_chapa
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ChapaStorageRequest(null);
    if (msg.id_chapa !== undefined) {
      resolved.id_chapa = msg.id_chapa;
    }
    else {
      resolved.id_chapa = 0
    }

    return resolved;
    }
};

class ChapaStorageResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.long_chapa = null;
      this.width_chapa = null;
      this.coordA = null;
      this.coordB = null;
      this.coordC = null;
      this.coordD = null;
      this.number_of_chapas = null;
    }
    else {
      if (initObj.hasOwnProperty('long_chapa')) {
        this.long_chapa = initObj.long_chapa
      }
      else {
        this.long_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('width_chapa')) {
        this.width_chapa = initObj.width_chapa
      }
      else {
        this.width_chapa = 0.0;
      }
      if (initObj.hasOwnProperty('coordA')) {
        this.coordA = initObj.coordA
      }
      else {
        this.coordA = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('coordB')) {
        this.coordB = initObj.coordB
      }
      else {
        this.coordB = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('coordC')) {
        this.coordC = initObj.coordC
      }
      else {
        this.coordC = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('coordD')) {
        this.coordD = initObj.coordD
      }
      else {
        this.coordD = new geometry_msgs.msg.Point();
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
    // Serializes a message object of type ChapaStorageResponse
    // Serialize message field [long_chapa]
    bufferOffset = _serializer.float32(obj.long_chapa, buffer, bufferOffset);
    // Serialize message field [width_chapa]
    bufferOffset = _serializer.float32(obj.width_chapa, buffer, bufferOffset);
    // Serialize message field [coordA]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.coordA, buffer, bufferOffset);
    // Serialize message field [coordB]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.coordB, buffer, bufferOffset);
    // Serialize message field [coordC]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.coordC, buffer, bufferOffset);
    // Serialize message field [coordD]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.coordD, buffer, bufferOffset);
    // Serialize message field [number_of_chapas]
    bufferOffset = _serializer.int32(obj.number_of_chapas, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ChapaStorageResponse
    let len;
    let data = new ChapaStorageResponse(null);
    // Deserialize message field [long_chapa]
    data.long_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [width_chapa]
    data.width_chapa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coordA]
    data.coordA = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [coordB]
    data.coordB = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [coordC]
    data.coordC = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [coordD]
    data.coordD = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [number_of_chapas]
    data.number_of_chapas = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 108;
  }

  static datatype() {
    // Returns string type for a service object
    return 'action_server_package/ChapaStorageResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5aae4cddd2d81a64c074397519c7dd87';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 long_chapa
    float32 width_chapa
    
    geometry_msgs/Point coordA
    geometry_msgs/Point coordB
    geometry_msgs/Point coordC
    geometry_msgs/Point coordD
    
    int32 number_of_chapas
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
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
    const resolved = new ChapaStorageResponse(null);
    if (msg.long_chapa !== undefined) {
      resolved.long_chapa = msg.long_chapa;
    }
    else {
      resolved.long_chapa = 0.0
    }

    if (msg.width_chapa !== undefined) {
      resolved.width_chapa = msg.width_chapa;
    }
    else {
      resolved.width_chapa = 0.0
    }

    if (msg.coordA !== undefined) {
      resolved.coordA = geometry_msgs.msg.Point.Resolve(msg.coordA)
    }
    else {
      resolved.coordA = new geometry_msgs.msg.Point()
    }

    if (msg.coordB !== undefined) {
      resolved.coordB = geometry_msgs.msg.Point.Resolve(msg.coordB)
    }
    else {
      resolved.coordB = new geometry_msgs.msg.Point()
    }

    if (msg.coordC !== undefined) {
      resolved.coordC = geometry_msgs.msg.Point.Resolve(msg.coordC)
    }
    else {
      resolved.coordC = new geometry_msgs.msg.Point()
    }

    if (msg.coordD !== undefined) {
      resolved.coordD = geometry_msgs.msg.Point.Resolve(msg.coordD)
    }
    else {
      resolved.coordD = new geometry_msgs.msg.Point()
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
  Request: ChapaStorageRequest,
  Response: ChapaStorageResponse,
  md5sum() { return 'd420ea154534426ff59c21556a0bdbf4'; },
  datatype() { return 'action_server_package/ChapaStorage'; }
};
