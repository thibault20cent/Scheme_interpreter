; TEST_RETURN_CODE=PASS
; TEST_COMMENT= string to number

(string->number "1")
(string->number "123456789")
(define a "1")
(string->number a)
a
(string->number "12345 toto")
