#include "minishell.h"

static int	evaluate_conditional(t_node_type condition)
{
	if (condition == NODE_AND_IF)
		return (g_exit_status == 0);
	if (condition == NODE_OR_IF)
		return (g_exit_status != 0);
	return (errno = EINVAL, -1);
}

t_node	*handle_conditional(t_node *nodelist)
{
	t_node_type	condition;

	if (evaluate_conditional(nodelist->type))
		return (free_node(nodelist));
	if (nodelist->type == NODE_AND_IF)
		condition = NODE_OR_IF;
	if (nodelist->type == NODE_OR_IF)
		condition = NODE_AND_IF;
	while (nodelist != NULL)
	{
		if (nodelist->type == condition)
			return (free_node(nodelist));
		if (nodelist->type == NODE_SEMICOLON)
			return (free_node(nodelist));
		nodelist = free_node(nodelist);
	}
	return (NULL);
}
