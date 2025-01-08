// Auto-generated. Do not edit!

// (in-package control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Command {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mode = null;
      this.force = null;
      this.kp = null;
      this.ki = null;
      this.kd = null;
      this.flag = null;
      this.Tsta = null;
      this.Trise = null;
      this.Tfall = null;
      this.Fmax = null;
      this.measure = null;
    }
    else {
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('force')) {
        this.force = initObj.force
      }
      else {
        this.force = 0.0;
      }
      if (initObj.hasOwnProperty('kp')) {
        this.kp = initObj.kp
      }
      else {
        this.kp = 0.0;
      }
      if (initObj.hasOwnProperty('ki')) {
        this.ki = initObj.ki
      }
      else {
        this.ki = 0.0;
      }
      if (initObj.hasOwnProperty('kd')) {
        this.kd = initObj.kd
      }
      else {
        this.kd = 0.0;
      }
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0;
      }
      if (initObj.hasOwnProperty('Tsta')) {
        this.Tsta = initObj.Tsta
      }
      else {
        this.Tsta = 0.0;
      }
      if (initObj.hasOwnProperty('Trise')) {
        this.Trise = initObj.Trise
      }
      else {
        this.Trise = 0.0;
      }
      if (initObj.hasOwnProperty('Tfall')) {
        this.Tfall = initObj.Tfall
      }
      else {
        this.Tfall = 0.0;
      }
      if (initObj.hasOwnProperty('Fmax')) {
        this.Fmax = initObj.Fmax
      }
      else {
        this.Fmax = 0.0;
      }
      if (initObj.hasOwnProperty('measure')) {
        this.measure = initObj.measure
      }
      else {
        this.measure = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Command
    // Serialize message field [mode]
    bufferOffset = _serializer.int32(obj.mode, buffer, bufferOffset);
    // Serialize message field [force]
    bufferOffset = _serializer.float32(obj.force, buffer, bufferOffset);
    // Serialize message field [kp]
    bufferOffset = _serializer.float32(obj.kp, buffer, bufferOffset);
    // Serialize message field [ki]
    bufferOffset = _serializer.float32(obj.ki, buffer, bufferOffset);
    // Serialize message field [kd]
    bufferOffset = _serializer.float32(obj.kd, buffer, bufferOffset);
    // Serialize message field [flag]
    bufferOffset = _serializer.int32(obj.flag, buffer, bufferOffset);
    // Serialize message field [Tsta]
    bufferOffset = _serializer.float32(obj.Tsta, buffer, bufferOffset);
    // Serialize message field [Trise]
    bufferOffset = _serializer.float32(obj.Trise, buffer, bufferOffset);
    // Serialize message field [Tfall]
    bufferOffset = _serializer.float32(obj.Tfall, buffer, bufferOffset);
    // Serialize message field [Fmax]
    bufferOffset = _serializer.float32(obj.Fmax, buffer, bufferOffset);
    // Serialize message field [measure]
    bufferOffset = _serializer.int32(obj.measure, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Command
    let len;
    let data = new Command(null);
    // Deserialize message field [mode]
    data.mode = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [force]
    data.force = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [kp]
    data.kp = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ki]
    data.ki = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [kd]
    data.kd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [flag]
    data.flag = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [Tsta]
    data.Tsta = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Trise]
    data.Trise = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Tfall]
    data.Tfall = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Fmax]
    data.Fmax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [measure]
    data.measure = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 44;
  }

  static datatype() {
    // Returns string type for a message object
    return 'control/Command';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9b8e94fa3e1923da82a28a1fd42c0d6b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 mode  #mode 1 力位控制 mode 2  速度模式 mode 3 位置模式
    float32 force
    float32 kp    #刚度 N/mm 或 PID的比例
    float32 ki    
    float32 kd   
    int32 flag    #标志触地
    float32 Tsta    #助力开始时刻
    float32 Trise    #助力结束时刻
    float32 Tfall    #助力开始时刻
    float32 Fmax    #助力结束时刻
    int32 measure  #开始测量
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Command(null);
    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.force !== undefined) {
      resolved.force = msg.force;
    }
    else {
      resolved.force = 0.0
    }

    if (msg.kp !== undefined) {
      resolved.kp = msg.kp;
    }
    else {
      resolved.kp = 0.0
    }

    if (msg.ki !== undefined) {
      resolved.ki = msg.ki;
    }
    else {
      resolved.ki = 0.0
    }

    if (msg.kd !== undefined) {
      resolved.kd = msg.kd;
    }
    else {
      resolved.kd = 0.0
    }

    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0
    }

    if (msg.Tsta !== undefined) {
      resolved.Tsta = msg.Tsta;
    }
    else {
      resolved.Tsta = 0.0
    }

    if (msg.Trise !== undefined) {
      resolved.Trise = msg.Trise;
    }
    else {
      resolved.Trise = 0.0
    }

    if (msg.Tfall !== undefined) {
      resolved.Tfall = msg.Tfall;
    }
    else {
      resolved.Tfall = 0.0
    }

    if (msg.Fmax !== undefined) {
      resolved.Fmax = msg.Fmax;
    }
    else {
      resolved.Fmax = 0.0
    }

    if (msg.measure !== undefined) {
      resolved.measure = msg.measure;
    }
    else {
      resolved.measure = 0
    }

    return resolved;
    }
};

module.exports = Command;
