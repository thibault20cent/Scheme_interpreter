; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= definiton of lambda calul, first way. multiple arguments

(define mul (lambda (x y z) (* x y z)))
(mul 2 3 4)
(mul 3)