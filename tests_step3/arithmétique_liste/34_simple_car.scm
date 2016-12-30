; TEST_RETURN_CODE=PASS
; TEST_COMMENT= simple car

(car (quote (1 2)))
(car (quote ((1 2) 2)))
(define a 8)
(car (quote (a 2)))
(car (quote (((2 3) a) 8 9 6 21 5)))
