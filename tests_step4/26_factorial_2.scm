; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= factorial with wrong number of arguments

(define factorial (lambda (n) (if (= n 0) 1 (* n (factorial (- n 1))))))

(factorial)
