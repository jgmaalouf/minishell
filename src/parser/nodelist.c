#include "minishell.h"

static t_node_type	convert_tk_type(t_tk_type type)
{
	if (type == TK_WORD)
		return (NODE_COMMAND);
	if (type == TK_ASSIGNMENT_WORD)
		return (NODE_ASSIGNMENT);
	if (token_is_redirection(type))
		return (NODE_COMMAND);
	if (type == TK_PIPE)
		return (NODE_PIPE);
	if (type == TK_LOGICAL_AND)
		return (NODE_AND_IF);
	if (type == TK_LOGICAL_OR)
		return (NODE_OR_IF);
	if (type == TK_OPEN_PARENTHESIS)
		return (NODE_SUBSHELL);
	if (type == TK_SEMICOLON)
		return (NODE_SEMICOLON);
	return (NODE_NULL);
}

bool	node_requires_command_table(t_node_type type)
{
	return (type == NODE_COMMAND || type == NODE_ASSIGNMENT);
}

static t_node	*new_node(t_token **tokenlist)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	new->type = convert_tk_type((*tokenlist)->type);
	if (node_requires_command_table(new->type))
		new->table = create_command_table(tokenlist);
	else
		*tokenlist = (*tokenlist)->next;
	return (new);
}

static void	insert_nodes(t_node *node, t_token **tokenlist)
{
	while (*tokenlist != NULL)
	{
		if (node->type == NODE_SUBSHELL)
		{
			node->sub = new_node(tokenlist);
			insert_nodes(node->sub, tokenlist);
			*tokenlist = (*tokenlist)->next;
			if (*tokenlist == NULL)
				return ;
		}
		if ((*tokenlist)->type == TK_CLOSE_PARENTHESIS)
			return ;
		node->next = new_node(tokenlist);
		node = node->next;
	}
}

static void	assign_nexuses(t_node *nodelist)
{
	while (nodelist != NULL)
	{
		if (nodelist->sub != NULL)
			assign_nexuses(nodelist->sub);
		if (nodelist->next == NULL)
			return ;
		nodelist->nexus = nodelist->next->type;
		nodelist = nodelist->next;
	}
}

t_node	*create_nodelist(t_token *tokenlist)
{
	t_node	*nodelist;

	nodelist = new_node(&tokenlist);
	insert_nodes(nodelist, &tokenlist);
	assign_nexuses(nodelist);
	return (nodelist);
}
