; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if avec quote

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(define a 1)
(define b 2)
(if b (quote (1 3)) 78)
(quote (if a 3 4))
(if #f a (quote (if a 3)))




