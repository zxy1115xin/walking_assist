// Auto-generated. Do not edit!

// (in-package strategy_test.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Fgrf {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.all_force = null;
      this.stance_flg = null;
    }
    else {
      if (initObj.hasOwnProperty('all_force')) {
        this.all_force = initObj.all_force
      }
      else {
        this.all_force = 0.0;
      }
      if (initObj.hasOwnProperty('stance_flg')) {
        this.stance_flg = initObj.stance_flg
      }
      else {
        this.stance_flg = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Fgrf
    // Serialize message field [all_force]
    bufferOffset = _serializer.float32(obj.all_force, buffer, bufferOffset);
    // Serialize message field [stance_flg]
    bufferOffset = _serializer.bool(obj.stance_flg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Fgrf
    let len;
    let data = new Fgrf(null);
    // Deserialize message field [all_force]
    data.all_force = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [stance_flg]
    data.stance_flg = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'strategy_test/Fgrf';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c3590a53ab517e32293f777e708cbb60';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 all_force
    bool stance_flg
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Fgrf(null);
    if (msg.all_force !== undefined) {
      resolved.all_force = msg.all_force;
    }
    else {
      resolved.all_force = 0.0
    }

    if (msg.stance_flg !== undefined) {
      resolved.stance_flg = msg.stance_flg;
    }
    else {
      resolved.stance_flg = false
    }

    return resolved;
    }
};

module.exports = Fgrf;
