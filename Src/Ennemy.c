#include	"../Includes/Tank.h"


void		Add_Tank(TANK *tank, int which_side, int type)
{
	OBUS *element;
	int	i;

	i = 0;
	element = tank->Obus_suivant; 
	while (element->Obus_suivant != NULL)
		{
			element = element->Obus_suivant;
			i++;
		}
	element->Obus_suivant = malloc(sizeof(OBUS));
	element = element->Obus_suivant;


void	create_ennemy()
{
	Add_ennemy(tank, x, y, 'l', which_side);


}

void	check_ennemy(TANK *ennemy, MAP *map)
{
	Tank 	*Actual_Ennemy;
	Tank	*Previous;
	int	temp;
	
	Actual_Ennemy = tank->Obus_suivant;
	Previous = Obus;
	while (Actual != NULL)
		{
		}
}
