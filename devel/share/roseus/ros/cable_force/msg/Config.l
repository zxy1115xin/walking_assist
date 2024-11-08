;; Auto-generated. Do not edit!


(when (boundp 'cable_force::Config)
  (if (not (find-package "CABLE_FORCE"))
    (make-package "CABLE_FORCE"))
  (shadow 'Config (find-package "CABLE_FORCE")))
(unless (find-package "CABLE_FORCE::CONFIG")
  (make-package "CABLE_FORCE::CONFIG"))

(in-package "ROS")
;;//! \htmlinclude Config.msg.html


(defclass cable_force::Config
  :super ros::object
  :slots (_channel _force ))

(defmethod cable_force::Config
  (:init
   (&key
    ((:channel __channel) 0)
    ((:force __force) 0.0)
    )
   (send-super :init)
   (setq _channel (round __channel))
   (setq _force (float __force))
   self)
  (:channel
   (&optional __channel)
   (if __channel (setq _channel __channel)) _channel)
  (:force
   (&optional __force)
   (if __force (setq _force __force)) _force)
  (:serialization-length
   ()
   (+
    ;; int32 _channel
    4
    ;; float32 _force
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _channel
       (write-long _channel s)
     ;; float32 _force
       (sys::poke _force (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _channel
     (setq _channel (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _force
     (setq _force (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cable_force::Config :md5sum-) "2cda1c75dfcd91f4ed0e090f920fd0e1")
(setf (get cable_force::Config :datatype-) "cable_force/Config")
(setf (get cable_force::Config :definition-)
      "int32 channel
float32 force
")



(provide :cable_force/Config "2cda1c75dfcd91f4ed0e090f920fd0e1")


