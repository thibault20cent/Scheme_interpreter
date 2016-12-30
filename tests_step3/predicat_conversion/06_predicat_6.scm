; TEST_RETURN_CODE=PASS
; TEST_COMMENT=float?

(float?)
(float? 1.0)
(float? 1.)
(float? 1.0 1.1 1.2 1.3 21.4 1.5 1.6 1.7 1.8 1.9 2.0)
(float? 1 1.0 1.1 1.2 1.3 21.4 1.5 1.6 1.7 1.8 1.9 2.0)
(float? 1.0 1.1 1.2 1.3 21.4 1.5 1.6 1.7 1.8 1.9 2.0 1)
(define b 1.1)
(float? b)
(float? 'b)
(float? 1)
(float? ())
(float? "1.1")
(float? #t)
(float? '(1.1))
