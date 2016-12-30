; TEST_RETURN_CODE=PASS
; TEST_COMMENT= or in or

(or (or 1 1) (or 1 1))
(or (or #f #f) (or #f #f))
(or (or 1 1) (or #f #f))
(or(or(or(or #f))))
(or(or(or(or #t))))