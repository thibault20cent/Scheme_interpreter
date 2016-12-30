; TEST_RETURN_CODE=PASS
; TEST_COMMENT=boolean?

(boolean?)
(boolean? #t)
(boolean? #f)
(boolean? #f #f #f #f #t #t #t #t)
(define a #t)
(boolean? a)
(boolean? (integer? 1))
(boolean? (null? 1))
(boolean? ())
(boolean? "toto")
(boolean? "#t")
(boolean? #\c)
(boolean? 1.0)
(boolean? 'b)
