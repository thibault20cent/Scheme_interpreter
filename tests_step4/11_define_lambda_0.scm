; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= definition of lambda calul, first way. x is unbound.

(define mul-by-2 (lambda (x) (* x 2)))
mul-by-2
(mul-by-2 3)
(mul-by-2 4)
(mul-by-2 (mul-by-2 2))
x