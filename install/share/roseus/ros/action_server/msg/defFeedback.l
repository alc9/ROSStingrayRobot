;; Auto-generated. Do not edit!


(when (boundp 'action_server::defFeedback)
  (if (not (find-package "ACTION_SERVER"))
    (make-package "ACTION_SERVER"))
  (shadow 'defFeedback (find-package "ACTION_SERVER")))
(unless (find-package "ACTION_SERVER::DEFFEEDBACK")
  (make-package "ACTION_SERVER::DEFFEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude defFeedback.msg.html


(defclass action_server::defFeedback
  :super ros::object
  :slots (_distance ))

(defmethod action_server::defFeedback
  (:init
   (&key
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _distance (float __distance))
   self)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; float64 _distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _distance
     (setq _distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get action_server::defFeedback :md5sum-) "acff7fda0c683c872875f5c4b069f124")
(setf (get action_server::defFeedback :datatype-) "action_server/defFeedback")
(setf (get action_server::defFeedback :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#feedback
float64 distance


")



(provide :action_server/defFeedback "acff7fda0c683c872875f5c4b069f124")


