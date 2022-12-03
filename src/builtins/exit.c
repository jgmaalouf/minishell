#include "minishell.h"

static int	builtin_exit_routine(t_cmd *table)
{
	extern char	**environ;

	free(table); // free content!
	strarr_free(environ);
	exit(g_exit_status);
}

int	builtin_exit(int argc, char *const argv[], t_cmd *table)
{
	ft_dwrite(2, "exit\n");
	if (argc == 1)
		return (builtin_exit_routine(table));
	errno = 0;
	g_exit_status = ft_strtol(argv[1], NULL, 10);
	if (!ft_isnumber(argv[1]) || errno == ERANGE)
	{
		output_error_arg("exit", argv[1], "numeric argument required");
		return (g_exit_status = -1, builtin_exit_routine(table));
	}
	if (argc == 2)
		return (builtin_exit_routine(table));
	return (output_error("exit", "too many arguments"));
}
