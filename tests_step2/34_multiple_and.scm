; TEST_RETURN_CODE=PASS
; TEST_COMMENT=multiple and

(and 1 2 3 4 5 6 7 8 9 10)
(and #t #t #t #t #t #t #t #t #t #t #t #t)
(and 1 2 3 4 5 6 7 8 9 10 #f)
(and 1 2 3 4 5 6 #f 7 8 9 10 )
(and #t #t #t #t #t #t #f #t #t #t #t)
(and #f #f #f #f #f #f #f #f #f #f #t)
(and #f #f #f #f #f #f #f #f #f #f #f)