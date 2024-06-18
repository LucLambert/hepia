########## Air Autism : The Fast Airbender ##########

#### Projet réalisé par : Andrey Vincent, Faisandel Florent, Lambert luc, Montandon Philippe ####

#### Composition du projet #### 
4 scripts python : boot.py, player1.py, player2.py, server.py
1 librairie : LIS2HH12.py
plusieurs assets: images, sounds
1 hotspot sur un smartphone pour avoir un wifi
2 pysenses munies de lopy4
1 ordinateur qui sert de serveur

#### Comment cela fonctionne-t-il ? ####
Le serveur utilise des sockets pour la connection avec les manettes. Il attend deux connexions
Les manettes utilisent deux scripts et une librairie : "boot.py" afin de se connecter au wifi, "player1.py" ou "player2.py" selon la manette et la librairie LIS2HH12.py
player1.py et player2.py récupèrent la valeur de l'axe z de l'accélérometre (à travers la carte) et envoie un message "ping1" ou "ping2" au serveur si la valeur de z
est plus grande que 3
Le principe du jeu est de déplacer le ballon se trouvant au centre dans le côté adverse en secouant la pysense
Lorsque le jeu est lancé, si le serveur reçoit le message "ping1" le ballon se déplace sur la droite et sur la gauche si "ping2"
Le premier joueur qui arrive à 5 pts gagne la partie

#### Marche a suivre ####
-Faire un wifi avec comme nom "Airbender" et comme mot de passe "akwt6871" ou bien changer cela dans "boot.py"
-Se connecter au wifi sur l'ordinateur qui sert de serveur
-Changer l'ip dans "player1.py" et "player2.py" par l'ip de l'ordinateur 
-Upload "boot.py", "LIS2HH12,py" et "player1.py" renommé en "main.py" sur la première pysense ainsi que la même chose mais "player2.py" renommé en "main.py" sur la deuxième
-Lancer "serveur.py" sur l'ordinateur
-Reboot les manettes
-Enjoy

########## 10/09/2021 - v 0.0.1 ########## 
