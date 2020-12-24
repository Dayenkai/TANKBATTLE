#include "../Includes/Tank.h"


IMAGE	*Image_Change(IMAGE *img, int i)
{

	while (i > 0)
		{
			img = img->Next_image;
			i--;
		}
		return img;
}

void	put_player_in_map(TANK *player, MAP *map, IMAGE *img, int state)
{
	int	x,y;

	for (x = 0; x < img->p_size_x; x++)
	{
		for (y = 0; y < img->p_size_y; y++)
			{
					if (state == 1)
						{
							if (map->Tab[x+player->pos_x][y+player->pos_y] == 32)
								{
									map->Tab[x+player->pos_x][y+player->pos_y] = img->Player[x][y];
								}
						}
					else if (state == 0)
					{
						if (map->Tab[x+player->pos_x][y+player->pos_y] == img->Player[x][y] && img->Player[x][y] != 32)
							{
								printf("Map : '%c', par %c (tab) ; ", map->Tab[x+player->pos_x][y+player->pos_y], 32);
								map->Tab[x+player->pos_x][y+player->pos_y] = 32;
							}
					}
			}
	}
	print_tab(map->Tab, map->x);
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
						put_player_in_map(player, map, img, 1);
						//return (0);
						exit(0);
					}
			}
		printf("\n");
	}

	return (1);
}

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
	
	Init_Player(&player);
	convert(*map);
	first_element = img;
	put_player_in_map(&player, map, img, 1);
	print_tab(map->Tab, map->x);
	

	system("mpg123 -q Sounds/CHIRIKU.wav &")
	while (1)
	{
		img = first_element;
		key = key_pressed();
		if (key == 108)
					{
						put_player_in_map(&player, map, img, 0);
						system("clear");
						pass = 1;
						if (pass == 1)
							{
								player.pos_y++;
								put_player_in_map(&player, map, img, 1);
							}
					}
		if (key == 106)
				{
					put_player_in_map(&player, map, img, 0);
					img = Image_Change(img,3);
					system("clear");
					pass = 1;
					if (pass == 1)
						{
							player.pos_y--;
							put_player_in_map(&player, map, img, 1);
							print_tab(map->Tab, map->x);
						}
					else
						print_tab(map->Tab, map->x);
				}
	}
}