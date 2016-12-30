; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= increment unbound

(define count ((lambda (total) (lambda (increment) (begin (set! total (+ total increment)) total))) 0))
increment