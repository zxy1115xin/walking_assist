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

class Sensor {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motor_id = null;
      this.T = null;
      this.Pos = null;
      this.Temp = null;
    }
    else {
      if (initObj.hasOwnProperty('motor_id')) {
        this.motor_id = initObj.motor_id
      }
      else {
        this.motor_id = 0;
      }
      if (initObj.hasOwnProperty('T')) {
        this.T = initObj.T
      }
      else {
        this.T = 0.0;
      }
      if (initObj.hasOwnProperty('Pos')) {
        this.Pos = initObj.Pos
      }
      else {
        this.Pos = 0.0;
      }
      if (initObj.hasOwnProperty('Temp')) {
        this.Temp = initObj.Temp
      }
      else {
        this.Temp = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Sensor
    // Serialize message field [motor_id]
    bufferOffset = _serializer.char(obj.motor_id, buffer, bufferOffset);
    // Serialize message field [T]
    bufferOffset = _serializer.float32(obj.T, buffer, bufferOffset);
    // Serialize message field [Pos]
    bufferOffset = _serializer.float32(obj.Pos, buffer, bufferOffset);
    // Serialize message field [Temp]
    bufferOffset = _serializer.float32(obj.Temp, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Sensor
    let len;
    let data = new Sensor(null);
    // Deserialize message field [motor_id]
    data.motor_id = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [T]
    data.T = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Pos]
    data.Pos = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Temp]
    data.Temp = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'unitree_motor/Sensor';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'beee0c2c439c8763e3016584e8002537';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    char        motor_id    #Motor ID【电机ID】
    float32     T           #The output torque of motor【当前实际电机输出力矩】
    float32     Pos         #The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】
    float32     Temp         # 温度
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Sensor(null);
    if (msg.motor_id !== undefined) {
      resolved.motor_id = msg.motor_id;
    }
    else {
      resolved.motor_id = 0
    }

    if (msg.T !== undefined) {
      resolved.T = msg.T;
    }
    else {
      resolved.T = 0.0
    }

    if (msg.Pos !== undefined) {
      resolved.Pos = msg.Pos;
    }
    else {
      resolved.Pos = 0.0
    }

    if (msg.Temp !== undefined) {
      resolved.Temp = msg.Temp;
    }
    else {
      resolved.Temp = 0.0
    }

    return resolved;
    }
};

module.exports = Sensor;
