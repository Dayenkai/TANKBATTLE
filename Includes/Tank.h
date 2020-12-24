#ifndef HARAKIRI
#define HARAKIRI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <ncurses.h>
#include	<termios.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<linux/keyboard.h>

#define	clear_screen()	printf("\033[H\033[J")
#define	gotoxy(x,y)		printf("\033[%d;%dH", (x), (y))
#define	white_mode()	printf("\033[37m");
#define	red_mode()		printf("\033[31m");
#define	cyan_mode()		printf("\033[36m");
#define	yellow_mode()	printf("\033[33m");
#define	green_mode()	printf("\033[32m");

typedef struct Tank TANK;
typedef struct OBUS OBUS;
typedef struct Piou_Piou PIOUPIOU;
typedef struct MAP MAP;
typedef struct BODY BODY;
typedef	struct PATH	PATH;

struct PATH
{
	int x;
	int y;
	PATH *Next_Case;
};

struct BODY
{
	char **Tab;
	int	size_x;
	int	size_y;
	int 	cannon_pos_x;
	int 	cannon_pos_y;
	BODY 	*Next_Body;
};

struct OBUS
{
	int	previous_x;
	int	previous_y;
	int	x;
	int	y;
	int	type;
	int	time;
	int	ally_or_ennemy;
	char	direction;
	OBUS	*Obus_suivant;
};

struct Tank
{
	BODY 	*Actual_Body;
	int who;
	int ally_or_ennemy;
	int direction;
	int type;
	int pos_x;
	int pos_y;
	int new_x;
	int new_y;
	OBUS *Obus_suivant;
	TANK *Next_Ennemy;
	TANK *Next_Player;
	int previous_error_movement;
	int Time_Move;
	int Time_shoot;
	int Previous_Body_Number;
	int Moving_State;
	int Firing_State;
	int Life;
};

struct Piou_Piou
{
	char	Body;
	int 	x;
	int 	y;
	int	Move_State;
	int	Life;
};

struct MAP
{
	char **Tab;
	int x;
	int y;
};

/* Prototype fonctions*/

/* GENERIC OUTPUT FUNCTIONS - La plupart dans output.c */

void	Intro();
void	Generic_Menu();
void	Menu();
void	Menu_mode_selected(int mode);
void	Menu_Exit_Game();
void	error_opening_file_message();
void	print_tab(char **tab, int width);
char 	print_converted(char **tab, int width);
void	print_line_jump(int n);
void	Defeat_Announce();

/* DATA CREATION/PREPARATION and MEMORY ALLOCATION FUNCTIONS- In data.c */

void	Get_Data();
void	Open_File(char *str, FILE **file);
void	File_Open(char *str, FILE **file);
void	Get_Map_Info(MAP *map, FILE **file);
void	Find_Size_Map(MAP *map, FILE **file);
void	Alloc_Tab(char ***tab, int width, int length);
void	Alloc_Tank(char ***str, int x, int y);
void	Copy_Map_to_Tab(MAP *map, FILE **file);
void	Copy_Chars_To_Tabs(BODY *tank, FILE **tank_file, int size_x, int size_y, int size_xprime, int size_yprime, int type);
void	Copy_Chars_To_Tabs_One_Side(BODY *tank, FILE **tank_file, int size_x, int size_y, int Number, int type) ;
BODY	*BODY_Change(BODY *Body, int i);
char 	convert(MAP map);
int		my_strlen(char str);

/* GAME MANAGEMENT Functions */
void	Game_Master(char **str);
void	Orchestra_Chief(BODY *Body,MAP *map);

void	what_who_got_shot(OBUS *Obus, MAP *map, TANK *tank, TANK *Previous, PIOUPIOU *piou);
int		check_who_got_shot(OBUS *Obus, MAP *map, TANK *tank, PIOUPIOU *piou, TANK *shooter);
void	create_obus(TANK	*tank, int x, int y, int Carrosserie_Number, int which_side, int type, MAP *map);
void	Add_Obus(TANK *tank, int x, int y, char c, int which_side, int type, MAP *map);
void	Erase_Obus(OBUS *element, OBUS *previous,TANK *tank);
void	check_obus(MAP *map,TANK *tank, TANK *list_tank, PIOUPIOU *Piou);

void	Calculate_new_pos(TANK *tab, MAP *map,BODY *Body);
int  	pass_or_not(TANK *Player, MAP *map, BODY *Body, int x, int y);
int		Move(TANK *Tank, BODY *Body, MAP *map, char direction);

void	Init_Player(TANK *Player, BODY *Body);
void	Init_Piou(PIOUPIOU *Piou);
void	Init_Ennemy(TANK *Ennemy);
void	create_ennemy(TANK *Tank, MAP *map, BODY *Body, int which_side, int type);
void	Add_Tank(TANK *tank, int which_side, int type, BODY *Body);
void	print_tank_on_screen(BODY	*Body, TANK *Player, int x, int y);
void	erase_tank_on_screen(BODY *Body, TANK *Player, int x, int y);
TANK*	return_first_tank_ennemy(TANK *ennemy);
void	check_ennemy(MAP *map, TANK *ennemy, BODY *Body, PIOUPIOU *Piou, TANK *Player);

void	put_tab_in_map(TANK *Player, MAP *map, BODY *Body);
void	put_piou_in_map(PIOUPIOU *Piou, MAP *map);



void	IA_if_Blocked(TANK *tank, MAP *map, BODY *body);

/* special_functions.c */

char 	key_pressed();
char 	key_pressed_blocked();
void	Set_off_Term();
void	Init_Term();

#endif
