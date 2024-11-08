// Auto-generated. Do not edit!

// (in-package unitree_motor.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Ctrl {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
      this.T = null;
      this.W = null;
      this.Pos = null;
      this.K_P = null;
      this.K_W = null;
    }
    else {
      if (initObj.hasOwnProperty('enable')) {
        this.enable = initObj.enable
      }
      else {
        this.enable = false;
      }
      if (initObj.hasOwnProperty('T')) {
        this.T = initObj.T
      }
      else {
        this.T = 0.0;
      }
      if (initObj.hasOwnProperty('W')) {
        this.W = initObj.W
      }
      else {
        this.W = 0.0;
      }
      if (initObj.hasOwnProperty('Pos')) {
        this.Pos = initObj.Pos
      }
      else {
        this.Pos = 0.0;
      }
      if (initObj.hasOwnProperty('K_P')) {
        this.K_P = initObj.K_P
      }
      else {
        this.K_P = 0.0;
      }
      if (initObj.hasOwnProperty('K_W')) {
        this.K_W = initObj.K_W
      }
      else {
        this.K_W = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Ctrl
    // Serialize message field [enable]
    bufferOffset = _serializer.bool(obj.enable, buffer, bufferOffset);
    // Serialize message field [T]
    bufferOffset = _serializer.float32(obj.T, buffer, bufferOffset);
    // Serialize message field [W]
    bufferOffset = _serializer.float32(obj.W, buffer, bufferOffset);
    // Serialize message field [Pos]
    bufferOffset = _serializer.float32(obj.Pos, buffer, bufferOffset);
    // Serialize message field [K_P]
    bufferOffset = _serializer.float32(obj.K_P, buffer, bufferOffset);
    // Serialize message field [K_W]
    bufferOffset = _serializer.float32(obj.K_W, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Ctrl
    let len;
    let data = new Ctrl(null);
    // Deserialize message field [enable]
    data.enable = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [T]
    data.T = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [W]
    data.W = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Pos]
    data.Pos = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [K_P]
    data.K_P = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [K_W]
    data.K_W = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'unitree_motor/Ctrl';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2c076a68349d15f6ea7b8be4ef49b0a7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool        enable
    float32     T       # Desired output torque of motor【期望电机本身的输出力矩（Nm）】 单位：Nm, T<255.9
    float32     W       # Desired output speed of motor【期望电机本身的速度(rad/s)】 单位：rad/s, W<511.9
    float32     Pos     #单位：rad, Pos<131071.9
    float32     K_P     #K_P<31.9
    float32     K_W     #K_W<63.9
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Ctrl(null);
    if (msg.enable !== undefined) {
      resolved.enable = msg.enable;
    }
    else {
      resolved.enable = false
    }

    if (msg.T !== undefined) {
      resolved.T = msg.T;
    }
    else {
      resolved.T = 0.0
    }

    if (msg.W !== undefined) {
      resolved.W = msg.W;
    }
    else {
      resolved.W = 0.0
    }

    if (msg.Pos !== undefined) {
      resolved.Pos = msg.Pos;
    }
    else {
      resolved.Pos = 0.0
    }

    if (msg.K_P !== undefined) {
      resolved.K_P = msg.K_P;
    }
    else {
      resolved.K_P = 0.0
    }

    if (msg.K_W !== undefined) {
      resolved.K_W = msg.K_W;
    }
    else {
      resolved.K_W = 0.0
    }

    return resolved;
    }
};

module.exports = Ctrl;
