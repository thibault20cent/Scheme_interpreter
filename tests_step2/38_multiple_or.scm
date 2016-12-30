; TEST_RETURN_CODE=PASS
; TEST_COMMENT=multiple or

(or 1 2 3 4 5 6 7 8 9 10)
(or #f #f #f #f #f #f #f #f #f #f #f #f)
(or 1 2 3 4 5 6 7 8 9 10 #f)
(or 1 2 3 4 5 6 #f 7 8 9 10 )
(or #f #f #f #f #f #f #f #f #f #f #t)