; Auto-generated. Do not edit!


(cl:in-package ground_reaction_force-msg)


;//! \htmlinclude GRF_Data.msg.html

(cl:defclass <GRF_Data> (roslisp-msg-protocol:ros-message)
  ((fore
    :reader fore
    :initarg :fore
    :type cl:float
    :initform 0.0)
   (mid
    :reader mid
    :initarg :mid
    :type cl:float
    :initform 0.0)
   (hind
    :reader hind
    :initarg :hind
    :type cl:float
    :initform 0.0)
   (xcop
    :reader xcop
    :initarg :xcop
    :type cl:float
    :initform 0.0)
   (ycop
    :reader ycop
    :initarg :ycop
    :type cl:float
    :initform 0.0)
   (all_force
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

(cl:defclass GRF_Data (<GRF_Data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GRF_Data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GRF_Data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ground_reaction_force-msg:<GRF_Data> is deprecated: use ground_reaction_force-msg:GRF_Data instead.")))

(cl:ensure-generic-function 'fore-val :lambda-list '(m))
(cl:defmethod fore-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:fore-val is deprecated.  Use ground_reaction_force-msg:fore instead.")
  (fore m))

(cl:ensure-generic-function 'mid-val :lambda-list '(m))
(cl:defmethod mid-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:mid-val is deprecated.  Use ground_reaction_force-msg:mid instead.")
  (mid m))

(cl:ensure-generic-function 'hind-val :lambda-list '(m))
(cl:defmethod hind-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:hind-val is deprecated.  Use ground_reaction_force-msg:hind instead.")
  (hind m))

(cl:ensure-generic-function 'xcop-val :lambda-list '(m))
(cl:defmethod xcop-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:xcop-val is deprecated.  Use ground_reaction_force-msg:xcop instead.")
  (xcop m))

(cl:ensure-generic-function 'ycop-val :lambda-list '(m))
(cl:defmethod ycop-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:ycop-val is deprecated.  Use ground_reaction_force-msg:ycop instead.")
  (ycop m))

(cl:ensure-generic-function 'all_force-val :lambda-list '(m))
(cl:defmethod all_force-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:all_force-val is deprecated.  Use ground_reaction_force-msg:all_force instead.")
  (all_force m))

(cl:ensure-generic-function 'stance_flg-val :lambda-list '(m))
(cl:defmethod stance_flg-val ((m <GRF_Data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ground_reaction_force-msg:stance_flg-val is deprecated.  Use ground_reaction_force-msg:stance_flg instead.")
  (stance_flg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GRF_Data>) ostream)
  "Serializes a message object of type '<GRF_Data>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fore))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mid))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'hind))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xcop))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ycop))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'all_force))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stance_flg) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GRF_Data>) istream)
  "Deserializes a message object of type '<GRF_Data>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fore) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mid) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'hind) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xcop) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ycop) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'all_force) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'stance_flg) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GRF_Data>)))
  "Returns string type for a message object of type '<GRF_Data>"
  "ground_reaction_force/GRF_Data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GRF_Data)))
  "Returns string type for a message object of type 'GRF_Data"
  "ground_reaction_force/GRF_Data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GRF_Data>)))
  "Returns md5sum for a message object of type '<GRF_Data>"
  "e0986bb67ac829a78eeead1a9f8401cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GRF_Data)))
  "Returns md5sum for a message object of type 'GRF_Data"
  "e0986bb67ac829a78eeead1a9f8401cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GRF_Data>)))
  "Returns full string definition for message of type '<GRF_Data>"
  (cl:format cl:nil "float32 fore~%float32 mid~%float32 hind~%float32 xcop~%float32 ycop~%float32 all_force~%bool stance_flg~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GRF_Data)))
  "Returns full string definition for message of type 'GRF_Data"
  (cl:format cl:nil "float32 fore~%float32 mid~%float32 hind~%float32 xcop~%float32 ycop~%float32 all_force~%bool stance_flg~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GRF_Data>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GRF_Data>))
  "Converts a ROS message object to a list"
  (cl:list 'GRF_Data
    (cl:cons ':fore (fore msg))
    (cl:cons ':mid (mid msg))
    (cl:cons ':hind (hind msg))
    (cl:cons ':xcop (xcop msg))
    (cl:cons ':ycop (ycop msg))
    (cl:cons ':all_force (all_force msg))
    (cl:cons ':stance_flg (stance_flg msg))
))
