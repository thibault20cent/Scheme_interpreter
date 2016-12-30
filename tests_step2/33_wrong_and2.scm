; TEST_RETURN_CODE=FAIL
; TEST_COMMENT=another unbound variable in and

(define a 1)
(and a b)
