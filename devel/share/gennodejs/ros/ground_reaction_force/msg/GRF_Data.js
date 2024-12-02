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
      this.fore = null;
      this.mid = null;
      this.hind = null;
      this.xcop = null;
      this.ycop = null;
      this.all_force = null;
      this.stance_flg = null;
    }
    else {
      if (initObj.hasOwnProperty('fore')) {
        this.fore = initObj.fore
      }
      else {
        this.fore = 0.0;
      }
      if (initObj.hasOwnProperty('mid')) {
        this.mid = initObj.mid
      }
      else {
        this.mid = 0.0;
      }
      if (initObj.hasOwnProperty('hind')) {
        this.hind = initObj.hind
      }
      else {
        this.hind = 0.0;
      }
      if (initObj.hasOwnProperty('xcop')) {
        this.xcop = initObj.xcop
      }
      else {
        this.xcop = 0.0;
      }
      if (initObj.hasOwnProperty('ycop')) {
        this.ycop = initObj.ycop
      }
      else {
        this.ycop = 0.0;
      }
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
    // Serializes a message object of type GRF_Data
    // Serialize message field [fore]
    bufferOffset = _serializer.float32(obj.fore, buffer, bufferOffset);
    // Serialize message field [mid]
    bufferOffset = _serializer.float32(obj.mid, buffer, bufferOffset);
    // Serialize message field [hind]
    bufferOffset = _serializer.float32(obj.hind, buffer, bufferOffset);
    // Serialize message field [xcop]
    bufferOffset = _serializer.float32(obj.xcop, buffer, bufferOffset);
    // Serialize message field [ycop]
    bufferOffset = _serializer.float32(obj.ycop, buffer, bufferOffset);
    // Serialize message field [all_force]
    bufferOffset = _serializer.float32(obj.all_force, buffer, bufferOffset);
    // Serialize message field [stance_flg]
    bufferOffset = _serializer.bool(obj.stance_flg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GRF_Data
    let len;
    let data = new GRF_Data(null);
    // Deserialize message field [fore]
    data.fore = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [mid]
    data.mid = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [hind]
    data.hind = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [xcop]
    data.xcop = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ycop]
    data.ycop = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [all_force]
    data.all_force = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [stance_flg]
    data.stance_flg = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 25;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ground_reaction_force/GRF_Data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e0986bb67ac829a78eeead1a9f8401cb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 fore
    float32 mid
    float32 hind
    float32 xcop
    float32 ycop
    float32 all_force
    bool stance_flg
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GRF_Data(null);
    if (msg.fore !== undefined) {
      resolved.fore = msg.fore;
    }
    else {
      resolved.fore = 0.0
    }

    if (msg.mid !== undefined) {
      resolved.mid = msg.mid;
    }
    else {
      resolved.mid = 0.0
    }

    if (msg.hind !== undefined) {
      resolved.hind = msg.hind;
    }
    else {
      resolved.hind = 0.0
    }

    if (msg.xcop !== undefined) {
      resolved.xcop = msg.xcop;
    }
    else {
      resolved.xcop = 0.0
    }

    if (msg.ycop !== undefined) {
      resolved.ycop = msg.ycop;
    }
    else {
      resolved.ycop = 0.0
    }

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

module.exports = GRF_Data;
