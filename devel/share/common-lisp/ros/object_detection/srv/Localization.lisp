; Auto-generated. Do not edit!


(cl:in-package object_detection-srv)


;//! \htmlinclude Localization-request.msg.html

(cl:defclass <Localization-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass Localization-request (<Localization-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Localization-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Localization-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name object_detection-srv:<Localization-request> is deprecated: use object_detection-srv:Localization-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Localization-request>) ostream)
  "Serializes a message object of type '<Localization-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Localization-request>) istream)
  "Deserializes a message object of type '<Localization-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Localization-request>)))
  "Returns string type for a service object of type '<Localization-request>"
  "object_detection/LocalizationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Localization-request)))
  "Returns string type for a service object of type 'Localization-request"
  "object_detection/LocalizationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Localization-request>)))
  "Returns md5sum for a message object of type '<Localization-request>"
  "742db672f1005567be304d1ccc310265")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Localization-request)))
  "Returns md5sum for a message object of type 'Localization-request"
  "742db672f1005567be304d1ccc310265")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Localization-request>)))
  "Returns full string definition for message of type '<Localization-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Localization-request)))
  "Returns full string definition for message of type 'Localization-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Localization-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Localization-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Localization-request
))
;//! \htmlinclude Localization-response.msg.html

(cl:defclass <Localization-response> (roslisp-msg-protocol:ros-message)
  ((Coords
    :reader Coords
    :initarg :Coords
    :type object_detection-msg:GoalPositions
    :initform (cl:make-instance 'object_detection-msg:GoalPositions)))
)

(cl:defclass Localization-response (<Localization-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Localization-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Localization-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name object_detection-srv:<Localization-response> is deprecated: use object_detection-srv:Localization-response instead.")))

(cl:ensure-generic-function 'Coords-val :lambda-list '(m))
(cl:defmethod Coords-val ((m <Localization-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader object_detection-srv:Coords-val is deprecated.  Use object_detection-srv:Coords instead.")
  (Coords m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Localization-response>) ostream)
  "Serializes a message object of type '<Localization-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Coords) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Localization-response>) istream)
  "Deserializes a message object of type '<Localization-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Coords) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Localization-response>)))
  "Returns string type for a service object of type '<Localization-response>"
  "object_detection/LocalizationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Localization-response)))
  "Returns string type for a service object of type 'Localization-response"
  "object_detection/LocalizationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Localization-response>)))
  "Returns md5sum for a message object of type '<Localization-response>"
  "742db672f1005567be304d1ccc310265")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Localization-response)))
  "Returns md5sum for a message object of type 'Localization-response"
  "742db672f1005567be304d1ccc310265")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Localization-response>)))
  "Returns full string definition for message of type '<Localization-response>"
  (cl:format cl:nil "GoalPositions Coords~%~%~%================================================================================~%MSG: object_detection/GoalPositions~%GoalPos[] Coords~%~%================================================================================~%MSG: object_detection/GoalPos~%float32 X~%float32 Y~%float32 Z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Localization-response)))
  "Returns full string definition for message of type 'Localization-response"
  (cl:format cl:nil "GoalPositions Coords~%~%~%================================================================================~%MSG: object_detection/GoalPositions~%GoalPos[] Coords~%~%================================================================================~%MSG: object_detection/GoalPos~%float32 X~%float32 Y~%float32 Z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Localization-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Coords))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Localization-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Localization-response
    (cl:cons ':Coords (Coords msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Localization)))
  'Localization-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Localization)))
  'Localization-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Localization)))
  "Returns string type for a service object of type '<Localization>"
  "object_detection/Localization")