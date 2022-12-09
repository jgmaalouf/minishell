#include "minishell.h"

t_node	*subshell_extract_nodelist(t_node *nodelist)
{
	t_node	*subshell;

	subshell = nodelist->sub;
	free_nodelist(nodelist->next);
	free(nodelist);
	return (subshell);
}

int	update_exit_status(int status)
{
	// printf("%d\n", WIFEXITED(status));
	// printf("%d\n", WIFSTOPPED(status));
	// printf("%d\n", WSTOPSIG(status));
	return (g_exit_status = WEXITSTATUS(status));
}

int	waitpid_exit_status(pid_t pid)
{
	int	stat_loc;

	waitpid(pid, &stat_loc, 0);
	if (WIFSIGNALED(stat_loc))
	{
		if (WTERMSIG(stat_loc) == 2)
			return (g_exit_status = 130);
		if (WTERMSIG(stat_loc) == 3)
			return (g_exit_status = 131);
		if (WTERMSIG(stat_loc) == 9)
			return (g_exit_status = 1);
		if (WTERMSIG(stat_loc) == 13)
			return (g_exit_status = 1);
		return (g_exit_status = WTERMSIG(stat_loc));
	}
	return (g_exit_status = WEXITSTATUS(stat_loc));
}

// dprintf(2, "pid           %d\n", nodelist->pid);
// dprintf(2, "wait          %s\n", nodelist->table->cmd_argv[0]);
// dprintf(2, "stat_loc      %d\n", stat_loc);
// dprintf(2, "g_exit_status %d\n", g_exit_status);
int	launch_subshell(t_node *nodelist)
{
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		/* stdio_fildes_handler(RESTORE_STD_FILDES); */
		exit(executor(subshell_extract_nodelist(nodelist)));
	}
	waitpid_exit_status(nodelist->pid);
	return (EXIT_SUCCESS);
}

# include <sys/stat.h>

bool	is_a_directory(const char *path)
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
	if (ft_strchr(table->cmd_argv[0], '/') == NULL)
		exit(error(table->cmd_argv[0], "command not found", 127));
	if (is_a_directory(table->cmd_argv[0]))
		exit(error(table->cmd_argv[0], "Is a directory", 126));
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

int	pipeline_closing_command(t_node *nodelist)
{
	int	exit_status;

	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		if (nodelist->type == NODE_SUBSHELL)
			exit(executor(subshell_extract_nodelist(nodelist)));
		if (nodelist->table->builtin_id > 0)
			exit(execute_builtin(nodelist));
		exit(execute_command(nodelist->table));
	}
	exit_status = waitpid_exit_status(nodelist->pid);
	/* close old pipe stdin and clobber it with saved value */
	close(STDIN_FILENO); /* also works with RESTORE_STD_FILDES handler */
	while (wait(NULL) > 0)
		continue ;
	stdio_fildes_handler(RESTORE_STD_FILDES);
	return (exit_status);
}

int	launch_pipe(t_node *nodelist)
{
	/* int pipe_fd[2]; */
	/* pipe_handler(OPEN_PIPE_FILEDES) */
	if (pipe(nodelist->pipe) == -1)
		return (-1);
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		close(nodelist->pipe[0]);
		dup2(nodelist->pipe[1], STDOUT_FILENO);
		close(nodelist->pipe[1]);
		/* pipe_handler(DUP_PIPE_STDOUT); */
		/* pipe_handler(CLOSE_PIPE_FILEDES); */
		if (nodelist->type == NODE_SUBSHELL)
			exit(executor(subshell_extract_nodelist(nodelist)));
		if (nodelist->table->builtin_id > 0)
			exit(execute_builtin(nodelist));
		exit(execute_command(nodelist->table));
	}
	close(nodelist->pipe[1]);
	dup2(nodelist->pipe[0], STDIN_FILENO);
	close(nodelist->pipe[0]);
	/* pipe_handler(DUP_PIPE_STDIN); */
	/* pipe_handler(CLOSE_PIPE_FILEDES); */
	return (EXIT_SUCCESS);
}

t_node	*handle_pipeline(t_node *nodelist)
{
	nodelist = free_node(nodelist);
	if (nodelist->nexus == NODE_PIPE)
		return (nodelist);
	pipeline_closing_command(nodelist);
	return (node_handler(nodelist));
}

t_node	*node_handler(t_node *nodelist)
{
	nodelist = free_node(nodelist);
	if (nodelist == NULL)
		return (NULL);
	if (nodelist->type == NODE_PIPE)
		return (handle_pipeline(nodelist));
	while (wait(NULL) > 0)
		continue ;
	stdio_fildes_handler(RESTORE_STD_FILDES);
	if (node_is_conditional(nodelist->type))
		return (handle_conditional(nodelist));
	return (free_node(nodelist));
}

static int	execute_handler(t_node *nodelist)
{
	if (nodelist->nexus == NODE_PIPE)
		return (launch_pipe(nodelist));
	if (nodelist->type == NODE_SUBSHELL)
		return (launch_subshell(nodelist));
	// if (nodelist->type == NODE_ASSIGNMENT)
	// 	return (launch_assignment(nodelist));
	if (nodelist->type == NODE_COMMAND)
		return (launch_command(nodelist));
	return (EXIT_SUCCESS);
}

int	executor(t_node *nodelist)
{
	stdio_fildes_handler(SAVE_STD_FILDES);
	signal(SIGINT, &signal_ctrl_c_runtime);
	signal(SIGQUIT, &signal_ctrl_backslash);
	while (nodelist != NULL)
	{
		execute_handler(nodelist);
		nodelist = node_handler(nodelist);
	}
	signal(SIGINT, signal_ctrl_c_input);
	signal(SIGQUIT, SIG_IGN);
	stdio_fildes_handler(RESTORE_STD_FILDES);
	stdio_fildes_handler(CLOSE_STD_FILDES_DUPS);
	return (g_exit_status);
}
