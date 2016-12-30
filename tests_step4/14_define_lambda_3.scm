; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= set! a lambda calcul

(define mul-by-2 (lambda (x) (* x 2)))
(mul-by-2 4)
(set! mul-by-2 (lambda (x) (* x 3)))
(mul-by-2 4)
(define mul-by-2 (lambda (x) (* x 4))