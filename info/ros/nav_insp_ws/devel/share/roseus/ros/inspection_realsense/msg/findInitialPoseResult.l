;; Auto-generated. Do not edit!


(when (boundp 'inspection_realsense::findInitialPoseResult)
  (if (not (find-package "INSPECTION_REALSENSE"))
    (make-package "INSPECTION_REALSENSE"))
  (shadow 'findInitialPoseResult (find-package "INSPECTION_REALSENSE")))
(unless (find-package "INSPECTION_REALSENSE::FINDINITIALPOSERESULT")
  (make-package "INSPECTION_REALSENSE::FINDINITIALPOSERESULT"))

(in-package "ROS")
;;//! \htmlinclude findInitialPoseResult.msg.html


(defclass inspection_realsense::findInitialPoseResult
  :super ros::object
  :slots (_finished _n_pasadas_totales ))

(defmethod inspection_realsense::findInitialPoseResult
  (:init
   (&key
    ((:finished __finished) nil)
    ((:n_pasadas_totales __n_pasadas_totales) 0)
    )
   (send-super :init)
   (setq _finished __finished)
   (setq _n_pasadas_totales (round __n_pasadas_totales))
   self)
  (:finished
   (&optional __finished)
   (if __finished (setq _finished __finished)) _finished)
  (:n_pasadas_totales
   (&optional __n_pasadas_totales)
   (if __n_pasadas_totales (setq _n_pasadas_totales __n_pasadas_totales)) _n_pasadas_totales)
  (:serialization-length
   ()
   (+
    ;; bool _finished
    1
    ;; int32 _n_pasadas_totales
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _finished
       (if _finished (write-byte -1 s) (write-byte 0 s))
     ;; int32 _n_pasadas_totales
       (write-long _n_pasadas_totales s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _finished
     (setq _finished (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int32 _n_pasadas_totales
     (setq _n_pasadas_totales (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get inspection_realsense::findInitialPoseResult :md5sum-) "0364f8fadbc00287ab44396c35cc11f8")
(setf (get inspection_realsense::findInitialPoseResult :datatype-) "inspection_realsense/findInitialPoseResult")
(setf (get inspection_realsense::findInitialPoseResult :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#result definition
bool finished
int32 n_pasadas_totales

")



(provide :inspection_realsense/findInitialPoseResult "0364f8fadbc00287ab44396c35cc11f8")

