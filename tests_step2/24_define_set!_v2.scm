; TEST_RETURN_CODE=PASS
; TEST_COMMENT= define and set

(define a 1)
(define b 2)
(define c "toto")
(define d #\z)
(define e #t)
(set! a "toto")
a
(set! b #\y)
b
(set! c 3)
c
(set! d #f)
d
(set! e "tata")
e
(set! a 12345678)
a
(set! b "blablabla")
b
(set! c #t)
c
(set! d #\u)
d
(set! e 1)
e