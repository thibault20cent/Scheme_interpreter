; TEST_RETURN_CODE=PASS
; TEST_COMMENT=pair?

(pair?)
(pair? '(1))
(pair?  '(((((1))))) )
(pair? '(1) '("toto") '(#\c) '(#t) '(1.0) '(a) '(()))
(pair?  1 '(1) '("toto") '(#\c) '(#t) '(1.0) '(a) '(()))
(pair?  '(1) '("toto") '(#\c) '(#t) '(1.0) '(a) '(()) 1)
(define b '(1))
(pair? b)
(pair? 'b)
(pair? ())
(pair? "a")
(pair? #t)
(pair? 1.0)
