; TEST_RETURN_CODE=PASS
; TEST_COMMENT=and in and

(and (and 1 1) (and 1 1))
(and (and #f 1) (and 1 1))
(and (and 1 1) (and #f 1))
(and(and(and(and #f))))
(and(and(and(and #t))))