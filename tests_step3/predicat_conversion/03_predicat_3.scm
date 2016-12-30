; TEST_RETURN_CODE=PASS
; TEST_COMMENT=symbol?

(symbol?)
(symbol? 'a)
(symbol? 'a 'b 'c 'd 'e 'f 'g 'h)
(symbol? 'azertyuiopqsdfghjklm)
(define a 'b)
(symbol? a)
(symbol? 'b)
(symbol? ())
(symbol? "a")
(symbol? #\a)
(symbol? '(a))
(symbol? 1.0)
