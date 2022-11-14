#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		printf("SIGINT\n");
	if (signal == SIGQUIT)
		printf("SIGQUIT\n");
}

// signal(SIGINT, signal_handler);
// signal(SIGQUIT, signal_handler);

void	ctrl_c(int signal)
{
	// int g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
