;; Auto-generated. Do not edit!


(when (boundp 'action_server::defResult)
  (if (not (find-package "ACTION_SERVER"))
    (make-package "ACTION_SERVER"))
  (shadow 'defResult (find-package "ACTION_SERVER")))
(unless (find-package "ACTION_SERVER::DEFRESULT")
  (make-package "ACTION_SERVER::DEFRESULT"))

(in-package "ROS")
;;//! \htmlinclude defResult.msg.html


(defclass action_server::defResult
  :super ros::object
  :slots (_status ))

(defmethod action_server::defResult
  (:init
   (&key
    ((:status __status) nil)
    )
   (send-super :init)
   (setq _status __status)
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; bool _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _status
       (if _status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _status
     (setq _status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get action_server::defResult :md5sum-) "3a1255d4d998bd4d6585c64639b5ee9a")
(setf (get action_server::defResult :datatype-) "action_server/defResult")
(setf (get action_server::defResult :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#result
bool status

")



(provide :action_server/defResult "3a1255d4d998bd4d6585c64639b5ee9a")


