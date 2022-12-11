#include "minishell.h"

static void	nodelist_expand_block(t_node *node)
{
	while (node != NULL && !node_is_block_separator(node->type))
	{
		if (node->type != NODE_SUBSHELL && node->type != NODE_PIPE)
		{
			shell_expansion(node->tokenlist);
			node->table = create_command_table(node->tokenlist);
		}
		node = node->next;
	}
}

static t_node	*free_processed_nodes(t_node *nodelist)
{
	if (nodelist->nexus == NODE_NULL)
		return (free_node(nodelist));
	if (nodelist->type == NODE_ASSIGNMENT)
	{
		nodelist = free_node(nodelist);
		if (nodelist->type == NODE_COMMAND)
			return (free_node(nodelist));
		else
			return (nodelist);
	}
	return (free_node(nodelist));
}

t_node	*node_handler(t_node *nodelist)
{
	nodelist = free_processed_nodes(nodelist);
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
	if (nodelist->type == NODE_ASSIGNMENT)
		return (launch_assignment(nodelist));
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
