; TEST_RETURN_CODE=PASS
; TEST_COMMENT= define lambda with an already defined lambda

(define (mul-by-2 x) (* x 2))
(define (mul-by-4 x) (mul-by-2 (mul-by-2 x)))
(mul-by-4 5)