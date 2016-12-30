; TEST_RETURN_CODE=PASS
; TEST_COMMENT=null?

(null? ())
(null? () () ())
(null?)
(define a ())
(null? a)
(null? () () () () () () () () () () () () () () () () () () ())
(null? 0)
(null? () () () 1)
(null?  1 () () ())
(null?  ()  1 () ())
(null?  1 1 1 1)
(null?  () () () () () () () () () () () () () () () () () () 1)
