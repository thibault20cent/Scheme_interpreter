; TEST_RETURN_CODE=PASS
; TEST_COMMENT= simple set-car!

(set-cdr! '(1 2) 3)
(define l '(1 2))
(set-cdr! l 3)
