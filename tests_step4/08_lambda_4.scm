; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= lambda with multiple variables. Wrong number of arguments

((lambda (x y) (* x y z)) 1 2)
