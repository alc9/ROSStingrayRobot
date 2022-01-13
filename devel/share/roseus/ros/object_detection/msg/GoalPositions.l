;; Auto-generated. Do not edit!


(when (boundp 'object_detection::GoalPositions)
  (if (not (find-package "OBJECT_DETECTION"))
    (make-package "OBJECT_DETECTION"))
  (shadow 'GoalPositions (find-package "OBJECT_DETECTION")))
(unless (find-package "OBJECT_DETECTION::GOALPOSITIONS")
  (make-package "OBJECT_DETECTION::GOALPOSITIONS"))

(in-package "ROS")
;;//! \htmlinclude GoalPositions.msg.html


(defclass object_detection::GoalPositions
  :super ros::object
  :slots (_Coords ))

(defmethod object_detection::GoalPositions
  (:init
   (&key
    ((:Coords __Coords) (let (r) (dotimes (i 0) (push (instance object_detection::GoalPos :init) r)) r))
    )
   (send-super :init)
   (setq _Coords __Coords)
   self)
  (:Coords
   (&rest __Coords)
   (if (keywordp (car __Coords))
       (send* _Coords __Coords)
     (progn
       (if __Coords (setq _Coords (car __Coords)))
       _Coords)))
  (:serialization-length
   ()
   (+
    ;; object_detection/GoalPos[] _Coords
    (apply #'+ (send-all _Coords :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; object_detection/GoalPos[] _Coords
     (write-long (length _Coords) s)
     (dolist (elem _Coords)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; object_detection/GoalPos[] _Coords
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Coords (let (r) (dotimes (i n) (push (instance object_detection::GoalPos :init) r)) r))
     (dolist (elem- _Coords)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get object_detection::GoalPositions :md5sum-) "6e1cbfbf293ab70ab330ff223c5f1fcd")
(setf (get object_detection::GoalPositions :datatype-) "object_detection/GoalPositions")
(setf (get object_detection::GoalPositions :definition-)
      "GoalPos[] Coords

================================================================================
MSG: object_detection/GoalPos
float32 X
float32 Y
float32 Z

")



(provide :object_detection/GoalPositions "6e1cbfbf293ab70ab330ff223c5f1fcd")


