## A quoi sert de redéfinir la méthode hashcode si la méthode equals a déjà été redéfinie ?

Par définition, si deux objets sont égaux ils doivent avoir le même hash. Donc s’ils n’ont pas le même hash, ils ne sont pas égaux. Voilà Pourquoi il faut redéfinire le hash. 