// Auto-generated. Do not edit!

// (in-package object_detection.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let GoalPositions = require('../msg/GoalPositions.js');

//-----------------------------------------------------------

class LocalizationRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LocalizationRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LocalizationRequest
    let len;
    let data = new LocalizationRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'object_detection/LocalizationRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LocalizationRequest(null);
    return resolved;
    }
};

class LocalizationResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Coords = null;
    }
    else {
      if (initObj.hasOwnProperty('Coords')) {
        this.Coords = initObj.Coords
      }
      else {
        this.Coords = new GoalPositions();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LocalizationResponse
    // Serialize message field [Coords]
    bufferOffset = GoalPositions.serialize(obj.Coords, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LocalizationResponse
    let len;
    let data = new LocalizationResponse(null);
    // Deserialize message field [Coords]
    data.Coords = GoalPositions.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += GoalPositions.getMessageSize(object.Coords);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'object_detection/LocalizationResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '742db672f1005567be304d1ccc310265';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    GoalPositions Coords
    
    
    ================================================================================
    MSG: object_detection/GoalPositions
    GoalPos[] Coords
    
    ================================================================================
    MSG: object_detection/GoalPos
    float32 X
    float32 Y
    float32 Z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LocalizationResponse(null);
    if (msg.Coords !== undefined) {
      resolved.Coords = GoalPositions.Resolve(msg.Coords)
    }
    else {
      resolved.Coords = new GoalPositions()
    }

    return resolved;
    }
};

module.exports = {
  Request: LocalizationRequest,
  Response: LocalizationResponse,
  md5sum() { return '742db672f1005567be304d1ccc310265'; },
  datatype() { return 'object_detection/Localization'; }
};
