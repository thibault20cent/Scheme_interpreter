; TEST_RETURN_CODE=PASS
; TEST_COMMENT= simple cdr

(cdr (quote (1 2)))
(cdr (quote (2 (1 2))))
(define a 8)
(cdr (quote (2 a)))
(cdr (quote (8 ((2 3) a))))
(cdr (quote (1 2 3 4 5 6 7 8 9)))
