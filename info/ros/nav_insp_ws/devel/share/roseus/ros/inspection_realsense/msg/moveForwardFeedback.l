;; Auto-generated. Do not edit!


(when (boundp 'inspection_realsense::moveForwardFeedback)
  (if (not (find-package "INSPECTION_REALSENSE"))
    (make-package "INSPECTION_REALSENSE"))
  (shadow 'moveForwardFeedback (find-package "INSPECTION_REALSENSE")))
(unless (find-package "INSPECTION_REALSENSE::MOVEFORWARDFEEDBACK")
  (make-package "INSPECTION_REALSENSE::MOVEFORWARDFEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude moveForwardFeedback.msg.html


(defclass inspection_realsense::moveForwardFeedback
  :super ros::object
  :slots (_sequence ))

(defmethod inspection_realsense::moveForwardFeedback
  (:init
   (&key
    ((:sequence __sequence) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _sequence __sequence)
   self)
  (:sequence
   (&optional __sequence)
   (if __sequence (setq _sequence __sequence)) _sequence)
  (:serialization-length
   ()
   (+
    ;; int32[] _sequence
    (* 4    (length _sequence)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32[] _sequence
     (write-long (length _sequence) s)
     (dotimes (i (length _sequence))
       (write-long (elt _sequence i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32[] _sequence
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _sequence (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _sequence i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get inspection_realsense::moveForwardFeedback :md5sum-) "b81e37d2a31925a0e8ae261a8699cb79")
(setf (get inspection_realsense::moveForwardFeedback :datatype-) "inspection_realsense/moveForwardFeedback")
(setf (get inspection_realsense::moveForwardFeedback :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#feedback
int32[] sequence



")



(provide :inspection_realsense/moveForwardFeedback "b81e37d2a31925a0e8ae261a8699cb79")

