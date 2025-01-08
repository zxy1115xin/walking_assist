;; Auto-generated. Do not edit!


(when (boundp 'control::Command)
  (if (not (find-package "CONTROL"))
    (make-package "CONTROL"))
  (shadow 'Command (find-package "CONTROL")))
(unless (find-package "CONTROL::COMMAND")
  (make-package "CONTROL::COMMAND"))

(in-package "ROS")
;;//! \htmlinclude Command.msg.html


(defclass control::Command
  :super ros::object
  :slots (_mode _force _kp _ki _kd _flag _Tsta _Trise _Tfall _Fmax _measure ))

(defmethod control::Command
  (:init
   (&key
    ((:mode __mode) 0)
    ((:force __force) 0.0)
    ((:kp __kp) 0.0)
    ((:ki __ki) 0.0)
    ((:kd __kd) 0.0)
    ((:flag __flag) 0)
    ((:Tsta __Tsta) 0.0)
    ((:Trise __Trise) 0.0)
    ((:Tfall __Tfall) 0.0)
    ((:Fmax __Fmax) 0.0)
    ((:measure __measure) 0)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _force (float __force))
   (setq _kp (float __kp))
   (setq _ki (float __ki))
   (setq _kd (float __kd))
   (setq _flag (round __flag))
   (setq _Tsta (float __Tsta))
   (setq _Trise (float __Trise))
   (setq _Tfall (float __Tfall))
   (setq _Fmax (float __Fmax))
   (setq _measure (round __measure))
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:force
   (&optional __force)
   (if __force (setq _force __force)) _force)
  (:kp
   (&optional __kp)
   (if __kp (setq _kp __kp)) _kp)
  (:ki
   (&optional __ki)
   (if __ki (setq _ki __ki)) _ki)
  (:kd
   (&optional __kd)
   (if __kd (setq _kd __kd)) _kd)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:Tsta
   (&optional __Tsta)
   (if __Tsta (setq _Tsta __Tsta)) _Tsta)
  (:Trise
   (&optional __Trise)
   (if __Trise (setq _Trise __Trise)) _Trise)
  (:Tfall
   (&optional __Tfall)
   (if __Tfall (setq _Tfall __Tfall)) _Tfall)
  (:Fmax
   (&optional __Fmax)
   (if __Fmax (setq _Fmax __Fmax)) _Fmax)
  (:measure
   (&optional __measure)
   (if __measure (setq _measure __measure)) _measure)
  (:serialization-length
   ()
   (+
    ;; int32 _mode
    4
    ;; float32 _force
    4
    ;; float32 _kp
    4
    ;; float32 _ki
    4
    ;; float32 _kd
    4
    ;; int32 _flag
    4
    ;; float32 _Tsta
    4
    ;; float32 _Trise
    4
    ;; float32 _Tfall
    4
    ;; float32 _Fmax
    4
    ;; int32 _measure
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _mode
       (write-long _mode s)
     ;; float32 _force
       (sys::poke _force (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _kp
       (sys::poke _kp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ki
       (sys::poke _ki (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _kd
       (sys::poke _kd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _flag
       (write-long _flag s)
     ;; float32 _Tsta
       (sys::poke _Tsta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Trise
       (sys::poke _Trise (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Tfall
       (sys::poke _Tfall (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Fmax
       (sys::poke _Fmax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _measure
       (write-long _measure s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _mode
     (setq _mode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _force
     (setq _force (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _kp
     (setq _kp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ki
     (setq _ki (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _kd
     (setq _kd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _flag
     (setq _flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _Tsta
     (setq _Tsta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Trise
     (setq _Trise (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Tfall
     (setq _Tfall (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Fmax
     (setq _Fmax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _measure
     (setq _measure (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get control::Command :md5sum-) "9b8e94fa3e1923da82a28a1fd42c0d6b")
(setf (get control::Command :datatype-) "control/Command")
(setf (get control::Command :definition-)
      "int32 mode  #mode 1 力位控制 mode 2  速度模式 mode 3 位置模式
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
")



(provide :control/Command "9b8e94fa3e1923da82a28a1fd42c0d6b")


