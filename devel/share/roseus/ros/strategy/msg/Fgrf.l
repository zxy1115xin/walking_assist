;; Auto-generated. Do not edit!


(when (boundp 'strategy::Fgrf)
  (if (not (find-package "STRATEGY"))
    (make-package "STRATEGY"))
  (shadow 'Fgrf (find-package "STRATEGY")))
(unless (find-package "STRATEGY::FGRF")
  (make-package "STRATEGY::FGRF"))

(in-package "ROS")
;;//! \htmlinclude Fgrf.msg.html


(defclass strategy::Fgrf
  :super ros::object
  :slots (_all_force _stance_flg ))

(defmethod strategy::Fgrf
  (:init
   (&key
    ((:all_force __all_force) 0.0)
    ((:stance_flg __stance_flg) nil)
    )
   (send-super :init)
   (setq _all_force (float __all_force))
   (setq _stance_flg __stance_flg)
   self)
  (:all_force
   (&optional __all_force)
   (if __all_force (setq _all_force __all_force)) _all_force)
  (:stance_flg
   (&optional (__stance_flg :null))
   (if (not (eq __stance_flg :null)) (setq _stance_flg __stance_flg)) _stance_flg)
  (:serialization-length
   ()
   (+
    ;; float32 _all_force
    4
    ;; bool _stance_flg
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _all_force
       (sys::poke _all_force (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _stance_flg
       (if _stance_flg (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _all_force
     (setq _all_force (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _stance_flg
     (setq _stance_flg (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get strategy::Fgrf :md5sum-) "c3590a53ab517e32293f777e708cbb60")
(setf (get strategy::Fgrf :datatype-) "strategy/Fgrf")
(setf (get strategy::Fgrf :definition-)
      "float32 all_force
bool stance_flg
")



(provide :strategy/Fgrf "c3590a53ab517e32293f777e708cbb60")


