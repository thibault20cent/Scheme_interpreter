; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if avec and

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(define a #f)
(define b 8)
(if (and a b) (define c 2) (define d 6))
d
(if (and b #t) d 45)
(if (and b #f) d 48)
(if (and b #f) 45 a)
(if (and b #t) 45 23)
(if b (and d a) 8)
(if a 8 (and d b))


