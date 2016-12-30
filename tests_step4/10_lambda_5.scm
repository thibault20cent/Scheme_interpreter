; TEST_RETURN_CODE=PASS
; TEST_COMMENT= lambda with multiple variables. Wrong number of arguments

((lambda (x y z) (* x y)) 1 2 3)
