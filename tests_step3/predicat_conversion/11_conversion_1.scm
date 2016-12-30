; TEST_RETURN_CODE=PASS
; TEST_COMMENT=integer to char

(integer->char 97)
(integer->char 10)
(integer->char 32)
(integer->char 123456788)
(define i 98)
(integer->char i)
i
