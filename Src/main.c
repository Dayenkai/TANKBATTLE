#include "../Includes/Tank.h"

int main(int argc, char *argv[])
{
	Set_off_Term();
	Menu(argv); //C'est la 1ère fonction angulaire du programme. Elle va recuperer les arguments (argv) du programme
					// ceux mis vis à vis de l'éxécutable. Normalement, ce sont les fichiers qui contiennent les Tanks et la Map
					// La gestion d'erreur se fait juste après, verifiant si ce sont bien des fichiers mis en paramètre.
}
