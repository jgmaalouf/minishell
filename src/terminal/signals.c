#include "minishell.h"

void	signal_ctrl_c_input(int signal)
{
	(void)signal;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 1;
}

void	signal_ctrl_c_runtime(int signal)
{
	(void)signal;
	write(1, "^C\n", 3);
	rl_redisplay();
	g_exit_status = 130;
}

void	signal_ctrl_backslash(int signal)
{
	(void)signal;
	write(1, "^\\Quit: 3\n", 10);
	g_exit_status = 131;
}

int	exit_ctrl_d(void)
{
	printf("\e[1A");
	rl_on_new_line();
	rl_redisplay();
	ft_dwrite(2, "exit\n");
	rl_clear_history();
	ft_environ(ENVIRON_DESTROY, NULL);
	return (g_exit_status);
}
