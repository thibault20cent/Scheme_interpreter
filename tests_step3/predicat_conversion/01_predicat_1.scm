; TEST_RETURN_CODE=PASS
; TEST_COMMENT=integer?

(integer?)
(integer? 1)
(integer? 1 2 3 4 5 6 7 8 9 10 11 12)
(define a 1)
(integer? a)
(integer? ())
(integer? "toto")
(integer? "1")
(integer? #t)
(integer? #\c)
(integer? #\1)
(integer? 1.0)
(integer? #t)
