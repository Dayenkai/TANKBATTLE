#include "../Includes/Tank.h"

BODY	*BODY_Change(BODY *Body, int i)
{
	int 	a;

	a = 0;
	while (i > 0)
		{
			Body = Body->Next_Body;
			i--;
		}
	return Body;
}

void	erase_tank_on_screen(BODY *Body, TANK *Player, int x, int y)
{
	int	i;
	int	j;

	for (i = 0; i < Body->size_x; i++)
		{
			for (j = 0; j < Body->size_y; j++)
				{
					if (Body->Tab[i][j] != 32)
						{
							gotoxy(1+x+i, 1+y+j);
							printf(" ");
						}
				}
		}
}

void		print_tank_on_screen(BODY	*Body, TANK *Player, int x, int y)
{
	int	i;
	int	j;	

	for (i = 0; i < Body->size_x; i++)
		{
			for (j = 0; j < Body->size_y; j++)
				{
					if (Body->Tab[i][j] != 32)
						{
							gotoxy(1+x+i, 1+y+j);
							if (Player->who == 1)
								green_mode();
							if (Player->who != 1)
								red_mode();
							switch(Body->Tab[i][j])
								{
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
											printf("%c", 178);
										break;
									case 76:
											printf("%c", 247);
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
									case 't':
											printf("%c", 195);
											break;
									case 'p':
											printf("%c", 194);
											break;
									case 'q':
											printf("%c", 180);
											break;
									case 'o':
											printf("%c", 196);
											break;
									default:
											printf("%c", Body->Tab[i][j]);
										break;
								}
								white_mode();
						}
				}
		}
}

void		Calculate_new_pos(TANK *tab, MAP *map,BODY *Body)
{
	int	x;
	int	y;
	int	temp;
	
	temp = 0;
	for (x = 0; x < Body->size_x; x++)
		{
			for (y = 0; y < Body->size_y; y++)
				{
						if (Body->Tab[x][y] == 'e' || Body->Tab[x][y] == 'r' || Body->Tab[x][y] == 'z' || Body->Tab[x][y] == 'k')
							{
								if (temp == 0)
									{
										tab->pos_x = tab->pos_x - x;
										tab->pos_y = tab->pos_y - y;
										temp++;
									}
							}
				}
		}
}

void	Erase_Tank(TANK *Player, MAP *map, BODY *Body, int number, int number_actual)
{
	int	x;
	int	y;
	int	temp;
	int	previous_x;
	int	previous_y;
	
	temp = 0;
	previous_x = Player->pos_x;
	previous_y = Player->pos_y;
	Body = BODY_Change(Body, number);
	for (x = 0; x < Body->size_x; x++)
		{
			for (y = 0; y < Body->size_y; y++)
				{
					if (number != number_actual)
						if (map->Tab[x+Player->pos_x][y+Player->pos_y] == 'e' || map->Tab[x+Player->pos_x][y+Player->pos_y] == 'r' || map->Tab[x+Player->pos_x][y+Player->pos_y] == 'z' || map->Tab[x+Player->pos_x][y+Player->pos_y] == 'k')
							{
								if (temp == 0)
									{
										Player->new_x = x+Player->pos_x;
										Player->new_y = y+Player->pos_y;
										temp++;
									}
							}
					if (map->Tab[x+Player->pos_x][y+Player->pos_y] == Body->Tab[x][y] && Body->Tab[x][y] != 32)
						map->Tab[x+Player->pos_x][y+Player->pos_y] = 32;
				}
		}
	erase_tank_on_screen(Body, Player, Player->pos_x, Player->pos_y);
	if (number != number_actual)
		{
			Player->pos_x = Player->new_x;
			Player->pos_y = Player->new_y;
			Player->new_x = previous_x;
			Player->new_y = previous_y;
		}
	else
		{
			Player->new_x = previous_x;
			Player->new_y = previous_y;
		}
}

void	put_piou_in_map(PIOUPIOU *Piou, MAP *map)
{
	map->Tab[Piou->x][Piou->y] = Piou->Body;
}

void	put_tab_in_map(TANK *Player, MAP *map, BODY *Body)
{
	int	x,y;

	for (x = 0; x < Body->size_x; x++)
	{
		for (y = 0; y < Body->size_y; y++)
			{
				if (map->Tab[x+Player->pos_x][y+Player->pos_y] == 32)
					map->Tab[x+Player->pos_x][y+Player->pos_y] = Body->Tab[x][y];
			}
	}
}

int  pass_or_not(TANK *Player, MAP *map, BODY *Body, int x, int y)
{
	int	i,j;

	for (i = 0; i < Body->size_x; i++)
	{
		for (j = 0; j < Body->size_y; j++)
			{
				if (map->Tab[i+x][j+y] != 32 && Body->Tab[i][j] != 32)
					if (map->Tab[i+x][j+y] != Body->Tab[i][j])
						{
							return (0);
						}
			}
	}
	return (1);
}

