#include	"../Includes/Tank.h"

TANK*	return_first_tank_ennemy(TANK *ennemy)
{
	TANK *First;

	First = ennemy->Next_Ennemy;
	return(First);
}

/*void	Check_Around(TANK *Tank,BODY *Body,MAP * map,int distx_to_piou,int disty_to_piou)
{

}*/

/*void	Gank_Piou(TANK *Tank,BODY *Body,MAP * map,int distx_to_piou,int disty_to_piou)
{
	if (distx_to_piou < 0 && disty_to_piou > 0)
	{
		Tank->direction = 'D';
		Move(Tank, Body, map, 'D');
	}
	//Body = BODY_Change(Body,Tank->Previous_Body_Number);
}*/

void		Add_Tank(TANK *tank, int which_side, int type, BODY *Body)
{
	TANK *element;
	int	i;

	i = 0;
	element = tank;
	while (element->Next_Ennemy != NULL)
		element = element->Next_Ennemy;
	element->Next_Ennemy = malloc(sizeof(TANK));
	element = element->Next_Ennemy;
	element->type = type;
	element->direction = 'U';
	element->ally_or_ennemy = which_side;
	element->Previous_Body_Number = 0;
	element->Actual_Body = Body;
	element->Time_Move = 0;
	element->Next_Ennemy = NULL;
	element->pos_x = 20;
	element->pos_y = 110;
	element->Time_shoot=0;
	element->who = -1;
	element->previous_error_movement = 0;
	element->Obus_suivant = malloc(sizeof(OBUS));
	element->Obus_suivant->Obus_suivant = NULL;
	element->Moving_State = 0;
	element->Firing_State = 0;
	element->Life = 3;
}

void	create_ennemy(TANK *Tank, MAP *map, BODY *Body, int which_side, int type)
{
	if (pass_or_not(Tank, map, Body, 20, 110)== 1)
		{
			Add_Tank(Tank, which_side, 0, Body);
			while (Tank->Next_Ennemy != NULL)
			Tank = Tank->Next_Ennemy;
			put_tab_in_map(Tank, map, Body);
			print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
		}
}

void	check_ennemy(MAP *map, TANK *ennemy, BODY *Body, PIOUPIOU *Piou, TANK *Player)
{
	TANK 	*Actual;
	TANK	*Previous;
	int	distx_to_piou;
	int	disty_to_piou;
	int	distance=0;
	int	random=0;
	
	srand(time(NULL));
	Actual = ennemy->Next_Ennemy;
	Previous = Actual;
	while (Actual != NULL)
		{
			random = rand()%4+1;
			if (Actual->Time_Move > 10000)
				{
					Actual->Time_Move = 0;
					distx_to_piou = Actual->pos_x - Piou->x;
					disty_to_piou = Actual->pos_y - Piou->y;
					switch (random)
						{
								case 1:
									Actual->direction = 'R';
									break;
								case 2:
									Actual->direction = 'D';
									break;
								case 3:
									Actual->direction = 'L';
									break;
								case 4:
									Actual->direction = 'U';
									break;
						}
					Move(Actual, Body, map, Actual->direction);
				}
			if (Actual->Time_shoot > 30000)
			{
				random = rand()%3+1;
				if (random == 1)
					create_obus(Actual, Actual->pos_x, Actual->pos_y, Actual->Previous_Body_Number, -1, 1, map);
				Actual->Time_shoot = 0;	
			}
			Actual->Time_Move++;
			Actual->Time_shoot++;
			check_obus(map, Actual, Player, Piou);
			Actual = Actual->Next_Ennemy;
		}
}