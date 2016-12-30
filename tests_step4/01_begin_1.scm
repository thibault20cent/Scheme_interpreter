; TEST_RETURN_CODE=PASS
; TEST_COMMENT=more complex begin form

(define x 8)
(if (> x 5) (begin (set! x 5) (* x x) ) (- x 5) )
x
(begin (set! x 2) (+ x 1))
x

