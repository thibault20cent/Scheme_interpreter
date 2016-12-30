; TEST_RETURN_CODE=PASS
; TEST_COMMENT= simple set-car!

(set-car! '(1 2) 3)
(define l '(1 2))
(set-car! l 3)
