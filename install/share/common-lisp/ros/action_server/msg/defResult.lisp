; Auto-generated. Do not edit!


(cl:in-package action_server-msg)


;//! \htmlinclude defResult.msg.html

(cl:defclass <defResult> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass defResult (<defResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <defResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'defResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_server-msg:<defResult> is deprecated: use action_server-msg:defResult instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <defResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_server-msg:status-val is deprecated.  Use action_server-msg:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <defResult>) ostream)
  "Serializes a message object of type '<defResult>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <defResult>) istream)
  "Deserializes a message object of type '<defResult>"
    (cl:setf (cl:slot-value msg 'status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<defResult>)))
  "Returns string type for a message object of type '<defResult>"
  "action_server/defResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'defResult)))
  "Returns string type for a message object of type 'defResult"
  "action_server/defResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<defResult>)))
  "Returns md5sum for a message object of type '<defResult>"
  "3a1255d4d998bd4d6585c64639b5ee9a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'defResult)))
  "Returns md5sum for a message object of type 'defResult"
  "3a1255d4d998bd4d6585c64639b5ee9a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<defResult>)))
  "Returns full string definition for message of type '<defResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result~%bool status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'defResult)))
  "Returns full string definition for message of type 'defResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#result~%bool status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <defResult>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <defResult>))
  "Converts a ROS message object to a list"
  (cl:list 'defResult
    (cl:cons ':status (status msg))
))
