#include "minishell.h"

static void	add_assignment_command_environ(char *const argv[])
{
	char	*name;
	char	*value;

	while (*argv != NULL)
	{
		split_variable(*argv++, &name, &value);
		ft_setenv(name, value, 1);
		free(name);
		free(value);
	}
}

int	launch_assignment(t_node *nodelist)
{
	char *const	*argv;

	argv = nodelist->table->cmd_argv;
	if (handle_redirects(nodelist->table->redirlist) != EXIT_SUCCESS)
		return (stdio_fildes_handler(RESTORE_STD_FILDES), EXIT_FAILURE);
	if (nodelist->nexus == NODE_COMMAND)
	{
		nodelist->pid = fork();
		if (nodelist->pid < 0)
			return (-1);
		if (nodelist->pid == 0)
		{
			add_assignment_command_environ(argv);
			if (nodelist->table->builtin_id > 0)
				exit(execute_builtin(nodelist));
			exit(execute_command(nodelist->table));
		}
		stdio_fildes_handler(RESTORE_STD_FILDES);
		return (waitpid_exit_status(nodelist->pid));
	}
	while (*argv != NULL)
		variable_assignment(*argv++);
	stdio_fildes_handler(RESTORE_STD_FILDES);
	return (g_exit_status = 0);
}
