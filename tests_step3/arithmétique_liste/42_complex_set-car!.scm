; TEST_RETURN_CODE=PASS
; TEST_COMMENT= complex set-car!

(define a '(((2 3) (4 5)) 8))
(set-car! a 7)
(set-car! a (* 2 3))
(set-car! a '(< 2 3))
(set-car! a (= 2 2))
