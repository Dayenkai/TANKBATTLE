#include "../Includes/Tank.h"

int		check_who_got_shot(OBUS *Obus, MAP *map, TANK *tank, PIOUPIOU *piou, TANK *shooter)
{
	int 	x;
	int 	y;
	TANK 	*Previous;

	if (shooter->who == 1)
	{
		Previous = tank;
		tank = tank->Next_Ennemy;
	}
	while(tank != NULL)
	{
		if (tank->who == 1)
		{
			for (x=0; x < tank->Actual_Body->size_x; x++)
				for (y=0; y < tank->Actual_Body->size_y; y++)
				{
					if (tank->pos_x + x == Obus->x && tank->pos_y+y == Obus->y)
					{
						if (tank->Actual_Body->Tab[x][y] != ' ')
							{
								tank->Life -= 1;
								if (tank->Life == 0)
								{				
									system("aplay -q Sounds/Suicide_Bomber.wav &");
									system("clear");
									Defeat_Announce();
									Init_Term();
									exit(0);
								}
							}
						if (piou->x + x == Obus->x && piou->y + y == Obus->y)
						{
							piou->Life--;
							if (piou->Life == 0)
								{
									system("aplay -q Sounds/Suicide_Bomber.wav &");
									system("clear");
									Defeat_Announce();
									Init_Term();
									exit(0);
								}
						}

					}
				}
			}
		if (tank->who == -1)
		{
			if (Obus->ally_or_ennemy != tank->who)
				tank->Life -= 1;
			if (tank->Life == 0)
			{
				//Supposed to erase the ennemy tank with no life anymore, work in progress;
			}
		}
		Previous = tank;
		tank = tank->Next_Ennemy;
	}
	return(0);
}

void	what_who_got_shot(OBUS *Obus, MAP *map, TANK *tank, TANK *shooter, PIOUPIOU *piou)
{
	if (Obus->type == 1)
		{
			if (map->Tab[Obus->x][Obus->y] == 'B')
				{
					map->Tab[Obus->x][Obus->y] = 32;
					gotoxy(1+Obus->x, 1+Obus->y);printf(" ");
				}
			else if(map->Tab[Obus->x][Obus->y] == 'R')
			{
				map->Tab[Obus->x][Obus->y] = 'B';
				gotoxy(1+Obus->x, 1+Obus->y);
				printf("%c", 177);
			}
			else if (Obus->y > 3 && map->Tab[Obus->x][Obus->y] != 'i' && Obus->x > 0 && Obus->x < map->x-1 && map->Tab[Obus->x][Obus->y] != 32 &&  map->Tab[Obus->x][Obus->y] != 76 && map->Tab[Obus->x][Obus->y] != 65 && map->Tab[Obus->x][Obus->y] != 'B' && map->Tab[Obus->x][Obus->y] != 'R')
			{
				check_who_got_shot(Obus, map, tank, piou, shooter);
			}
		}
}

void		Erase_Obus(OBUS *element, OBUS *previous,TANK *tank)  	    
{
	if (element->Obus_suivant == NULL)
		{
			if (element == previous)
				{
					free(previous);
					tank->Obus_suivant->Obus_suivant = NULL;
				}
			else
				{
					free(element);
					previous->Obus_suivant = NULL;
				}
		}
	else
		{
			if (previous == element)
				{
					tank->Obus_suivant->Obus_suivant = previous->Obus_suivant;
					free(previous);
				}
			else
				{
					previous->Obus_suivant = element->Obus_suivant;
					free(element);
				}
		}
}

void		Add_Obus(TANK *tank, int x, int y, char c, int which_side, int type, MAP *map)
{
	OBUS *element;
	OBUS *previous;
	int	i;

	i = 0;
	element = tank->Obus_suivant;
	previous = element;
	while (element->Obus_suivant != NULL)
		{
			element = element->Obus_suivant;
			previous = element;
			i++;
		}
	element->Obus_suivant = malloc(sizeof(OBUS));
	element = element->Obus_suivant;
	if (c == 'i')
		{		
			element->x = x - 1;
			element->y = y + 2;
		}
	if (c == 'l')
		{
			element->x = x +1;
			element->y = y + 8;
		}
	if (c == 'k')
		{
			element->x = x + 5;
			element->y = y + 2;
		}
	if (c == 'j')
		{
			element->x = x+1;
			element->y = y-1;
		}
	element->time = 0;
	element->previous_x = element->x;
	element->previous_y = element->y;
	element->direction = c;
	element->type = type;
	element->ally_or_ennemy = which_side;
	element->Obus_suivant = NULL;
	if (map->Tab[element->x][element->y] != 32)
		{
			free(element);
			previous->Obus_suivant = NULL;
		}
}

void	create_obus(TANK	*tank, int x, int y, int Carrosserie_Number, int which_side, int type, MAP *map)
{
	OBUS *Obus;
	int 	random;
	
	srand(time(NULL));
	random = rand()%3+1;
	if (random == 1)
		system("aplay -q Sounds/Cannon.wav &");
	Obus = tank->Obus_suivant;
	switch (Carrosserie_Number)
			{
				case 1:
					Add_Obus(tank, x, y, 'l', which_side,type, map);
					break;
				case 3:
					Add_Obus(tank, x, y, 'j', which_side, type, map);
					break;
				case 2:
					Add_Obus(tank, x, y, 'k', which_side, type, map);
					break;
				case 0:
					Add_Obus(tank, x, y, 'i', which_side, type, map);
					break;
			}
}

void	check_obus(MAP *map,TANK *tank, TANK *list_tank, PIOUPIOU *Piou)
{
	OBUS *Obus;
	OBUS	*Previous;
	int	temp;
	int if_erased=0;
	
	Obus = tank->Obus_suivant;
	Obus = Obus->Obus_suivant;
	Previous = Obus;
	while (Obus != NULL)
		{
			temp = 0;
			if (Obus->time > 2000)
				{
					Obus->time = 0;
					switch (Obus->direction)
						{
							case 'l':
								Obus->y++;
							break;
							case 'j':
								Obus->y--;
							break;
							case 'k':
								Obus->x++;
							break;
							case 'i':
								Obus->x--;
							break;
						}
					if (Obus->y == 3 || Obus->x == 0 || Obus->y == map->y-1 || Obus->x == map->x-1 || map->Tab[Obus->x][Obus->y] != 32)
						{
							map->Tab[Obus->previous_x][Obus->previous_y] = ' ';
							gotoxy(1+Obus->previous_x, 1+Obus->previous_y);printf(" ");
							gotoxy(1,1);
							what_who_got_shot(Obus, map, list_tank, tank, Piou);
							Erase_Obus(Obus, Previous,tank);
							temp++;
							gotoxy(1,1);
						}
					if (temp == 0)
					if (Obus != NULL && map->Tab[Obus->x][Obus->y] == 32)
						{
							map->Tab[Obus->previous_x][Obus->previous_y] = 32;
							gotoxy(1+Obus->previous_x, 1+Obus->previous_y);printf(" ");
							map->Tab[Obus->x][Obus->y] = 97;
							gotoxy(1+Obus->x, 1+Obus->y);printf("%c", 169);
							gotoxy(1,1);
							Obus->previous_x = Obus->x;
							Obus->previous_y = Obus->y;
						}
				}
			Previous = Obus;
			if (Obus != NULL)
				{
					Obus->time++;
					Obus = Obus->Obus_suivant;
				}
		}
}

void	IA_if_Blocked(TANK *tank, MAP *map, BODY *body)
{
	
}
