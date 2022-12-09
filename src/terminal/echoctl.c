#include "minishell.h"

void	disable_echoctl(void)
{
	struct termios	terminal;

	tcgetattr(1, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &terminal);
}
