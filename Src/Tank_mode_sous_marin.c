#include "../Includes/Tank.h"


IMAGE	*Image_Change(IMAGE *img, int i)
{
	int 	a;

	a = 0;
	while (i > 0)
		{
			img = img->Next_image;
			i--;
			printf("1 tour\n", a);	
		}
		return img;
}

void	Erase_Tank(TANK *player, MAP *map, IMAGE *img, int number)
{
	int	x;
	int	y;
	
	img = Image_Change(img, number);
	for (x = 0; x < img->p_size_x; x++)
		{
			for (y = 0; y < img->p_size_y; y++)
				{
					if (map->Tab[x+player->pos_x][y+player->pos_y] == img->Player[x][y] && img->Player[x][y] != 32)
						map->Tab[x+player->pos_x][y+player->pos_y] = 32;
				}
		}
}

void	put_player_in_map(TANK *player, MAP *map, IMAGE *img)
{
	int	x,y;

	for (x = 0; x < img->p_size_x; x++)
	{
		for (y = 0; y < img->p_size_y; y++)
			{
				if (map->Tab[x+player->pos_x][y+player->pos_y] == 32)
					{
						printf("Map : '%c', par %c (tab) ; (pass_or_not_1) ", map->Tab[x+player->pos_x][y+player->pos_y], img->Player[x][y]);
						map->Tab[x+player->pos_x][y+player->pos_y] = img->Player[x][y];
					}
			}
		//printf("\n");
		//system("sleep 1");
	}
}

int  pass_or_not(TANK *player, MAP *map, IMAGE *img, int x, int y)
{
	int	i,j;

	printf("Pass_or_not\n\n");
	for (i = 0; i < img->p_size_x; i++)
	{
		for (j = 0; j < img->p_size_y; j++)
			{
				printf("%c", map->Tab[i+x][j+y]);
				if (map->Tab[i+x][j+y] != 32 && img->Player[i][j] != 32)
					{
						printf("le caractere qui bloque est %c\n", map->Tab[i+x][j+y]);
						system("sleep 2");
						put_player_in_map(player, map, img);
						//return (0);
						exit(0);
					}
			}
		printf("\n");
		//system("sleep 0.5");
	}
	/*printf("Ca passe oklm\n");
	system("sleep 0.5");*/
	return (1);
}

/*void	Spawn_Ennemy(TANK *ennemy)
{
	ennemy->who = 0;
	ennemy->pic = NULL;
	ennemy->pos_x = 75;
	ennemy->pos_y = 3;
	ennemy->Obus_suivant = NULL;
	ennemy->Ennemi_suivant = NULL;
	ennemy->Moving_State = NULL;
	ennemy->Firing_State = NULL;
	ennemy->Life = 1;
}
*/

void	Init_Player(TANK *player)
{
	player->pic = NULL;
	player->pos_x = 21;
	player->pos_y = 29;
	player->Obus_suivant = NULL;
	player->Ennemi_suivant = NULL;
	player->Moving_State = 0;
	player->Firing_State = 0;
	player->Life = 3;
}


