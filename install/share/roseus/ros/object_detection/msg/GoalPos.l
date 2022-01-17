;; Auto-generated. Do not edit!


(when (boundp 'object_detection::GoalPos)
  (if (not (find-package "OBJECT_DETECTION"))
    (make-package "OBJECT_DETECTION"))
  (shadow 'GoalPos (find-package "OBJECT_DETECTION")))
(unless (find-package "OBJECT_DETECTION::GOALPOS")
  (make-package "OBJECT_DETECTION::GOALPOS"))

(in-package "ROS")
;;//! \htmlinclude GoalPos.msg.html


(defclass object_detection::GoalPos
  :super ros::object
  :slots (_X _Y _Z ))

(defmethod object_detection::GoalPos
  (:init
   (&key
    ((:X __X) 0.0)
    ((:Y __Y) 0.0)
    ((:Z __Z) 0.0)
    )
   (send-super :init)
   (setq _X (float __X))
   (setq _Y (float __Y))
   (setq _Z (float __Z))
   self)
  (:X
   (&optional __X)
   (if __X (setq _X __X)) _X)
  (:Y
   (&optional __Y)
   (if __Y (setq _Y __Y)) _Y)
  (:Z
   (&optional __Z)
   (if __Z (setq _Z __Z)) _Z)
  (:serialization-length
   ()
   (+
    ;; float32 _X
    4
    ;; float32 _Y
    4
    ;; float32 _Z
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _X
       (sys::poke _X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Y
       (sys::poke _Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Z
       (sys::poke _Z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _X
     (setq _X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Y
     (setq _Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Z
     (setq _Z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get object_detection::GoalPos :md5sum-) "a1dfb8f61d81d8e9fe291bc0d86a2f48")
(setf (get object_detection::GoalPos :datatype-) "object_detection/GoalPos")
(setf (get object_detection::GoalPos :definition-)
      "float32 X
float32 Y
float32 Z

")



(provide :object_detection/GoalPos "a1dfb8f61d81d8e9fe291bc0d86a2f48")


