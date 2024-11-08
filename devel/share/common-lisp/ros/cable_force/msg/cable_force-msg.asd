
(cl:in-package :asdf)

(defsystem "cable_force-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Config" :depends-on ("_package_Config"))
    (:file "_package_Config" :depends-on ("_package"))
    (:file "Load" :depends-on ("_package_Load"))
    (:file "_package_Load" :depends-on ("_package"))
  ))