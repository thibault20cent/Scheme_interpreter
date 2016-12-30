# Scheme_interpreter

Vincent MEURISSE & Thibault VINCENT. SICOM A.

Code de l'interpréteur Scheme à la fin de l’incrément 4 du projet info PHELMA.

Ce code fonctionne aussi bien en mode interactif qu'en mode script. 

Le répertoire est organisé ainsi : 
- Makefile pour compiler soit en mode debug (afficher les traces du programme) soit en mode release (produit final)
- src : qui contient le code C de l’interpréteur. 
- include : qui contient toutes les définitions de types et prototypes du programme.
- tests_step4 : tests du code de l’incrément 4.

--- pour compiler le code en mode debug (il créé l'exécutable 'scheme')
$ make debug 

--- pour le lancer en mode interactif 
$ ./scheme

--- pour le lancer en mode script 
$ ./scheme monFichier.scm

--- !!!IMPORTANT!!!: pour lancer le programme de test sur l'ensemble des fichiers de tests de l’incrément 4 en mode batch 
$ simpleUnitTest.sh -b -e ./scheme tests_step4/*.scm
