; TEST_RETURN_CODE=PASS
; TEST_COMMENT=quote define & set. define and set! must not assign value to symbol.

(quote (define a 9))
(quote (set! a 2))
