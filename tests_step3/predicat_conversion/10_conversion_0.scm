; TEST_RETURN_CODE=PASS
; TEST_COMMENT= char to int. Résultats vérifiés avec la table ASCII

(char->integer #\a)
(char->integer #\1)
(char->integer #\?)
(char->integer #\newline)
(char->integer #\space)
(define c #\b)
(char->integer c)
c
