
(cl:in-package :asdf)

(defsystem "ground_reaction_force-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GRF_Data" :depends-on ("_package_GRF_Data"))
    (:file "_package_GRF_Data" :depends-on ("_package"))
    (:file "GRF_Data1" :depends-on ("_package_GRF_Data1"))
    (:file "_package_GRF_Data1" :depends-on ("_package"))
    (:file "GRF_Data2" :depends-on ("_package_GRF_Data2"))
    (:file "_package_GRF_Data2" :depends-on ("_package"))
  ))