void Orchestra_Chief(IMAGE *img,MAP *map)
{
	TANK	player;
	TANK	ennemy;
	char	key;
	int	pass;
	IMAGE	*first_element;
	int	Carroserie_Number;
	
	Init_Player(&player);
	convert(*map);
	first_element = img;
	put_player_in_map(&player, map, img);
	Carroserie_Number = 0;
	print_tab(map->Tab, map->x);
	printf("VOICI LA MAP APRES L'INITIALISATION");
	//system("sleep 1");
	//system("clear");
	//img = Image_Change(img,3);
	while (1)
	{
		img = first_element;
		key = key_pressed();
		if (key == 108)
					{
						Erase_Tank(&player, map, img, Carroserie_Number);
						img = Image_Change(img,1);
						print_tab(map->Tab, map->x);
						//printf("Map vide affichage dans 1 s\n");
						//system("sleep 1");
						//system("sleep 2");	
						system("clear");
						//pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y + 1);
						pass = 1;
						if (pass == 1)
							{
								//printf("Pass_or_not reussie, affichage de la map\nPosition de y = %d\n", player.pos_y);
								//system("sleep 1");
								player.pos_y++;
								//printf("Put_player_in_map dans 1 s\n");
								//system("sleep 1");
								put_player_in_map(&player, map, img);
								print_tab(map->Tab, map->x);
								Carroserie_Number = 1;
							}
						else
							{
								system("clear");
								printf("AH BAH OBSTACLE ENFOIRE\n");
								system("sleep 1");
								exit(0);
								print_tab(map->Tab, map->x);
							}
					}
		if (key == 106)
				{
					Erase_Tank(&player, map, img, Carroserie_Number);
					img = Image_Change(img,3);
					print_tab(map->Tab, map->x);
					//pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y - 1);
					pass = 1;
					system("clear");
					if (pass == 1)
						{
							player.pos_y--;
							put_player_in_map(&player, map, img);
							print_tab(map->Tab, map->x);
							Carroserie_Number = 3;
						}
					else
						print_tab(map->Tab, map->x);
				}
		if (key == 105)
				{
					Erase_Tank(&player, map, img, Carroserie_Number);
					print_tab(map->Tab, map->x);
					//pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y - 1);
					pass = 1;
					system("clear");
					if (pass == 1)
						{
							player.pos_x--;
							put_player_in_map(&player, map, img);
							print_tab(map->Tab, map->x);
							Carroserie_Number = 0;
						}
					else
						print_tab(map->Tab, map->x);
				}
		if (key == 107)
				{
					Erase_Tank(&player, map, img, Carroserie_Number);
					img = Image_Change(img,2);
					print_tab(map->Tab, map->x);
					//pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y - 1);
					pass = 1;
					system("clear");
					if (pass == 1)
						{
							player.pos_x++;
							put_player_in_map(&player, map, img);
							print_tab(map->Tab, map->x);
							Carroserie_Number = 2;
						}
					else
						print_tab(map->Tab, map->x);
				}
	}
	/*I	mage_Change(img,3);
	exit(0);*/
	/*while (1)
		{
			img = first_element;
			key = key_pressed();
			put_player_in_map(&player, map, img, 0);
			if (key == 108)
				{
					img = Image_Change(img,1);
					system("clear");
					pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y + 1);
					if (pass == 1)
						{
							player.pos_y++;
							put_player_in_map(&player, map, img, 1);
							print_tab(map->Tab, map->x);
						}
					else
						print_tab(map->Tab, map->x);
				}
			if (key == 106)
				{
					img = Image_Change(img,3);
					system("clear");
					pass = pass_or_not(&player, map, img, player.pos_x, player.pos_y - 1);
					if (pass == 1)
						{
							player.pos_y--;
							put_player_in_map(&player, map, img, 1);
							print_tab(map->Tab, map->x);
						}
					else
						print_tab(map->Tab, map->x);
				}
			if (key == 105)
				{
					system("clear");
					pass = pass_or_not(&player, map, img, player.pos_x - 1, player.pos_y);
					if (pass == 1)
						{
							player.pos_x--;
							put_player_in_map(&player, map, img, 1);
							print_tab(map->Tab, map->x);
						}
					else
						print_tab(map->Tab, map->x);
				}
			if (key == 107)
				{
					img = Image_Change(img,2);
					system("clear");
					pass = pass_or_not(&player, map, img, player.pos_x + 1, player.pos_y);
					if (pass == 1)
						{
							player.pos_x++;
							put_player_in_map(&player, map, img, 1);
							print_tab(map->Tab, map->x);
						}
					else
						print_tab(map->Tab, map->x);
				}
			}
			/*exit(0);*/
			//}
}


/*void	Start_position(TANK)
{
	

}*/
