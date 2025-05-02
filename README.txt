ce dépôt est conçu pour compiler, calibrer, mesurer 
et optimiser les performances d'un programme ici c'est kernel.c ,
tout en fournissant des outils pour l'analyse approfondie des performances.
Il a été profiler avec mqao dons le contenue peut etre visible en cliquant sur le  fichier index.html .

Pour compiler la version originale : make OPT=NOOPT
Pour compiler la première version optimisée : make OPT=OPT1
Pour compiler la seconde version optimisée : make OPT=OPT2

Pour vérifier la sortie avec une taille 300 et l'enregistrer dans out.txt :
 ./check 300 out.txt

Pour calibrer avec une taille 300 le bon nombre de répétitions (max 100) de warmup à utiliser:
 ./calibrate 300 100

Pour mesurer avec une taille 300, 100 répétitions de warmup (lors de la première méta) et 30 répétitions de mesure :
 ./measure 300 100 30

Pour exécuter avec ce'²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²MAQAO :
maqao oneview -R1 -- ./measure 300 100 30
