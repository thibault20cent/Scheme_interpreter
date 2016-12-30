; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= let form. x is unbound => FAIL

(let ((x 3)) (* x 2))
x