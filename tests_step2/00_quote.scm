; TEST_RETURN_CODE=PASS
; TEST_COMMENT=basic quote

(quote a)
'a
(quote (* a (+ 4 5)))
'(* a (+ 4 5))
