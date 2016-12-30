; TEST_RETURN_CODE=PASS
; TEST_COMMENT= multiple cons 

(define a 2)
(define b 8)
(cons a (cons 2 ()))
(cons (+ 1 2) (cons b (cons (+ a 1) ())))
