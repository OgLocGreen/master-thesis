
(cl:in-package :asdf)

(defsystem "aux_controllers-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetFrame" :depends-on ("_package_SetFrame"))
    (:file "_package_SetFrame" :depends-on ("_package"))
  ))