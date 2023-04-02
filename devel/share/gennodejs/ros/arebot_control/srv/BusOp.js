// Auto-generated. Do not edit!

// (in-package arebot_control.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class BusOpRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.bus_id = null;
      this.recv_len = null;
      this.data = null;
    }
    else {
      if (initObj.hasOwnProperty('bus_id')) {
        this.bus_id = initObj.bus_id
      }
      else {
        this.bus_id = 0;
      }
      if (initObj.hasOwnProperty('recv_len')) {
        this.recv_len = initObj.recv_len
      }
      else {
        this.recv_len = 0;
      }
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BusOpRequest
    // Serialize message field [bus_id]
    bufferOffset = _serializer.uint8(obj.bus_id, buffer, bufferOffset);
    // Serialize message field [recv_len]
    bufferOffset = _serializer.uint8(obj.recv_len, buffer, bufferOffset);
    // Serialize message field [data]
    bufferOffset = _arraySerializer.uint8(obj.data, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BusOpRequest
    let len;
    let data = new BusOpRequest(null);
    // Deserialize message field [bus_id]
    data.bus_id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [recv_len]
    data.recv_len = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [data]
    data.data = _arrayDeserializer.uint8(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.data.length;
    return length + 6;
  }

  static datatype() {
    // Returns string type for a service object
    return 'arebot_control/BusOpRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fda2775269fdf0be82c797ced44c6ef9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 bus_id
    uint8 recv_len
    uint8[] data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BusOpRequest(null);
    if (msg.bus_id !== undefined) {
      resolved.bus_id = msg.bus_id;
    }
    else {
      resolved.bus_id = 0
    }

    if (msg.recv_len !== undefined) {
      resolved.recv_len = msg.recv_len;
    }
    else {
      resolved.recv_len = 0
    }

    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = []
    }

    return resolved;
    }
};

class BusOpResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.data = null;
    }
    else {
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BusOpResponse
    // Serialize message field [data]
    bufferOffset = _arraySerializer.uint8(obj.data, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BusOpResponse
    let len;
    let data = new BusOpResponse(null);
    // Deserialize message field [data]
    data.data = _arrayDeserializer.uint8(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.data.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'arebot_control/BusOpResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f43a8e1b362b75baa741461b46adc7e0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8[] data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BusOpResponse(null);
    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = []
    }

    return resolved;
    }
};

module.exports = {
  Request: BusOpRequest,
  Response: BusOpResponse,
  md5sum() { return 'f42be7da85859f0e278c64aea47889c1'; },
  datatype() { return 'arebot_control/BusOp'; }
};
