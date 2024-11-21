;; Auto-generated. Do not edit!


(when (boundp 'ground_reaction_force::GRF_Data)
  (if (not (find-package "GROUND_REACTION_FORCE"))
    (make-package "GROUND_REACTION_FORCE"))
  (shadow 'GRF_Data (find-package "GROUND_REACTION_FORCE")))
(unless (find-package "GROUND_REACTION_FORCE::GRF_DATA")
  (make-package "GROUND_REACTION_FORCE::GRF_DATA"))

(in-package "ROS")
;;//! \htmlinclude GRF_Data.msg.html


(defclass ground_reaction_force::GRF_Data
  :super ros::object
  :slots (_fore _mid _hind _all_force _stance_flg ))

(defmethod ground_reaction_force::GRF_Data
  (:init
   (&key
    ((:fore __fore) 0.0)
    ((:mid __mid) 0.0)
    ((:hind __hind) 0.0)
    ((:all_force __all_force) 0.0)
    ((:stance_flg __stance_flg) nil)
    )
   (send-super :init)
   (setq _fore (float __fore))
   (setq _mid (float __mid))
   (setq _hind (float __hind))
   (setq _all_force (float __all_force))
   (setq _stance_flg __stance_flg)
   self)
  (:fore
   (&optional __fore)
   (if __fore (setq _fore __fore)) _fore)
  (:mid
   (&optional __mid)
   (if __mid (setq _mid __mid)) _mid)
  (:hind
   (&optional __hind)
   (if __hind (setq _hind __hind)) _hind)
  (:all_force
   (&optional __all_force)
   (if __all_force (setq _all_force __all_force)) _all_force)
  (:stance_flg
   (&optional (__stance_flg :null))
   (if (not (eq __stance_flg :null)) (setq _stance_flg __stance_flg)) _stance_flg)
  (:serialization-length
   ()
   (+
    ;; float32 _fore
    4
    ;; float32 _mid
    4
    ;; float32 _hind
    4
    ;; float32 _all_force
    4
    ;; bool _stance_flg
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _fore
       (sys::poke _fore (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _mid
       (sys::poke _mid (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _hind
       (sys::poke _hind (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _all_force
       (sys::poke _all_force (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _stance_flg
       (if _stance_flg (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _fore
     (setq _fore (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _mid
     (setq _mid (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _hind
     (setq _hind (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _all_force
     (setq _all_force (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _stance_flg
     (setq _stance_flg (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ground_reaction_force::GRF_Data :md5sum-) "5b6c0986b39b00f008d103a1a1b557b8")
(setf (get ground_reaction_force::GRF_Data :datatype-) "ground_reaction_force/GRF_Data")
(setf (get ground_reaction_force::GRF_Data :definition-)
      "float32 fore
float32 mid
float32 hind
float32 all_force
bool stance_flg
")



(provide :ground_reaction_force/GRF_Data "5b6c0986b39b00f008d103a1a1b557b8")


