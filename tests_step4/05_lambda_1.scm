; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= evaluation of lambda. x is unbound => FAIL

((lambda (x) (* x 2)) 2)
x
