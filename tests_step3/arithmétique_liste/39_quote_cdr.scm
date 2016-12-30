; TEST_RETURN_CODE=PASS
; TEST_COMMENT= quote cdr

(cdr (quote (2 (quote (+ 1 2)) 3)))
