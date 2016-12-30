; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= map form

(define (mul-by-2 x) (* 2 x))

(define (map proc items)
(if (null? items)
'()
(cons (proc (car items))
(map proc (cdr items)))))

(map mul-by-2 ’(0 1 2 3))
