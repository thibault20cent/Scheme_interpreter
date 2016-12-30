; TEST_RETURN_CODE=PASS
; TEST_COMMENT=number to string

(number->string 1)
(number->string 0)
(number->string 123456789)
(number->string 1.345)
(number->string (+ 1 2))

