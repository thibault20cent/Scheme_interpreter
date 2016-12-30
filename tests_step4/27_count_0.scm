; TEST_RETURN_CODE=PASS
; TEST_COMMENT= count

(define count ((lambda (total) (lambda (increment) (begin (set! total (+ total increment)) total))) 0))

(count 3)

(count 4)

(count 0)

(count -5)

(count "toto")