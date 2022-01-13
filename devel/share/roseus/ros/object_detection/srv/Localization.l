;; Auto-generated. Do not edit!


(when (boundp 'object_detection::Localization)
  (if (not (find-package "OBJECT_DETECTION"))
    (make-package "OBJECT_DETECTION"))
  (shadow 'Localization (find-package "OBJECT_DETECTION")))
(unless (find-package "OBJECT_DETECTION::LOCALIZATION")
  (make-package "OBJECT_DETECTION::LOCALIZATION"))
(unless (find-package "OBJECT_DETECTION::LOCALIZATIONREQUEST")
  (make-package "OBJECT_DETECTION::LOCALIZATIONREQUEST"))
(unless (find-package "OBJECT_DETECTION::LOCALIZATIONRESPONSE")
  (make-package "OBJECT_DETECTION::LOCALIZATIONRESPONSE"))

(in-package "ROS")





(defclass object_detection::LocalizationRequest
  :super ros::object
  :slots ())

(defmethod object_detection::LocalizationRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass object_detection::LocalizationResponse
  :super ros::object
  :slots (_Coords ))

(defmethod object_detection::LocalizationResponse
  (:init
   (&key
    ((:Coords __Coords) (instance object_detection::GoalPositions :init))
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
    ;; object_detection/GoalPositions _Coords
    (send _Coords :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; object_detection/GoalPositions _Coords
       (send _Coords :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; object_detection/GoalPositions _Coords
     (send _Coords :deserialize buf ptr-) (incf ptr- (send _Coords :serialization-length))
   ;;
   self)
  )

(defclass object_detection::Localization
  :super ros::object
  :slots ())

(setf (get object_detection::Localization :md5sum-) "742db672f1005567be304d1ccc310265")
(setf (get object_detection::Localization :datatype-) "object_detection/Localization")
(setf (get object_detection::Localization :request) object_detection::LocalizationRequest)
(setf (get object_detection::Localization :response) object_detection::LocalizationResponse)

(defmethod object_detection::LocalizationRequest
  (:response () (instance object_detection::LocalizationResponse :init)))

(setf (get object_detection::LocalizationRequest :md5sum-) "742db672f1005567be304d1ccc310265")
(setf (get object_detection::LocalizationRequest :datatype-) "object_detection/LocalizationRequest")
(setf (get object_detection::LocalizationRequest :definition-)
      "
---
GoalPositions Coords


================================================================================
MSG: object_detection/GoalPositions
GoalPos[] Coords

================================================================================
MSG: object_detection/GoalPos
float32 X
float32 Y
float32 Z
")

(setf (get object_detection::LocalizationResponse :md5sum-) "742db672f1005567be304d1ccc310265")
(setf (get object_detection::LocalizationResponse :datatype-) "object_detection/LocalizationResponse")
(setf (get object_detection::LocalizationResponse :definition-)
      "
---
GoalPositions Coords


================================================================================
MSG: object_detection/GoalPositions
GoalPos[] Coords

================================================================================
MSG: object_detection/GoalPos
float32 X
float32 Y
float32 Z
")



(provide :object_detection/Localization "742db672f1005567be304d1ccc310265")


