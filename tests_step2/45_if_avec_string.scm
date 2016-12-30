; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if avec string

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(define a 3)
(if #t "salut" "hello")
(if #f "bonjour" "yo")
(if #t "a" "hey")
(if #t "b" "hi")




