; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= define lambda with an already defined lambda

(define mul-by-2 (lambda (x)(* x 2)))
(define mul-by-4 (lambda (x) (mul-by-2 x)))
(mul-by-4 2)
x