#include "minishell.h"

static int	builtin_exit_routine(t_cmd *table)
{
	extern char	**environ;

	free(table); // free content!
	strarr_free(environ);
	exit(g_exit_status);
}

// int	exit_builtin(t_cmd *table)
int	builtin_exit(t_cmd *table)
{
	ft_dwrite(2, "exit\n");
	if (table->cmd_argc == 1)
		return (builtin_exit_routine(table));
	errno = 0;
	g_exit_status = ft_strtol(table->cmd_argv[1], NULL, 10);
	if (!ft_isnumber(table->cmd_argv[1]) || errno == ERANGE)
	{
		output_error_arg("exit", table->cmd_argv[1], "numeric argument required");
		return (g_exit_status = -1, builtin_exit_routine(table));
	}
	if (table->cmd_argc == 2)
		return (builtin_exit_routine(table));
	return (output_error("exit", "too many arguments"));
}
