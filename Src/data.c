#include "../Includes/Tank.h"

void	Add_element_last(BODY *element) // Permet d'ajouter en fin de chaine d'une liste chainée un corps de tank.
{
	while (element->Next_Body != NULL)
			element = element->Next_Body;
	element->Next_Body = malloc(sizeof(BODY));
}

void	Copy_Chars_To_Tabs_One_Side(BODY *tank, FILE **tank_file, int size_x, int size_y, int Number, int type) // Copie un corps de Tank dans un double tableau, 
{																												//puis sauvegarde les longueurs et largeur de ces corps, selon leur type déjà défini par les fichiers.
	int	line;
	int	column;
	int	carac;
	
 	for (line = 0; line < size_x; line++)
 		{
			for (column = 0; column < size_y+1; column++)
				{
					carac = fgetc(*tank_file);
					if (carac == '\n')
						{
							while (column < size_y+1)
								{
									tank->Tab[line][column] = 32;
									column++;
								}
							tank->Tab[line][column] = '\0';
						}
					else
						tank->Tab[line][column] = carac;
				}
		}
	switch (type)
		{
			case 0:
				switch (Number)
					{
						case 0:
							tank->cannon_pos_x = - 1;
							tank->cannon_pos_y = 5;
						case 1:
							tank->cannon_pos_x = 2;
							tank->cannon_pos_y = 16;
						case 2:
							tank->cannon_pos_x = 7;
							tank->cannon_pos_y = 5;
						case 3:
							tank->cannon_pos_x = 2;
							tank->cannon_pos_y = -1;
					}
				break;
		}
}

void	Copy_Chars_To_Tabs(BODY *tank, FILE **tank_file, int size_x, int size_y, int size_xprime, int size_yprime, int type)
{
	int	z;
	int	line;
	int	colunm;
	int	carac;
	
	for (z = 0; z < 4 ; z++)
		{
			if (z % 2 == 0)
			{
				Copy_Chars_To_Tabs_One_Side(tank, tank_file, size_x, size_y, z, type);
				tank->size_x = size_x ; tank->size_y = size_y;
			}
			if (z % 2 == 1)
			{
				Copy_Chars_To_Tabs_One_Side(tank, tank_file, size_xprime, size_yprime, z, type);
				tank->size_x = size_xprime ;tank->size_y = size_yprime;
			}
			tank = tank->Next_Body;
		}
}

void	Get_Tanks_Player(BODY *Tank, FILE **tank_file, int size_x, int size_y, int size_xprime, int size_yprime, int type) //On récupère le tank du joueur de son fichier envoyé en paramètre de fonction.
{
	int	i;
	BODY *First;
	
	Tank->Next_Body = NULL;
	First = Tank;
	for (i = 0; i < 4; i++)
	{
		if (i % 2 == 0)
			Alloc_Tab(&(Tank->Tab), size_x, size_y+1);
		if (i % 2 != 0)
			Alloc_Tab(&(Tank->Tab), size_xprime, size_yprime+1);
		Add_element_last(Tank);
		Tank = Tank->Next_Body;
	}
	Tank = First;
	Copy_Chars_To_Tabs(Tank, tank_file, size_x, size_y, size_xprime, size_yprime, type);
}

void	Alloc_Tab(char ***str, int x, int y) // On alloue juste un tableau d'une taille (x;y) dans lelquel on va copier notre map ou notre tank. Ici l'adresse du tableau est en parametre, on accede au contenu avec *, nul besoin donc de retourner le tableau alloué.
{
	int	i = 0;
	*str = malloc(x*sizeof(char*));
	for (i; i < x ; i++)
		*(*(str)+i) = malloc(y*sizeof(char));
}

