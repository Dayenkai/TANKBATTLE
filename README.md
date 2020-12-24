# TANKBATTLE
#TANK BATTLE

#PROGRAMME DEVELOPPE EN C SOUS ENVIRONNEMENT UNIX
#2018/2019
#Authors : Bawilu-Mafuta Beker, 3A ESIEA PARIS
with Kamalakran Risan, 3A ESIEA PARIS


#TANK BATTLE est un jeu de tir du style des Shoot-Em-Up en 2D
#Le joueur incarne un tank, par lequel il doit se défendre et défendre un petit oisillon jaune en faisant face à des vagues de tanks ennemis 
#dans un territoire concu pour les escarmouches. Chaque vague fait apparaître différents types d'ennemis, 
#laissant le joueur face à une diversité d'agression, lequel devra s'adapter en disposant à sa guise de 
#plusieurs mode de tirs d'obus. Une fois les vagues détruites, le joueur accède au boss, lequel demeure
#la dernière passerelle afin de remporter la partie.


LANCEMENT DU PROGRAMME :

#./Game map Tank-Joueur Tank-ennemi

#Tout ce qui concerne le choix du terrain (map) se trouve dans le dossier "Map" du projet.
#Le design du tank du joueur est à choisir parmi les véhicules se trouvant dans le dossier "Tanks"


INDICATIONS/PROBLEMES :

#-> Le jeu utilise des caractères non alphanumériques de la table ascii, dont la plupart ne sont pas visible
#via l'encodage standard UTF-8. Il faut rendre donc un encodage de type "Occidental - IBM850" ou similaire dans les paramètres
#du terminal, la seule interface graphique du jeu.

#-> La taille de la map ne s'adapte pas à la taille de l'écran, il faut aller en full screen afin d'éviter les désagréables décalages d'objets. 

#-> L'apparition de quelques erreurs peuvent survenir du fait que certaines fonctions utilisent des librairies qui ne sont pas nécessairement installés.
Voici la liste des librairies à se procurer pour assurer un bon fonctionnement du jeu :

	Librairies sur Ubuntu-Debian :
		#- Ncurses (sudo apt-get install libncurses5-dev libncursesw5dev)
		#- Aplay (sudo apt-get install aplay)

#-> L'ennemi est pour l'instant indestructible, il y a des problèmes dans le programme, corrigés prochainement.
  #-> L'oisillon est de même indestructible, jusqu'à ce que le premier bug soit réglé.

#-> Lorsue le jeu est interrompu via un Ctrl+C, Ctrl+Z, la musique en arrière plan ne s'arrête pas en même temps que le processus.
   #ps -aux | grep "action_music.wav" permet de trouver le pid du process. Vous pouvez ensuite le terminer via un "kill -9 pid_du_process"

