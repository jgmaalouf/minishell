#include "minishell.h"

int	fd_write_str(int fd, char *s)
{
	int	bytes;

	if (s == NULL)
		return (0);
	bytes = 0;
	while (*s)
		bytes += write(fd, s++, 1);
	return (bytes);
}

int	output_error(char *cmd, char *arg, char *msg)
{
	fd_write_str(2, "minishell: ");
	fd_write_str(2, cmd);
	fd_write_str(2, ": ");
	if (arg != NULL)
	{
		fd_write_str(2, arg);
		fd_write_str(2, ": ");
	}
	fd_write_str(2, msg);
	fd_write_str(2, "\n");
	return (EXIT_FAILURE);
}

int	builtin_exit_routine(t_cmd *table, int exit_status)
{
	free(table); // free content!
	exit(exit_status);
}

// int	exit_builtin(t_cmd *table)
int	builtin_exit(t_cmd *table)
{
	fd_write_str(2, "exit\n");
	if (table->cmd_argc == 1)
		builtin_exit_routine(table, g_exit_status);
	if (!ft_isnumber(table->cmd_argv[1]))
	{
		output_error("exit", table->cmd_argv[1], "numeric argument required");
		builtin_exit_routine(table, -1);
	}
	if (table->cmd_argc == 2)
		builtin_exit_routine(table, atoi(table->cmd_argv[1]));
	output_error("exit", NULL, "too many arguments");
	return (EXIT_FAILURE);
}
