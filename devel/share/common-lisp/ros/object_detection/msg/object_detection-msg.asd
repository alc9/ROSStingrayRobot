
(cl:in-package :asdf)

(defsystem "object_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GoalPos" :depends-on ("_package_GoalPos"))
    (:file "_package_GoalPos" :depends-on ("_package"))
    (:file "GoalPositions" :depends-on ("_package_GoalPositions"))
    (:file "_package_GoalPositions" :depends-on ("_package"))
  ))