; Auto-generated. Do not edit!


(cl:in-package strategy_test-msg)


;//! \htmlinclude Fgrf.msg.html

(cl:defclass <Fgrf> (roslisp-msg-protocol:ros-message)
  ((all_force
    :reader all_force
    :initarg :all_force
    :type cl:float
    :initform 0.0)
   (stance_flg
    :reader stance_flg
    :initarg :stance_flg
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Fgrf (<Fgrf>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Fgrf>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Fgrf)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name strategy_test-msg:<Fgrf> is deprecated: use strategy_test-msg:Fgrf instead.")))

(cl:ensure-generic-function 'all_force-val :lambda-list '(m))
(cl:defmethod all_force-val ((m <Fgrf>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader strategy_test-msg:all_force-val is deprecated.  Use strategy_test-msg:all_force instead.")
  (all_force m))

(cl:ensure-generic-function 'stance_flg-val :lambda-list '(m))
(cl:defmethod stance_flg-val ((m <Fgrf>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader strategy_test-msg:stance_flg-val is deprecated.  Use strategy_test-msg:stance_flg instead.")
  (stance_flg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Fgrf>) ostream)
  "Serializes a message object of type '<Fgrf>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'all_force))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stance_flg) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Fgrf>) istream)
  "Deserializes a message object of type '<Fgrf>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'all_force) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'stance_flg) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Fgrf>)))
  "Returns string type for a message object of type '<Fgrf>"
  "strategy_test/Fgrf")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Fgrf)))
  "Returns string type for a message object of type 'Fgrf"
  "strategy_test/Fgrf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Fgrf>)))
  "Returns md5sum for a message object of type '<Fgrf>"
  "c3590a53ab517e32293f777e708cbb60")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Fgrf)))
  "Returns md5sum for a message object of type 'Fgrf"
  "c3590a53ab517e32293f777e708cbb60")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Fgrf>)))
  "Returns full string definition for message of type '<Fgrf>"
  (cl:format cl:nil "float32 all_force~%bool stance_flg~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Fgrf)))
  "Returns full string definition for message of type 'Fgrf"
  (cl:format cl:nil "float32 all_force~%bool stance_flg~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Fgrf>))
  (cl:+ 0
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Fgrf>))
  "Converts a ROS message object to a list"
  (cl:list 'Fgrf
    (cl:cons ':all_force (all_force msg))
    (cl:cons ':stance_flg (stance_flg msg))
))
