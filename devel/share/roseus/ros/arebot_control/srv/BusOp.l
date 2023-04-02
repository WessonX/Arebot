;; Auto-generated. Do not edit!


(when (boundp 'arebot_control::BusOp)
  (if (not (find-package "AREBOT_CONTROL"))
    (make-package "AREBOT_CONTROL"))
  (shadow 'BusOp (find-package "AREBOT_CONTROL")))
(unless (find-package "AREBOT_CONTROL::BUSOP")
  (make-package "AREBOT_CONTROL::BUSOP"))
(unless (find-package "AREBOT_CONTROL::BUSOPREQUEST")
  (make-package "AREBOT_CONTROL::BUSOPREQUEST"))
(unless (find-package "AREBOT_CONTROL::BUSOPRESPONSE")
  (make-package "AREBOT_CONTROL::BUSOPRESPONSE"))

(in-package "ROS")





(defclass arebot_control::BusOpRequest
  :super ros::object
  :slots (_bus_id _recv_len _data ))

(defmethod arebot_control::BusOpRequest
  (:init
   (&key
    ((:bus_id __bus_id) 0)
    ((:recv_len __recv_len) 0)
    ((:data __data) (make-array 0 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _bus_id (round __bus_id))
   (setq _recv_len (round __recv_len))
   (setq _data __data)
   self)
  (:bus_id
   (&optional __bus_id)
   (if __bus_id (setq _bus_id __bus_id)) _bus_id)
  (:recv_len
   (&optional __recv_len)
   (if __recv_len (setq _recv_len __recv_len)) _recv_len)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint8 _bus_id
    1
    ;; uint8 _recv_len
    1
    ;; uint8[] _data
    (* 1    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _bus_id
       (write-byte _bus_id s)
     ;; uint8 _recv_len
       (write-byte _recv_len s)
     ;; uint8[] _data
     (write-long (length _data) s)
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _bus_id
     (setq _bus_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _recv_len
     (setq _recv_len (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[] _data
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _data (make-array n :element-type :char))
     (replace _data buf :start2 ptr-) (incf ptr- n))
   ;;
   self)
  )

(defclass arebot_control::BusOpResponse
  :super ros::object
  :slots (_data ))

(defmethod arebot_control::BusOpResponse
  (:init
   (&key
    ((:data __data) (make-array 0 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _data __data)
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint8[] _data
    (* 1    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8[] _data
     (write-long (length _data) s)
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8[] _data
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _data (make-array n :element-type :char))
     (replace _data buf :start2 ptr-) (incf ptr- n))
   ;;
   self)
  )

(defclass arebot_control::BusOp
  :super ros::object
  :slots ())

(setf (get arebot_control::BusOp :md5sum-) "f42be7da85859f0e278c64aea47889c1")
(setf (get arebot_control::BusOp :datatype-) "arebot_control/BusOp")
(setf (get arebot_control::BusOp :request) arebot_control::BusOpRequest)
(setf (get arebot_control::BusOp :response) arebot_control::BusOpResponse)

(defmethod arebot_control::BusOpRequest
  (:response () (instance arebot_control::BusOpResponse :init)))

(setf (get arebot_control::BusOpRequest :md5sum-) "f42be7da85859f0e278c64aea47889c1")
(setf (get arebot_control::BusOpRequest :datatype-) "arebot_control/BusOpRequest")
(setf (get arebot_control::BusOpRequest :definition-)
      "uint8 bus_id
uint8 recv_len
uint8[] data
---
uint8[] data
")

(setf (get arebot_control::BusOpResponse :md5sum-) "f42be7da85859f0e278c64aea47889c1")
(setf (get arebot_control::BusOpResponse :datatype-) "arebot_control/BusOpResponse")
(setf (get arebot_control::BusOpResponse :definition-)
      "uint8 bus_id
uint8 recv_len
uint8[] data
---
uint8[] data
")



(provide :arebot_control/BusOp "f42be7da85859f0e278c64aea47889c1")


