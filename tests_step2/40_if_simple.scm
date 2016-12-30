; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if simple

; RAPPEL SYNTAXE : (if predicat consequence alternative)

(define a -4)
(define b 6)
(if 651981 a b)
(if 32 (define c 6) -78)
c
(if #t 78 8)
(if #f a b)
