; TEST_RETURN_CODE=PASS
; TEST_COMMENT=string to symbol

(string->symbol "toto")
(define a "toto")
(string->symbol a)
a
