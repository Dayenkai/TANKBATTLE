Exe: Game

Game : Src/main.o Src/Output.o Src/convertchar.o Src/CPU.o Src/shoot.o Src/Special_Fonctions.o Src/data.o Src/IA.o
	cc -o Game Src/main.o Src/Output.o Src/convertchar.o Src/CPU.o Src/Special_Fonctions.o Src/shoot.o Src/data.o Src/IA.o -lncurses -Wall

main.o : Src/main.c Includes/Tank.h
	cc -c Src/main.c -lncurses
	
Output.o : Src/Output.c Src/data.c
	cc -c Src/Output.c -lncurses
	
data.o : Src/data.c
	cc -c Src/data.c -lncurses	
	
CPU.o : Src/CPU.c Src/shoot.c Src/IA.c
	cc -c Src/CPU.c -lncurses

shoot.o : Src/shoot.c
	cc -c Src/shoot.c -lncurses
	
IA.o : Src/IA.c
	cc -c Src/IA.c	-lncurses

clean :
	rm -rf Src/*o Src/*~ ./*~