void	Copy_Map_to_Tab(MAP *map, FILE **file) // On Récupère la map que l'on stocke dans un tableau à deux dimensions
{
	int	line = 0;
	int	column = 0;
	int	carac;

	rewind(*file); // Le fichier ayant été préalablement lu, le curseur en memoire qui nous a permit de recuperer chacune des lettre se trouve à la fin du fichier. rewind permet donc de repositionner ce curseur invisible, en memoire, au début du fichier, afin de pouvoir le relire à nouveau
	for (line = 0; line < map->x ; line++)
	{
		for (column = 0; column < map->y + 1; column++) //On lit la ligne du fichier. Il est possible qu'elle soit plus petite que la taille max de la map. Mais cela proviendrait de la responsabilité des créateurs à l'origine de la création d'une telle map bizarre...
			{
				carac = fgetc(*file);
				if (carac != '\n')
					{
						map->Tab[line][column] = carac;
					}
				if (carac == '\n') // A la fin de la ligne dans le fichier
					{
						while (column < map->y+1) // Voir le commentaire ci dessus. Si jamais c'est le cas, et que la ligne est plus petite que la longueur max du tableau, le reste de la ligne dans le tableau est remplacé par des espaces.
							{
								map->Tab[line][column] = 32;
								column++;
							}
					}
			}
		map->Tab[line][column] = '\0'; //Apparemment pas necessaire, mais ce qui delimite la fin d'une chaine de caractere...
	}
}

void	Find_Size_Map(MAP *map, FILE **file) //La fonction calcule simplement la taille maxx necessaire au tableau pour contenir la map
{
	int carac = 0;
	int line = 0;
	int column = 0;
	int temp_column = 0;

	while (carac != EOF)
		{
			carac = fgetc(*file);
			if (carac == '\n')    					// le but est de trouver la plus longue ligne possible, qui determinera le nombre de colonne max du tableau qui contiendra la map
				{
					if (temp_column > column)		 // Si la longueur de la ligne est plus grande que la précédente
						column = temp_column; 		// column prendra la valeur de temp_column
					temp_column = -1; 				// On réinitialise la variable afin de compter la longueur de la prochaine ligne jusqu'à ce qu'on retrouve un \n dans le fichier.
					line++; 								// A chaque \n rencontré, la largeur du tableau qui contiendra la map augmentera de 1 ligne, naturellement.
				}
			temp_column++; // A chaque caractere lu, on incremente temp column, ou la longueur de la ligne est 1 caractere plus grand.
		}
	map->x = line;
	map->y = column;
}

void	Get_Map_Info(MAP *map, FILE **file) //Dans cette fonction, on récupère la  taille de la map, qu'on suvegarde ensuite en mémoire
{
	Find_Size_Map(map, file);
	Alloc_Tab(&(map->Tab), map->x, map->y+1);
	Copy_Map_to_Tab(map,file);
}

void	Open_File(char *str, FILE **file) //Fonction pour ouvrir le fichier
{	*file = fopen(str,"r+");
	if(*file == NULL)
		error_opening_file_message();
}

void	Get_Data() // GET DATA() VA STOCKER LES INFOS CONTENU DANS DIFFERENTS FICHIERS PREDEFINI AFIN DE CHARGER CORRECTEMENT LA MAP ET LES TANKS ! ORCHESTRA CHIEF PRENDRA LE RELAI POUR LE DEROULEMENT DU JEU.
{
	FILE	*file_map;
	FILE	*file_tank_player;
	FILE	*file_tank_ennemy;
	FILE	*file_tank_ennemy_2;
	MAP	map;
	BODY	player_tank;
	BODY	regular_ennemy_tank;
	BODY 	second_ennemy_tank;

	Open_File("Maps/RISAN_MAP.txt",&file_map); // Va ouvrir la map (si le fichier est valide)
	Get_Map_Info(&map,&file_map); // Recupere les données du fichier map et le stocke dans la structure map
	fclose(file_map); // ferme le fichier ouvert
	Open_File("Tanks/tanknul.txt",&file_tank_player); // Ouvre le second fichier, contenant les carrosserie du joueur
	Open_File("Tanks/tankbof.txt",&file_tank_ennemy);
	Open_File("Tanks/tankfortaskip.txt",&file_tank_ennemy_2); // Ouvre le troisieme, contenant celui des joueurs ennemi
	Get_Tanks_Player(&player_tank, &file_tank_player,5,5,3,8,0); // Recupere les données des fichiers tank, soit leur longueur et largeur selon u'ils soient dirigé vers le haut/bas, ou gauche/droite, et on les stockent dans la structure BODY
	Get_Tanks_Player(&regular_ennemy_tank, &file_tank_ennemy, 7,7,5,10,0);
	//Get_Tanks_Player(&second_ennemy_tank, &file_tank_ennemy_2, 7,7,5,11,0);
	fclose(file_tank_player);
	fclose(file_tank_ennemy);
	fclose(file_tank_ennemy_2);
	Orchestra_Chief(&player_tank,&map);
}