; TEST_RETURN_CODE=PASS
; TEST_COMMENT= arithmetic cdr

(cdr (quote (3 (+ 1 2))))
(cdr (quote (5 ((* 2 5) (- 9 8)))))
