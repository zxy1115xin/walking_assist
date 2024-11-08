; Auto-generated. Do not edit!


(cl:in-package unitree_motor-msg)


;//! \htmlinclude Ctrl.msg.html

(cl:defclass <Ctrl> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:boolean
    :initform cl:nil)
   (T
    :reader T
    :initarg :T
    :type cl:float
    :initform 0.0)
   (W
    :reader W
    :initarg :W
    :type cl:float
    :initform 0.0)
   (Pos
    :reader Pos
    :initarg :Pos
    :type cl:float
    :initform 0.0)
   (K_P
    :reader K_P
    :initarg :K_P
    :type cl:float
    :initform 0.0)
   (K_W
    :reader K_W
    :initarg :K_W
    :type cl:float
    :initform 0.0))
)

(cl:defclass Ctrl (<Ctrl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Ctrl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Ctrl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name unitree_motor-msg:<Ctrl> is deprecated: use unitree_motor-msg:Ctrl instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:enable-val is deprecated.  Use unitree_motor-msg:enable instead.")
  (enable m))

(cl:ensure-generic-function 'T-val :lambda-list '(m))
(cl:defmethod T-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:T-val is deprecated.  Use unitree_motor-msg:T instead.")
  (T m))

(cl:ensure-generic-function 'W-val :lambda-list '(m))
(cl:defmethod W-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:W-val is deprecated.  Use unitree_motor-msg:W instead.")
  (W m))

(cl:ensure-generic-function 'Pos-val :lambda-list '(m))
(cl:defmethod Pos-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:Pos-val is deprecated.  Use unitree_motor-msg:Pos instead.")
  (Pos m))

(cl:ensure-generic-function 'K_P-val :lambda-list '(m))
(cl:defmethod K_P-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:K_P-val is deprecated.  Use unitree_motor-msg:K_P instead.")
  (K_P m))

(cl:ensure-generic-function 'K_W-val :lambda-list '(m))
(cl:defmethod K_W-val ((m <Ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader unitree_motor-msg:K_W-val is deprecated.  Use unitree_motor-msg:K_W instead.")
  (K_W m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Ctrl>) ostream)
  "Serializes a message object of type '<Ctrl>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'enable) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'T))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'K_P))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'K_W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Ctrl>) istream)
  "Deserializes a message object of type '<Ctrl>"
    (cl:setf (cl:slot-value msg 'enable) (cl:not (cl:zerop (cl:read-byte istream))))
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
    (cl:setf (cl:slot-value msg 'W) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'K_P) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'K_W) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Ctrl>)))
  "Returns string type for a message object of type '<Ctrl>"
  "unitree_motor/Ctrl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Ctrl)))
  "Returns string type for a message object of type 'Ctrl"
  "unitree_motor/Ctrl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Ctrl>)))
  "Returns md5sum for a message object of type '<Ctrl>"
  "2c076a68349d15f6ea7b8be4ef49b0a7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Ctrl)))
  "Returns md5sum for a message object of type 'Ctrl"
  "2c076a68349d15f6ea7b8be4ef49b0a7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Ctrl>)))
  "Returns full string definition for message of type '<Ctrl>"
  (cl:format cl:nil "bool        enable~%float32     T       # Desired output torque of motor【期望电机本身的输出力矩（Nm）】 单位：Nm, T<255.9~%float32     W       # Desired output speed of motor【期望电机本身的速度(rad/s)】 单位：rad/s, W<511.9~%float32     Pos     #单位：rad, Pos<131071.9~%float32     K_P     #K_P<31.9~%float32     K_W     #K_W<63.9~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Ctrl)))
  "Returns full string definition for message of type 'Ctrl"
  (cl:format cl:nil "bool        enable~%float32     T       # Desired output torque of motor【期望电机本身的输出力矩（Nm）】 单位：Nm, T<255.9~%float32     W       # Desired output speed of motor【期望电机本身的速度(rad/s)】 单位：rad/s, W<511.9~%float32     Pos     #单位：rad, Pos<131071.9~%float32     K_P     #K_P<31.9~%float32     K_W     #K_W<63.9~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Ctrl>))
  (cl:+ 0
     1
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Ctrl>))
  "Converts a ROS message object to a list"
  (cl:list 'Ctrl
    (cl:cons ':enable (enable msg))
    (cl:cons ':T (T msg))
    (cl:cons ':W (W msg))
    (cl:cons ':Pos (Pos msg))
    (cl:cons ':K_P (K_P msg))
    (cl:cons ':K_W (K_W msg))
))
