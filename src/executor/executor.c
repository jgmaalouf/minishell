#include "minishell.h"

int	update_exit_status(int status)
{
	/* man waitpid */
	// printf("%d\n", status);

	// printf("%d\n", WIFEXITED(status));
	// printf("%d\n", WIFSIGNALED(status));
	// printf("%d\n", WIFSTOPPED(status));
	// printf("%d\n", WEXITSTATUS(status));
	// printf("%d\n", WTERMSIG(status));
	// printf("%d\n", WSTOPSIG(status));
	return (g_exit_status = WEXITSTATUS(status));
}

int	launch_subshell(t_node *nodelist)
{
	t_node	*subshell;

	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		subshell = nodelist->sub;
		free_nodelist(nodelist->next);
		free(nodelist);
		exit(executor(subshell));
	}
	return (EXIT_SUCCESS);
}

int	execute_command(t_cmd *table)
{
	extern char	**environ;

	table->cmd_path = find_cmd_path(table->cmd_argv[0]);
	if (table->cmd_path == NULL)
		return (error(table->cmd_argv[0], "command not found", 127));
	execve(table->cmd_path, table->cmd_argv, environ);
	return (-1);
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
	return (EXIT_SUCCESS);
}

int	launch_command_subshell(t_node *nodelist)
{
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		if (nodelist->table->builtin_id > 0)
			exit(execute_builtin(nodelist));
		exit(execute_command(nodelist->table));
	}
	return (EXIT_SUCCESS);
}

int	launch_pipe(t_node *nodelist)
{
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		close(nodelist->table->pipe[0]);
		dup2(nodelist->table->pipe[1], STDOUT_FILENO);
		close(nodelist->table->pipe[1]);
		/* pipe_handler(DUP_PIPE_STDOUT); */
		/* pipe_handler(CLOSE_PIPE_FILEDES); */
		if (nodelist->table->builtin_id > 0)
			exit(execute_builtin(nodelist));
		exit(execute_command(nodelist->table));
	}
	close(nodelist->table->pipe[1]);
	dup2(nodelist->table->pipe[0], STDIN_FILENO);
	close(nodelist->table->pipe[0]);
	/* pipe_handler(DUP_PIPE_STDIN); */
	/* pipe_handler(CLOSE_PIPE_FILEDES); */
	return (EXIT_SUCCESS);
}

int	create_pipe(t_node *nodelist)
{
	/* pipe_handler(OPEN_PIPE_FILEDES) */
	pipe(nodelist->table->pipe);
	if (launch_pipe(nodelist) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

t_node	*handle_pipe(t_node *nodelist)
{
	if (nodelist->next->nexus == NODE_PIPE)
		return (free_node(nodelist));
	nodelist = free_node(nodelist);
	launch_command_subshell(nodelist);
	return (next_node(nodelist));
}

t_node	*next_node(t_node *nodelist)
{
	// pid_t	pid;
	int		stat_loc;

	// pid = nodelist->pid;
	if (nodelist->pid != 0)
	{
		// waitpid(nodelist->pid, &stat_loc, WNOHANG);
		// waitpid(nodelist->pid, NULL, 0);
		while (wait(&stat_loc) > 0);
		// update_exit_status(stat_loc);
	}
	nodelist = free_node(nodelist);
	if (nodelist == NULL)
		return (NULL);
	if (nodelist->type == NODE_PIPE)
		return (handle_pipe(nodelist));
	if (node_is_conditional(nodelist->type))
		return (handle_conditional(nodelist));
	if (nodelist->type == NODE_SEMICOLON)
		return (free_node(nodelist));
	return (nodelist);
}

static int	execute(t_node *nodelist)
{
	if (nodelist->type == NODE_SUBSHELL)
		return (launch_subshell(nodelist));
	if (nodelist->nexus == NODE_PIPE)
		return (create_pipe(nodelist));
	// if (nodelist->type == NODE_ASSIGNMENT)
	// 	return (execute_assignment(nodelist));
	if (nodelist->type == NODE_COMMAND)
		return (launch_command(nodelist));
	return (EXIT_SUCCESS);
}

int	executor(t_node	*nodelist)
{
	stdio_fildes_handler(SAVE_STD_FILDES);
	while (nodelist != NULL)
	{
		// if (nodelist->nexus != NODE_PIPE)
		// 	stdio_fildes_handler(RESTORE_STD_FILDES);
		execute(nodelist);
		nodelist = next_node(nodelist);
	}
	// int	stat_loc = 0;
	// update_exit_status(stat_loc);
	// dprintf(2, "done\n");
	stdio_fildes_handler(RESTORE_STD_FILDES);
	stdio_fildes_handler(CLOSE_STD_FILDES_DUPS);
	return (EXIT_SUCCESS);
}
