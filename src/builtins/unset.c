#include "minishell.h"

static int	unset_name(char *name)
{
	if (!valid_variable_name(name))
		return (error_argv_quoted("unset", name, "not a valid identifier"));
	// delete `set' variable
	return (ft_unsetenv(name));
}

int	builtin_unset(int argc, char *const argv[])
{
	int	status;

	if (argc == 1)
		return (g_exit_status = 0);
	status = 0;
	while (*(++argv) != NULL)
		if (unset_name(*argv) != EXIT_SUCCESS)
			status = 1;
	return (g_exit_status = status);
}
