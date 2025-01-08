; Auto-generated. Do not edit!


(cl:in-package unitree_motor-msg)


;//! \htmlinclude Sensor.msg.html

(cl:defclass <Sensor> (roslisp-msg-protocol:ros-message)
  ((motor_id
    :reader motor_id
    :initarg :motor_id
    :type cl:integer
    :initform 0)
   (T
    :reader T
    :initarg :T
    :type cl:float
    :initform 0.0)
   (Pos
    :reader Pos
    :initarg :Pos
    :type cl:float
    :initform 0.0)
   (Temp
    :reader Temp
    :initarg :Temp
    :type cl:float
    :initform 0.0))
)

(cl:defclass Sensor (<Sensor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Sensor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Sensor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name unitree_motor-msg:<Sensor> is deprecated: use unitree_motor-msg:Sensor instead.")))

(cl:ensure-generic-function 'motor_id-val :lambda-list '(m))
(cl:defmethod motor_id-val ((m <Sensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:motor_id-val is deprecated.  Use unitree_motor-msg:motor_id instead.")
  (motor_id m))

(cl:ensure-generic-function 'T-val :lambda-list '(m))
(cl:defmethod T-val ((m <Sensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:T-val is deprecated.  Use unitree_motor-msg:T instead.")
  (T m))

(cl:ensure-generic-function 'Pos-val :lambda-list '(m))
(cl:defmethod Pos-val ((m <Sensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:Pos-val is deprecated.  Use unitree_motor-msg:Pos instead.")
  (Pos m))

(cl:ensure-generic-function 'Temp-val :lambda-list '(m))
(cl:defmethod Temp-val ((m <Sensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:Temp-val is deprecated.  Use unitree_motor-msg:Temp instead.")
  (Temp m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Sensor>) ostream)
  "Serializes a message object of type '<Sensor>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'T))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Temp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Sensor>) istream)
  "Deserializes a message object of type '<Sensor>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'T) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Pos) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Temp) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Sensor>)))
  "Returns string type for a message object of type '<Sensor>"
  "unitree_motor/Sensor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Sensor)))
  "Returns string type for a message object of type 'Sensor"
  "unitree_motor/Sensor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Sensor>)))
  "Returns md5sum for a message object of type '<Sensor>"
  "beee0c2c439c8763e3016584e8002537")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Sensor)))
  "Returns md5sum for a message object of type 'Sensor"
  "beee0c2c439c8763e3016584e8002537")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Sensor>)))
  "Returns full string definition for message of type '<Sensor>"
  (cl:format cl:nil "char        motor_id    #Motor ID【电机ID】~%float32     T           #The output torque of motor【当前实际电机输出力矩】~%float32     Pos         #The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】~%float32     Temp         # 温度~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Sensor)))
  "Returns full string definition for message of type 'Sensor"
  (cl:format cl:nil "char        motor_id    #Motor ID【电机ID】~%float32     T           #The output torque of motor【当前实际电机输出力矩】~%float32     Pos         #The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】~%float32     Temp         # 温度~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Sensor>))
  (cl:+ 0
     1
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Sensor>))
  "Converts a ROS message object to a list"
  (cl:list 'Sensor
    (cl:cons ':motor_id (motor_id msg))
    (cl:cons ':T (T msg))
    (cl:cons ':Pos (Pos msg))
    (cl:cons ':Temp (Temp msg))
))
