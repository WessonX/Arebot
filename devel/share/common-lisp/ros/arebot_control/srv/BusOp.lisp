; Auto-generated. Do not edit!


(cl:in-package arebot_control-srv)


;//! \htmlinclude BusOp-request.msg.html

(cl:defclass <BusOp-request> (roslisp-msg-protocol:ros-message)
  ((bus_id
    :reader bus_id
    :initarg :bus_id
    :type cl:fixnum
    :initform 0)
   (recv_len
    :reader recv_len
    :initarg :recv_len
    :type cl:fixnum
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass BusOp-request (<BusOp-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BusOp-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BusOp-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arebot_control-srv:<BusOp-request> is deprecated: use arebot_control-srv:BusOp-request instead.")))

(cl:ensure-generic-function 'bus_id-val :lambda-list '(m))
(cl:defmethod bus_id-val ((m <BusOp-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arebot_control-srv:bus_id-val is deprecated.  Use arebot_control-srv:bus_id instead.")
  (bus_id m))

(cl:ensure-generic-function 'recv_len-val :lambda-list '(m))
(cl:defmethod recv_len-val ((m <BusOp-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arebot_control-srv:recv_len-val is deprecated.  Use arebot_control-srv:recv_len instead.")
  (recv_len m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <BusOp-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arebot_control-srv:data-val is deprecated.  Use arebot_control-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BusOp-request>) ostream)
  "Serializes a message object of type '<BusOp-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bus_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'recv_len)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BusOp-request>) istream)
  "Deserializes a message object of type '<BusOp-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bus_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'recv_len)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BusOp-request>)))
  "Returns string type for a service object of type '<BusOp-request>"
  "arebot_control/BusOpRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BusOp-request)))
  "Returns string type for a service object of type 'BusOp-request"
  "arebot_control/BusOpRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BusOp-request>)))
  "Returns md5sum for a message object of type '<BusOp-request>"
  "f42be7da85859f0e278c64aea47889c1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BusOp-request)))
  "Returns md5sum for a message object of type 'BusOp-request"
  "f42be7da85859f0e278c64aea47889c1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BusOp-request>)))
  "Returns full string definition for message of type '<BusOp-request>"
  (cl:format cl:nil "uint8 bus_id~%uint8 recv_len~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BusOp-request)))
  "Returns full string definition for message of type 'BusOp-request"
  (cl:format cl:nil "uint8 bus_id~%uint8 recv_len~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BusOp-request>))
  (cl:+ 0
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BusOp-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BusOp-request
    (cl:cons ':bus_id (bus_id msg))
    (cl:cons ':recv_len (recv_len msg))
    (cl:cons ':data (data msg))
))
;//! \htmlinclude BusOp-response.msg.html

(cl:defclass <BusOp-response> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass BusOp-response (<BusOp-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BusOp-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BusOp-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arebot_control-srv:<BusOp-response> is deprecated: use arebot_control-srv:BusOp-response instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <BusOp-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arebot_control-srv:data-val is deprecated.  Use arebot_control-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BusOp-response>) ostream)
  "Serializes a message object of type '<BusOp-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BusOp-response>) istream)
  "Deserializes a message object of type '<BusOp-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BusOp-response>)))
  "Returns string type for a service object of type '<BusOp-response>"
  "arebot_control/BusOpResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BusOp-response)))
  "Returns string type for a service object of type 'BusOp-response"
  "arebot_control/BusOpResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BusOp-response>)))
  "Returns md5sum for a message object of type '<BusOp-response>"
  "f42be7da85859f0e278c64aea47889c1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BusOp-response)))
  "Returns md5sum for a message object of type 'BusOp-response"
  "f42be7da85859f0e278c64aea47889c1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BusOp-response>)))
  "Returns full string definition for message of type '<BusOp-response>"
  (cl:format cl:nil "uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BusOp-response)))
  "Returns full string definition for message of type 'BusOp-response"
  (cl:format cl:nil "uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BusOp-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BusOp-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BusOp-response
    (cl:cons ':data (data msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BusOp)))
  'BusOp-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BusOp)))
  'BusOp-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BusOp)))
  "Returns string type for a service object of type '<BusOp>"
  "arebot_control/BusOp")