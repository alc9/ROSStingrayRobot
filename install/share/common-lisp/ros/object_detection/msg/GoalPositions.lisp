; Auto-generated. Do not edit!


(cl:in-package object_detection-msg)


;//! \htmlinclude GoalPositions.msg.html

(cl:defclass <GoalPositions> (roslisp-msg-protocol:ros-message)
  ((Coords
    :reader Coords
    :initarg :Coords
    :type (cl:vector object_detection-msg:GoalPos)
   :initform (cl:make-array 0 :element-type 'object_detection-msg:GoalPos :initial-element (cl:make-instance 'object_detection-msg:GoalPos))))
)

(cl:defclass GoalPositions (<GoalPositions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GoalPositions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GoalPositions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name object_detection-msg:<GoalPositions> is deprecated: use object_detection-msg:GoalPositions instead.")))

(cl:ensure-generic-function 'Coords-val :lambda-list '(m))
(cl:defmethod Coords-val ((m <GoalPositions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader object_detection-msg:Coords-val is deprecated.  Use object_detection-msg:Coords instead.")
  (Coords m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GoalPositions>) ostream)
  "Serializes a message object of type '<GoalPositions>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Coords))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Coords))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GoalPositions>) istream)
  "Deserializes a message object of type '<GoalPositions>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Coords) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Coords)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'object_detection-msg:GoalPos))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GoalPositions>)))
  "Returns string type for a message object of type '<GoalPositions>"
  "object_detection/GoalPositions")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GoalPositions)))
  "Returns string type for a message object of type 'GoalPositions"
  "object_detection/GoalPositions")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GoalPositions>)))
  "Returns md5sum for a message object of type '<GoalPositions>"
  "6e1cbfbf293ab70ab330ff223c5f1fcd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GoalPositions)))
  "Returns md5sum for a message object of type 'GoalPositions"
  "6e1cbfbf293ab70ab330ff223c5f1fcd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GoalPositions>)))
  "Returns full string definition for message of type '<GoalPositions>"
  (cl:format cl:nil "GoalPos[] Coords~%~%================================================================================~%MSG: object_detection/GoalPos~%float32 X~%float32 Y~%float32 Z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GoalPositions)))
  "Returns full string definition for message of type 'GoalPositions"
  (cl:format cl:nil "GoalPos[] Coords~%~%================================================================================~%MSG: object_detection/GoalPos~%float32 X~%float32 Y~%float32 Z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GoalPositions>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Coords) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GoalPositions>))
  "Converts a ROS message object to a list"
  (cl:list 'GoalPositions
    (cl:cons ':Coords (Coords msg))
))
