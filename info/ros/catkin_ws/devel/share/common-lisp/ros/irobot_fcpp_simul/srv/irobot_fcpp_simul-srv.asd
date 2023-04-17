
(cl:in-package :asdf)

(defsystem "irobot_fcpp_simul-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :irobot_fcpp_simul-msg
)
  :components ((:file "_package")
    (:file "FCPP_in" :depends-on ("_package_FCPP_in"))
    (:file "_package_FCPP_in" :depends-on ("_package"))
    (:file "FCPP_out" :depends-on ("_package_FCPP_out"))
    (:file "_package_FCPP_out" :depends-on ("_package"))
    (:file "IROBOT_ir_data" :depends-on ("_package_IROBOT_ir_data"))
    (:file "_package_IROBOT_ir_data" :depends-on ("_package"))
  ))