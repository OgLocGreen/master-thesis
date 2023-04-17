
(cl:in-package :asdf)

(defsystem "action_server_package-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "ChapaStorage" :depends-on ("_package_ChapaStorage"))
    (:file "_package_ChapaStorage" :depends-on ("_package"))
    (:file "FCPP_in" :depends-on ("_package_FCPP_in"))
    (:file "_package_FCPP_in" :depends-on ("_package"))
  ))