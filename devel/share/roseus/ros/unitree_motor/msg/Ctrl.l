;; Auto-generated. Do not edit!


(when (boundp 'unitree_motor::Ctrl)
  (if (not (find-package "UNITREE_MOTOR"))
    (make-package "UNITREE_MOTOR"))
  (shadow 'Ctrl (find-package "UNITREE_MOTOR")))
(unless (find-package "UNITREE_MOTOR::CTRL")
  (make-package "UNITREE_MOTOR::CTRL"))

(in-package "ROS")
;;//! \htmlinclude Ctrl.msg.html


(defclass unitree_motor::Ctrl
  :super ros::object
  :slots (_enable _T _W _Pos _K_P _K_W ))

(defmethod unitree_motor::Ctrl
  (:init
   (&key
    ((:enable __enable) nil)
    ((:T __T) 0.0)
    ((:W __W) 0.0)
    ((:Pos __Pos) 0.0)
    ((:K_P __K_P) 0.0)
    ((:K_W __K_W) 0.0)
    )
   (send-super :init)
   (setq _enable __enable)
   (setq _T (float __T))
   (setq _W (float __W))
   (setq _Pos (float __Pos))
   (setq _K_P (float __K_P))
   (setq _K_W (float __K_W))
   self)
  (:enable
   (&optional (__enable :null))
   (if (not (eq __enable :null)) (setq _enable __enable)) _enable)
  (:T
   (&optional __T)
   (if __T (setq _T __T)) _T)
  (:W
   (&optional __W)
   (if __W (setq _W __W)) _W)
  (:Pos
   (&optional __Pos)
   (if __Pos (setq _Pos __Pos)) _Pos)
  (:K_P
   (&optional __K_P)
   (if __K_P (setq _K_P __K_P)) _K_P)
  (:K_W
   (&optional __K_W)
   (if __K_W (setq _K_W __K_W)) _K_W)
  (:serialization-length
   ()
   (+
    ;; bool _enable
    1
    ;; float32 _T
    4
    ;; float32 _W
    4
    ;; float32 _Pos
    4
    ;; float32 _K_P
    4
    ;; float32 _K_W
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _enable
       (if _enable (write-byte -1 s) (write-byte 0 s))
     ;; float32 _T
       (sys::poke _T (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _W
       (sys::poke _W (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Pos
       (sys::poke _Pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _K_P
       (sys::poke _K_P (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _K_W
       (sys::poke _K_W (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _enable
     (setq _enable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _T
     (setq _T (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _W
     (setq _W (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Pos
     (setq _Pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _K_P
     (setq _K_P (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _K_W
     (setq _K_W (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get unitree_motor::Ctrl :md5sum-) "2c076a68349d15f6ea7b8be4ef49b0a7")
(setf (get unitree_motor::Ctrl :datatype-) "unitree_motor/Ctrl")
(setf (get unitree_motor::Ctrl :definition-)
      "bool        enable
float32     T       # Desired output torque of motor【期望电机本身的输出力矩（Nm）】 单位：Nm, T<255.9
float32     W       # Desired output speed of motor【期望电机本身的速度(rad/s)】 单位：rad/s, W<511.9
float32     Pos     #单位：rad, Pos<131071.9
float32     K_P     #K_P<31.9
float32     K_W     #K_W<63.9
")



(provide :unitree_motor/Ctrl "2c076a68349d15f6ea7b8be4ef49b0a7")