void	Init_Piou(PIOUPIOU *Piou)
{
	Piou->Body = 207;
	Piou->x = 30;
	Piou->y = 82;
	Piou->Move_State = 0;
}
void	Init_Ennemy(TANK *Ennemy)
{
	Ennemy->pos_x = 0;
	Ennemy->pos_y = 0;
	Ennemy->Obus_suivant = malloc(sizeof(OBUS));
	Ennemy->Obus_suivant->Obus_suivant = NULL;
	Ennemy->Next_Ennemy = NULL;
	Ennemy->Moving_State = 0;
	Ennemy->Firing_State = 0;
	Ennemy->Life = 3;
	Ennemy->Previous_Body_Number;
}

void	Init_Player(TANK *Player, BODY *Body)
{
	Player->pos_x = 21;
	Player->pos_y = 35;
	Player->Obus_suivant = malloc(sizeof(OBUS));
	Player->Obus_suivant->Obus_suivant = NULL;
	Player->Next_Ennemy = NULL;
	Player->Moving_State = 0;
	Player->Firing_State = 0;
	Player->who = 1;
	Player->Life = 3;
	Player->Previous_Body_Number = 0;
	Player->Actual_Body = Body;
}



int	Move(TANK *Tank, BODY *Body, MAP *map, char direction)
{

	int	pass = 0;
	BODY	*first_element = Body;
	
	if (direction == 'R')
			{
				//system("clear");
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 1);
				Body = BODY_Change(Body,1);
				if(Tank->Previous_Body_Number != 1)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y + 1);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 1)
							Tank->pos_y++;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						Tank->Previous_Body_Number = 1;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return(1);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return(0);
					}
					gotoxy(1,1);
				}
	if (direction == 'L')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 3);
				Body = BODY_Change(Body,3);
				if( Tank->Previous_Body_Number != 3)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y - 1);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 3)
							Tank->pos_y--;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						Tank->Previous_Body_Number = 3;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return (1);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return (0);
					}
				gotoxy(1,1);
			}
	if (direction == 'U')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 0);
				if( Tank->Previous_Body_Number != 0)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x - 1, Tank->pos_y);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 0)
							Tank->pos_x--;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						Tank->Previous_Body_Number = 0;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return (1);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return (0);
					}
				gotoxy(1,1);
			}
	if (direction == 'D')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 2);
				Body = BODY_Change(Body,2);
				if( Tank->Previous_Body_Number != 2)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x + 1, Tank->pos_y);
				if (pass == 1)
					{
						if(Tank->Previous_Body_Number == 2)
							Tank->pos_x++;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						Tank->Previous_Body_Number = 2;
						return(1);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						Tank->Actual_Body = Body;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						return(0);
					}
				gotoxy(1,1);
			}
}

void	Orchestra_Chief(BODY *Body,MAP *map)
{
	TANK	Player;
	TANK	Ennemy;
	PIOUPIOU	Piou;
	char	key;
	int	pass;
	BODY	*first_element;
	TANK	*unforget;
	int	Time_apparition = 0;
	int	temp = 0;
	
	Init_Player(&Player, Body);
	Init_Ennemy(&Ennemy);
	Init_Piou(&Piou);
	first_element = Body;
	put_tab_in_map(&Player, map, Body);
	put_piou_in_map(&Piou,map);
	Player.Previous_Body_Number = 0;
	clear_screen();
	print_converted(map->Tab, map->x);
	system("aplay -q  Sounds/action_music.wav &");
	printf("\nControls : i->up, k->down, j->left, l->right, r->fire\nQ: Quit the game");
	while (1)
	{
		Body = first_element;
		key = key_pressed();
		switch (key)
			{
				case 'i':
					key = Move(&Player, first_element, map, 'U');
					break;
				case 'l':
					Move(&Player, first_element, map, 'R');
					break;
				case 'j':
					Move(&Player, first_element, map, 'L');
					break;
				case 'k':
					Move(&Player, first_element, map, 'D');
					break;
				case 'r':
					create_obus(&Player, Player.pos_x, Player.pos_y, Player.Previous_Body_Number, 1, 1, map);
					break;
				case 'q':
					system("clear");
					system("printf \"                                                                    Leaving the Game\n; sleep 1"); clear_screen();
					system("clear");
					system("printf \"                                                                    Bye !\n; sleep 1"); clear_screen();
					Init_Term();
					exit(0);
			}
		check_obus(map, &Player, &Ennemy, &Piou);
		check_ennemy(map, &Ennemy, first_element, &Piou, &Player);
		if (Time_apparition < 500000)
			Time_apparition++;
		if (Time_apparition >= 500000)
			{
					if (temp == 0 || temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5 || temp == 6 || temp == 7 || temp == 8 || temp == 9)
						create_ennemy(&Ennemy, map, Body, 0, 0);
				temp++;
				Time_apparition = 0;
			}
	}
}
