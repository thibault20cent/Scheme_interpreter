; TEST_RETURN_CODE=PASS
; TEST_COMMENT=symbol to string

(symbol->string 'toto)
(define a 'symbol)
(symbol->string a)
a
