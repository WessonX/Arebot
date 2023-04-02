
(cl:in-package :asdf)

(defsystem "arebot_control-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "BusOp" :depends-on ("_package_BusOp"))
    (:file "_package_BusOp" :depends-on ("_package"))
  ))