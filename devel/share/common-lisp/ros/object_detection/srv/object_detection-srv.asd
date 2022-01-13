
(cl:in-package :asdf)

(defsystem "object_detection-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :object_detection-msg
)
  :components ((:file "_package")
    (:file "Localization" :depends-on ("_package_Localization"))
    (:file "_package_Localization" :depends-on ("_package"))
  ))