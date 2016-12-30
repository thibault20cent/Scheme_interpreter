; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if_avec_or

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(define a #f)
(define b 8)
(if (or a b) (define c 2) (define d 6))
c
(if (or b #t) c 81)
(if (or b #f) c 156)
(if (or a #f) c 14)
(if (or a #f) 17 456)
(if (or b #t) 541 15)


