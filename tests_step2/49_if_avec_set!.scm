; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if avec define et set!

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(if #t (define a 8) #f)
a
(if #t (set! a 9) #f)
a
(if #f 3 (set! a 1))
a
