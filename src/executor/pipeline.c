#include "minishell.h"

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
	/* close old pipe stdin and clobber it with saved value */
	close(STDIN_FILENO); /* also works with RESTORE_STD_FILDES handler */
	while (wait(NULL) > 0)
		continue ;
	stdio_fildes_handler(RESTORE_STD_FILDES);
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
