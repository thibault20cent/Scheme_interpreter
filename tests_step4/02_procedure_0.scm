; TEST_RETURN_CODE=PASS
; TEST_COMMENT=procedure?

(procedure? car)
(procedure? procedure?)
(procedure? car procedure? integer? null? float? string? symbol?)
(procedure? 1)
(procedure? car procedure? integer? null? float? string? symbol? 1)
(procedure? 'a)
(procedure? (lambda (x) (* x 2)))
(define mul-by-2 (lambda (x) (* x 2)))
(procedure? mul-by-2)