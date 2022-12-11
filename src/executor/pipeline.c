#include "minishell.h"

int	launch_pipe(t_node *nodelist)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (nodelist->type == NODE_SUBSHELL)
			exit(executor(subshell_extract_nodelist(nodelist)));
		if (nodelist->table->builtin_id > 0)
			exit(execute_builtin(nodelist));
		exit(execute_command(nodelist->table));
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}

static int	pipeline_closing_command(t_node *nodelist)
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
	stdio_fildes_handler(RESTORE_STD_FILDES);
	while (wait(NULL) > 0)
		continue ;
	return (exit_status);
}

t_node	*handle_pipeline(t_node *nodelist)
{
	nodelist = free_node(nodelist);
	if (nodelist->nexus == NODE_PIPE)
		return (nodelist);
	pipeline_closing_command(nodelist);
	return (node_handler(nodelist));
}
