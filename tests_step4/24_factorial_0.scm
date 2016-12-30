; TEST_RETURN_CODE=PASS
; TEST_COMMENT= factorial

(define factorial (lambda (n) (if (= n 0) 1 (* n (factorial (- n 1))))))

(factorial 0)

(factorial 1)

(factorial 4)

(factorial 5)

(factorial 10)