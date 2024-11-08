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
  :slots (_midtop_mid _all_force _bot_Med _bot_lat _stance_flg ))

(defmethod ground_reaction_force::GRF_Data
  (:init
   (&key
    ((:midtop_mid __midtop_mid) 0.0)
    ((:all_force __all_force) 0.0)
    ((:bot_Med __bot_Med) 0.0)
    ((:bot_lat __bot_lat) 0.0)
    ((:stance_flg __stance_flg) nil)
    )
   (send-super :init)
   (setq _midtop_mid (float __midtop_mid))
   (setq _all_force (float __all_force))
   (setq _bot_Med (float __bot_Med))
   (setq _bot_lat (float __bot_lat))
   (setq _stance_flg __stance_flg)
   self)
  (:midtop_mid
   (&optional __midtop_mid)
   (if __midtop_mid (setq _midtop_mid __midtop_mid)) _midtop_mid)
  (:all_force
   (&optional __all_force)
   (if __all_force (setq _all_force __all_force)) _all_force)
  (:bot_Med
   (&optional __bot_Med)
   (if __bot_Med (setq _bot_Med __bot_Med)) _bot_Med)
  (:bot_lat
   (&optional __bot_lat)
   (if __bot_lat (setq _bot_lat __bot_lat)) _bot_lat)
  (:stance_flg
   (&optional (__stance_flg :null))
   (if (not (eq __stance_flg :null)) (setq _stance_flg __stance_flg)) _stance_flg)
  (:serialization-length
   ()
   (+
    ;; float32 _midtop_mid
    4
    ;; float32 _all_force
    4
    ;; float32 _bot_Med
    4
    ;; float32 _bot_lat
    4
    ;; bool _stance_flg
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _midtop_mid
       (sys::poke _midtop_mid (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _all_force
       (sys::poke _all_force (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _bot_Med
       (sys::poke _bot_Med (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _bot_lat
       (sys::poke _bot_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _stance_flg
       (if _stance_flg (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _midtop_mid
     (setq _midtop_mid (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _all_force
     (setq _all_force (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _bot_Med
     (setq _bot_Med (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _bot_lat
     (setq _bot_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _stance_flg
     (setq _stance_flg (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ground_reaction_force::GRF_Data :md5sum-) "7f6bc012a85df06ce5797caa5e247628")
(setf (get ground_reaction_force::GRF_Data :datatype-) "ground_reaction_force/GRF_Data")
(setf (get ground_reaction_force::GRF_Data :definition-)
      "float32 midtop_mid
float32 all_force
float32 bot_Med
float32 bot_lat
bool stance_flg
")



(provide :ground_reaction_force/GRF_Data "7f6bc012a85df06ce5797caa5e247628")


