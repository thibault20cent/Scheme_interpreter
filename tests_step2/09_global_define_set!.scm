; TEST_RETURN_CODE=PASS
; TEST_COMMENT=define & set v2

(define a 1)
a
(set! a "toto")
a
(define b "tata")
b
(set! b 1)
b
(set! b a)
b
(define c 2)
(set! c 'symbol)
a
b
c
