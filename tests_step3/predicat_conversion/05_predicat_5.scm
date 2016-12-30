; TEST_RETURN_CODE=PASS
; TEST_COMMENT=string?

(string?)
(string? "toto")
(string? "toto" "tata" "titi" "tutu" "tete")
(string? "toto" "tata" "titi" "tutu" "tete" 1)
(string?  1 "toto" "tata" "titi" "tutu" "tete")
(string? 1 1 1 1 1 1 1 )
(string? "azertyuiopqsdfghjklm")
(define a "toto")
(string? a)
(string? 'a)
(string? ())
(string? #\c)
(string? #t)
(string? '("toto"))
(string? 1.0)
