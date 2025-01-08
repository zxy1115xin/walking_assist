;; Auto-generated. Do not edit!


(when (boundp 'unitree_motor::Sensor)
  (if (not (find-package "UNITREE_MOTOR"))
    (make-package "UNITREE_MOTOR"))
  (shadow 'Sensor (find-package "UNITREE_MOTOR")))
(unless (find-package "UNITREE_MOTOR::SENSOR")
  (make-package "UNITREE_MOTOR::SENSOR"))

(in-package "ROS")
;;//! \htmlinclude Sensor.msg.html


(defclass unitree_motor::Sensor
  :super ros::object
  :slots (_motor_id _T _Pos _Temp ))

(defmethod unitree_motor::Sensor
  (:init
   (&key
    ((:motor_id __motor_id) 0)
    ((:T __T) 0.0)
    ((:Pos __Pos) 0.0)
    ((:Temp __Temp) 0.0)
    )
   (send-super :init)
   (setq _motor_id (round __motor_id))
   (setq _T (float __T))
   (setq _Pos (float __Pos))
   (setq _Temp (float __Temp))
   self)
  (:motor_id
   (&optional __motor_id)
   (if __motor_id (setq _motor_id __motor_id)) _motor_id)
  (:T
   (&optional __T)
   (if __T (setq _T __T)) _T)
  (:Pos
   (&optional __Pos)
   (if __Pos (setq _Pos __Pos)) _Pos)
  (:Temp
   (&optional __Temp)
   (if __Temp (setq _Temp __Temp)) _Temp)
  (:serialization-length
   ()
   (+
    ;; char _motor_id
    1
    ;; float32 _T
    4
    ;; float32 _Pos
    4
    ;; float32 _Temp
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; char _motor_id
       (write-byte _motor_id s)
     ;; float32 _T
       (sys::poke _T (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Pos
       (sys::poke _Pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Temp
       (sys::poke _Temp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; char _motor_id
     (setq _motor_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _T
     (setq _T (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Pos
     (setq _Pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Temp
     (setq _Temp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get unitree_motor::Sensor :md5sum-) "beee0c2c439c8763e3016584e8002537")
(setf (get unitree_motor::Sensor :datatype-) "unitree_motor/Sensor")
(setf (get unitree_motor::Sensor :definition-)
      "char        motor_id    #Motor ID【电机ID】
float32     T           #The output torque of motor【当前实际电机输出力矩】
float32     Pos         #The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】
float32     Temp         # 温度

")



(provide :unitree_motor/Sensor "beee0c2c439c8763e3016584e8002537")


