#include "../Includes/Tank.h"

void	Intro()
{
	char	key;

	while (1)
	{
	if ((key = key_pressed()) == 10)
			break;
	clear_screen();
	printf("Press enter to skip the intro");
	print_line_jump(18);
	if ((key = key_pressed()) == 10)
			break;
	system("printf '                                                                                WELCOME'; sleep 2"); clear_screen();
	if ((key = key_pressed()) == 10)
			break;
	printf("Press enter to skip the intro");
	print_line_jump(18);
	if ((key = key_pressed()) == 10)
			break;
	system("printf '                                                                           BE THE WITNESS...'; sleep 2"); clear_screen();
	if ((key = key_pressed()) == 10)
		break;
	printf("Press enter to skip the intro");
	print_line_jump(18);
	if ((key = key_pressed()) == 10)
			break;
	system("printf '                                                                        OF THE DARKEST CONFLICT'; sleep 2"); clear_screen();
	if ((key = key_pressed()) == 10)
			break;
	printf("Press enter to skip the intro");
	print_line_jump(18);
	if ((key = key_pressed()) == 10)
			break;
	system("printf \"                                                                    IN THE WHOLE HUMANITY'S STORY\"; sleep 2"); clear_screen();
	if ((key = key_pressed()) == 10)
			break;
	printf("Press enter to skip the intro");
	print_line_jump(18);
	if ((key = key_pressed()) == 10)
			break;
	system("printf '                                                                               BE READY'; sleep 1.5");
	if ((key = key_pressed()) == 10)
			break;
	system("aplay -q Sounds/Bossu.wav &");
	if ((key = key_pressed()) == 10)
			break;
	print_line_jump(2);
	system("printf '                                                                               F' ; sleep 0.8 ; printf 'O'; sleep 1; printf 'R'");
	if ((key = key_pressed()) == 10)
			break;
	system("printf \"\033[31m\"; sleep 1.05 ; printf ' W'; sleep 0.9; printf 'A'; sleep 0.5 ; printf 'R'; sleep 2; printf \"\033[37m\"");
	if ((key = key_pressed()) == 10)
			break;
	white_mode();
	break;
	}
}

void	Generic_Menu() // La fonction affiche simplement le menu sans aucun mode sélectionné au préalable
{
	clear_screen();
	printf("Appuyer sur q pour quitter ; i et k pour haut et bas");
	gotoxy(18, 79);
	printf("Easy Mode\n\n"); gotoxy(20, 79); printf("Hell Mode\n\n");
}

void	Menu_Mode_Selected(int i) // La fonction affiche simplement le menu dépendant du mode sélectionné
{
	clear_screen();
	white_mode();
	printf("Appuyer sur q pour quitter ; i et k pour haut et bas");
	gotoxy(18, 79);
	if (i == 1)
		{
 			white_mode();
 		}
	else if (i == 0)
		red_mode();
	printf("Easy Mode\n\n"); gotoxy(20, 79); 
	if (i == 1)
		{
			red_mode();
		}
	else if (i == 0)
		white_mode();
	printf("Hell Mode\n\n");
	white_mode();
	gotoxy(21, 84);
}

void	Menu_Exit_Game() // Un simple message annonçant au joueur qu'il quitte le jeu, le programme mettant ensuite un terme à son execution.
{
	clear_screen();
	gotoxy(18,79); white_mode(); printf("SEE YOU SOON :(\n\n"); system("sleep 2"); clear_screen();
	exit(0);
}

char print_converted(char **tab, int width)
{
	int i;
	int j;
	
	for (i=0; i<width; i++)
		{
			j = 0;
		while (tab[i][j] != '\0')
			{
				switch(tab[i][j])
					{
						case 65:
							green_mode();printf("%c", 35);white_mode();
							break;
						case 105:
							printf("%c", 179);
							break;
						case 45:
							printf("%c", 196);
							break;
						case 66:
							printf("%c", 177);
							break;
						case 82:
							red_mode();printf("%c", 178);white_mode();
							break;
						case 76:
							cyan_mode();printf("%c", 219);white_mode();
							break;
						case 'e':
							printf("%c", 218);
							break;
						case 'z':
							printf("%c", 192);
							break;
						case 'k':
							printf("%c", 217);
							break;
						case 'r':
							printf("%c", 191);
							break;
						case 'c':
							printf("%c", 193);
							break;
						default :
							if (i == 30 && j == 82)
								{
									yellow_mode();printf("%c", tab[i][j]);white_mode();
								}
							else
								printf("%c", tab[i][j]);
							break;
					}
				j++;
			}
			printf("\n");
		}
}

void	print_tab(char **tab, int width)
{
	int	x;
	
	for(x = 0; x < width; x++)
		printf("%s\n", tab[x]);
}

void	error_opening_file_message()
{
	printf("\n");
	printf("Impossible d'ouvrir la Map et/ou les Tanks du Jeu :(...\n");
	printf("Veuillez verifiez le(s) fichier(s) le(s) contenant, ayant tous bien été mis au préalable en paramètre vis-à-vis de l'executable selon l'ordre suivant");
	printf(" :\n\nSyntaxe : [.../Game] [MAP] [FILE_tab_TANK] [FILE_ENNEMY_TANK]\n\n");
	printf(" (Si oui, verifiez les droits d'ouverture et de lecture du ou des fichiers en question, de même si il(s) existent bel et bien !)\n\n");
	Init_Term();
	exit(0);
}

void	Menu() //Voici la fonction qui gère l'affichage du choix de mode de jeu, et reçoit la confirmation venant de l'utilisateur
{	
	char	key;
	int	mode = -1;
	
	Intro();//Pas obligatoire, juste histoire de hype l'utilisateur !
	Generic_Menu();
	while (1)
	{
		key = key_pressed_blocked();
		switch(key)
			{
				case 'i':
								Menu_Mode_Selected(0); mode = 0;
								system("aplay -q Sounds/Silent_Hill_Select.wav &");
				break;
				case 'k':
								Menu_Mode_Selected(1); mode = 1;
								system("aplay -q Sounds/Silent_Hill_Select_2.wav &");
				break;
				case '\n':
								if (mode == 0)
									{
										system("aplay -q Sounds/Silent_Hill_Select_Sound_3.wav &");
										Get_Data();
									} //C'est à partie de cette fonction que le stockage des données des tanks, map etc se fera, ainsi que le lancement du jeu
								else if (mode == 1)
									{
										//Menu_Mode_Selected(1);
										gotoxy(22, 64); white_mode(); printf("\033[37mShowing mode only, Update soon Incoming !\n\n");
									}
				break;
				case	'q':
								Menu_Exit_Game();
			}
	}
}

void	Defeat_Announce()
{
									clear_screen();
	print_line_jump(18);
	
	system("printf '                                                                                YOU HAVE FAILED' ; sleep 2");
	system("clear");
	print_line_jump(18);
	system("printf '                                                                          MISSION IS A COMPLETE FAILURE...' ; sleep 2");
	system("clear");
	print_line_jump(18);
	red_mode();
	system("printf '                                                                                   GAME OVER' ; sleep 2");
	white_mode();
	system("clear");
}

void	Init_Term()
{
	system("stty echo");
	system("setterm -cursor on");
}

void	Set_off_Term()
{
	system("stty -echo");
	system("setterm -cursor off");	
}
