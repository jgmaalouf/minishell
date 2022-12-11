#include "minishell.h"

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

static void	nodelist_expand_block(t_node *node)
{
	if (node->type == NODE_SUBSHELL)
		node = node->next;
	while (node != NULL && !node_is_block_separator(node->type))
	{
		if (node->type != NODE_PIPE)
		{
			shell_expansion(node->tokenlist);
			t_token *tp = node->tokenlist; /* fix */
			node->table = create_command_table(&tp);
		}
		node = node->next;
	}
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
		nodelist = handle_conditional(nodelist);
	else
		nodelist = free_node(nodelist);
	nodelist_expand_block(nodelist);
	return (nodelist);
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
	nodelist_expand_block(nodelist);
	while (nodelist != NULL)
	{
		execute_handler(nodelist);
		nodelist = node_handler(nodelist);
	}
	signal(SIGINT, signal_ctrl_c_input);
	signal(SIGQUIT, SIG_IGN);
	stdio_fildes_handler(RESTORE_STD_FILDES);
	stdio_fildes_handler(CLOSE_STD_FILDES_DUPS);
	heredoc_handler(HEREDOC_DESTROY, NULL);
	return (g_exit_status);
}
