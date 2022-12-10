#include "minishell.h"

static bool	is_a_directory(const char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == EXIT_SUCCESS)
		if (S_ISDIR(stats.st_mode))
			return (true);
	return (false);
}

int	execute_command(t_cmd *table)
{
	extern char	**environ;

	if (handle_redirects(table->redirlist) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if (table->cmd_argc == 0)
		exit(EXIT_SUCCESS);
	table->cmd_path = find_cmd_path(table->cmd_argv[0]);
	if (table->cmd_path == NULL)
	{
		if (ft_strchr(table->cmd_argv[0], '/') != NULL)
			exit(error(table->cmd_argv[0], "No such file or directory", 127));
		exit(error(table->cmd_argv[0], "command not found", 127));
	}
	execve(table->cmd_path, table->cmd_argv, environ);
	if (is_a_directory(table->cmd_argv[0]))
	{
		if (ft_strchr(table->cmd_argv[0], '/') == NULL)
			exit(error(table->cmd_argv[0], "command not found", 127));
		exit(error(table->cmd_argv[0], "Is a directory", 126));
	}
	if (access(table->cmd_argv[0], X_OK) < 0)
		exit(error(table->cmd_argv[0], "Permission denied", 126));
	exit(-1);
}

int	launch_command(t_node *nodelist)
{
	if (nodelist->table->builtin_id > 0)
		return (execute_builtin(nodelist));
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
		exit(execute_command(nodelist->table));
	return (waitpid_exit_status(nodelist->pid));
}
