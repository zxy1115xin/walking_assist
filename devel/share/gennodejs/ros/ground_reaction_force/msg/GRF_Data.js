// Auto-generated. Do not edit!

// (in-package ground_reaction_force.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class GRF_Data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.midtop_mid = null;
      this.all_force = null;
      this.bot_Med = null;
      this.bot_lat = null;
      this.stance_flg = null;
    }
    else {
      if (initObj.hasOwnProperty('midtop_mid')) {
        this.midtop_mid = initObj.midtop_mid
      }
      else {
        this.midtop_mid = 0.0;
      }
      if (initObj.hasOwnProperty('all_force')) {
        this.all_force = initObj.all_force
      }
      else {
        this.all_force = 0.0;
      }
      if (initObj.hasOwnProperty('bot_Med')) {
        this.bot_Med = initObj.bot_Med
      }
      else {
        this.bot_Med = 0.0;
      }
      if (initObj.hasOwnProperty('bot_lat')) {
        this.bot_lat = initObj.bot_lat
      }
      else {
        this.bot_lat = 0.0;
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
    // Serializes a message object of type GRF_Data
    // Serialize message field [midtop_mid]
    bufferOffset = _serializer.float32(obj.midtop_mid, buffer, bufferOffset);
    // Serialize message field [all_force]
    bufferOffset = _serializer.float32(obj.all_force, buffer, bufferOffset);
    // Serialize message field [bot_Med]
    bufferOffset = _serializer.float32(obj.bot_Med, buffer, bufferOffset);
    // Serialize message field [bot_lat]
    bufferOffset = _serializer.float32(obj.bot_lat, buffer, bufferOffset);
    // Serialize message field [stance_flg]
    bufferOffset = _serializer.bool(obj.stance_flg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GRF_Data
    let len;
    let data = new GRF_Data(null);
    // Deserialize message field [midtop_mid]
    data.midtop_mid = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [all_force]
    data.all_force = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bot_Med]
    data.bot_Med = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bot_lat]
    data.bot_lat = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [stance_flg]
    data.stance_flg = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 17;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ground_reaction_force/GRF_Data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7f6bc012a85df06ce5797caa5e247628';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 midtop_mid
    float32 all_force
    float32 bot_Med
    float32 bot_lat
    bool stance_flg
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GRF_Data(null);
    if (msg.midtop_mid !== undefined) {
      resolved.midtop_mid = msg.midtop_mid;
    }
    else {
      resolved.midtop_mid = 0.0
    }

    if (msg.all_force !== undefined) {
      resolved.all_force = msg.all_force;
    }
    else {
      resolved.all_force = 0.0
    }

    if (msg.bot_Med !== undefined) {
      resolved.bot_Med = msg.bot_Med;
    }
    else {
      resolved.bot_Med = 0.0
    }

    if (msg.bot_lat !== undefined) {
      resolved.bot_lat = msg.bot_lat;
    }
    else {
      resolved.bot_lat = 0.0
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

module.exports = GRF_Data;
