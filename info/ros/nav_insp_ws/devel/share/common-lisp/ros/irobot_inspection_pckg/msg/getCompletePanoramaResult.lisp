; Auto-generated. Do not edit!


(cl:in-package irobot_inspection_pckg-msg)


;//! \htmlinclude getCompletePanoramaResult.msg.html

(cl:defclass <getCompletePanoramaResult> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass getCompletePanoramaResult (<getCompletePanoramaResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getCompletePanoramaResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getCompletePanoramaResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name irobot_inspection_pckg-msg:<getCompletePanoramaResult> is deprecated: use irobot_inspection_pckg-msg:getCompletePanoramaResult instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getCompletePanoramaResult>) ostream)
  "Serializes a message object of type '<getCompletePanoramaResult>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getCompletePanoramaResult>) istream)
  "Deserializes a message object of type '<getCompletePanoramaResult>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getCompletePanoramaResult>)))
  "Returns string type for a message object of type '<getCompletePanoramaResult>"
  "irobot_inspection_pckg/getCompletePanoramaResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getCompletePanoramaResult)))
  "Returns string type for a message object of type 'getCompletePanoramaResult"
  "irobot_inspection_pckg/getCompletePanoramaResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getCompletePanoramaResult>)))
  "Returns md5sum for a message object of type '<getCompletePanoramaResult>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getCompletePanoramaResult)))
  "Returns md5sum for a message object of type 'getCompletePanoramaResult"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getCompletePanoramaResult>)))
  "Returns full string definition for message of type '<getCompletePanoramaResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%#bool finished~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getCompletePanoramaResult)))
  "Returns full string definition for message of type 'getCompletePanoramaResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result definition~%#bool finished~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getCompletePanoramaResult>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getCompletePanoramaResult>))
  "Converts a ROS message object to a list"
  (cl:list 'getCompletePanoramaResult
))
