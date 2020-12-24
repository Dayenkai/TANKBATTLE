#include	"../Includes/Tank.h"

void	print_space(int n)
{	
	for (n; n > 0 ; n--)
		printf(" ");
}

void	print_line_jump(int n)
{
	for (n ; n > 0 ; n--)
		printf("%d\n", n);
}

char key_pressed_blocked()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;

	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {ungetc(c, stdin); result = getchar();}
		return result;
}

char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;

	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {ungetc(c, stdin); result = getchar();}
		return result;
}
