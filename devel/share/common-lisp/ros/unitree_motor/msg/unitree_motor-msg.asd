
(cl:in-package :asdf)

(defsystem "unitree_motor-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Ctrl" :depends-on ("_package_Ctrl"))
    (:file "_package_Ctrl" :depends-on ("_package"))
    (:file "Sensor" :depends-on ("_package_Sensor"))
    (:file "_package_Sensor" :depends-on ("_package"))
    (:file "Sensor1" :depends-on ("_package_Sensor1"))
    (:file "_package_Sensor1" :depends-on ("_package"))
  ))