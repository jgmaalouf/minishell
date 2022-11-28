#include "minishell.h"

int	output_error(char *cmd, char *msg)
{
	ft_dwrite(2, "minishell: ");
	ft_dwrite(2, cmd);
	ft_dwrite(2, ": ");
	ft_dwrite(2, msg);
	ft_dwrite(2, "\n");
	return (g_exit_status = 1);
}

int	output_error_arg(char *cmd, char *arg, char *msg)
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

int	output_error_quoted_arg(char *cmd, char *arg, char *msg)
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
