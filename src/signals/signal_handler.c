#include "minishell.h"

/*
void	signal_handler(int signal)
{
	if (signal == SIGINT)
		printf("SIGINT\n");
	if (signal == SIGQUIT)
		printf("SIGQUIT\n");
}

signal(SIGINT, signal_handler);
signal(SIGQUIT, signal_handler);
 */

/* SIGINT */
// void	signal_ctrl_c_idle(int signal)
// void	signal_ctrl_c_line(int signal)
void	signal_ctrl_c(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

/* SIGINT */
// void	signal_ctrl_c_running(int signal)
void	signal_ctrl_c_runtime(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

/* SIGQUIT */
void	signal_ctrl_backslash(int signal)
{
	(void)signal;
	write(1, "Quit: 3\n", 8);
	g_exit_status = 131;
}
