; TEST_RETURN_CODE=PASS
; TEST_COMMENT= predicat in argument of predicat, arithmetique in predicat

(integer? null?)
(null? integer?)
(integer? (+ 1 2))
(integer? '(+ 1 2))
(pair? (+ 1 2))
(pair? '(+ 1 2))