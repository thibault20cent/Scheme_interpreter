; TEST_RETURN_CODE=PASS
; TEST_COMMENT=char?

(char?)
(char? #\a)
(char? #\a #\b #\c #\d #\e #\f #\g #\h)
(define b #\a)
(char? b)
(char? 'b)
(char? ())
(char? "a")
(char? #t)
(char? '(#\a))
(char? 1.0)
