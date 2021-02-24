# TANKBATTLE
PROGRAMME DEVELOPED IN C - UNIX ENVIRONMENT

2018/2019

Authors : Bawilu-Mafuta Beker, 3A ESIEA PARIS
with Kamalakaran Risan, 3A ESIEA PARIS

TANK BATTLE is a Shoot-Em-Up 2D game, only playable through a terminal.
You play a tank, your own way by wich one you must protect a little bird and defend yourself against various ennemies, planning attacks in waves, 
in a map designed for skirmishes to happen, thus you get to have throughout the story mode different shooting modes.
Once the waves cleared, you'll access a boss, the last obstacle to get over to win the game.


# GAME LAUNCHING

./Game map Tank-Joueur Tank-ennemi

Every maps are in the "Map" folder of the project.
Your Tank appearance is in the "Tanks" folder, you do have the choice to change on your own preference.


# INDICATIONS/BUGS :

-> The characters used are non-alphanumeric. You might use a predefined encoding that would not allow to print them correctly, the default encoding being UTF-8.
You have to change it by switching into the "Occidental - IBM850" encoding, or a similar one in the terminal parameters.

-> The map size doesn't adjust to the screen, in consequence, you should always go to full screen to avoid some disturbing offsets.

-> Some error can appear due to game functions that use uninstalled libraries in your system. 
Here are the libraries that you might not have, necessary to make the game work :

	Libraries - Ubuntu-Debian :
		#- Ncurses (sudo apt-get install libncurses5-dev libncursesw5dev)
		#- Aplay (sudo apt-get install aplay)

-> Unfortunately, the ennemies and the yellow bird somehow are undestructible, I am looking forward to fixing it.

-> If you try to interrupt the game while playing it, with Ctrl+C or Ctrl+Z, the background music could probably not follow the kill process.
   ps -aux | grep "action_music.wav" will find the process after what, and you can kill it with the unix command "kill -9 pid_du_process"
   
UPDATE + FIX SOON !

