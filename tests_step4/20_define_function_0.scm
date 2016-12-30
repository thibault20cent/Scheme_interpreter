; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= define lambda calul, second way. x is unbound => FAIL

(define (mul-by-2 x) (* x 2))
mul-by-2
(mul-by-2 3)
(mul-by-2 4)
(mul-by-2 (mul-by-2 2))
x