#include "minishell.h"

int	error_output(char *cmd, char *msg)
{
	ft_dwrite(2, "minishell: ");
	ft_dwrite(2, cmd);
	ft_dwrite(2, ": ");
	ft_dwrite(2, msg);
	ft_dwrite(2, "\n");
	return (g_exit_status = 1);
}

int	error(char *cmd, char *msg, int status)
{
	error_output(cmd, msg);
	return (g_exit_status = status);
}

int	error_argv(char *cmd, char *arg, char *msg)
{
	ft_dwrite(2, "minishell: ");
	ft_dwrite(2, cmd);
	ft_dwrite(2, ": ");
	ft_dwrite(2, arg);
	ft_dwrite(2, ": ");
	ft_dwrite(2, msg);
	ft_dwrite(2, "\n");
	return (g_exit_status = 1);
}

int	error_argv_quoted(char *cmd, char *arg, char *msg)
{
	ft_dwrite(2, "minishell: ");
	ft_dwrite(2, cmd);
	ft_dwrite(2, ": ");
	ft_dwrite(2, "`");
	ft_dwrite(2, arg);
	ft_dwrite(2, "'");
	ft_dwrite(2, ": ");
	ft_dwrite(2, msg);
	ft_dwrite(2, "\n");
	return (g_exit_status = 1);
}

int	fatal_error(int code)
{
	ft_dwrite(2, BOLD RED);
	ft_dwrite(2, "minishell: fatal error: ");
	if (code == ENOMEM)
		ft_dwrite(2, "critical memory allocation failed\n");
	ft_dwrite(2, RESET);
	return (g_exit_status = -1);
}
