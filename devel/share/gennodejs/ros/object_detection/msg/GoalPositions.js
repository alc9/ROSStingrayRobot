// Auto-generated. Do not edit!

// (in-package object_detection.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let GoalPos = require('./GoalPos.js');

//-----------------------------------------------------------

class GoalPositions {
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
        this.Coords = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GoalPositions
    // Serialize message field [Coords]
    // Serialize the length for message field [Coords]
    bufferOffset = _serializer.uint32(obj.Coords.length, buffer, bufferOffset);
    obj.Coords.forEach((val) => {
      bufferOffset = GoalPos.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GoalPositions
    let len;
    let data = new GoalPositions(null);
    // Deserialize message field [Coords]
    // Deserialize array length for message field [Coords]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.Coords = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.Coords[i] = GoalPos.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 12 * object.Coords.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'object_detection/GoalPositions';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6e1cbfbf293ab70ab330ff223c5f1fcd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new GoalPositions(null);
    if (msg.Coords !== undefined) {
      resolved.Coords = new Array(msg.Coords.length);
      for (let i = 0; i < resolved.Coords.length; ++i) {
        resolved.Coords[i] = GoalPos.Resolve(msg.Coords[i]);
      }
    }
    else {
      resolved.Coords = []
    }

    return resolved;
    }
};

module.exports = GoalPositions;
