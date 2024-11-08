
(cl:in-package :asdf)

(defsystem "strategy_test-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Fgrf" :depends-on ("_package_Fgrf"))
    (:file "_package_Fgrf" :depends-on ("_package"))
  ))