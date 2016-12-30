; TEST_RETURN_CODE=PASS
; TEST_COMMENT= complex set-cdr!

(define a '(8 ((2 3) (4 5))))
(set-cdr! a 7)
(set-cdr! a (* 2 3))
(set-cdr! a '(< 2 3))
(set-cdr! a (= 2 2))
