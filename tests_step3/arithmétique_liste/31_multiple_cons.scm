; TEST_RETURN_CODE=PASS
; TEST_COMMENT= multiple cons 

(cons 1 (cons 2 ()))
(cons 1 (cons 2 (cons 3 ())))
(cons 1 (cons 2 (cons 3 (cons 4 ()))))
