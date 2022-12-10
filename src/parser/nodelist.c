#include "minishell.h"

static t_node	*new_node(t_node_type type)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	new->type = type;
	return (new);
}

static t_node	*node_insert_tokenlist(t_token **tokenlist)
{
	t_node	*new;
	t_token	*tp;

	new = new_node(convert_tk_type((*tokenlist)->type));
	new->tokenlist = *tokenlist;
	if (node_is_command_separator(new->type))
	{
		tp = new->tokenlist->next;
		new->tokenlist->next = NULL;
		*tokenlist = tp;
		return (new);
	}
	tp = new->tokenlist;
	while (tp->next != NULL)
	{
		if (token_is_command_separator(tp->next->type))
		{
			*tokenlist = tp->next;
			tp->next = NULL;
			return (new);
		}
		tp = tp->next;
	}
	*tokenlist = NULL;
	return (new);
}

static void	insert_nodes(t_node *node, t_token **tokenlist)
{
	while (*tokenlist != NULL)
	{
		if (node->type == NODE_SUBSHELL)
		{
			node->sub = node_insert_tokenlist(tokenlist);
			insert_nodes(node->sub, tokenlist);
			*tokenlist = (*tokenlist)->next;
			if (*tokenlist == NULL)
				return ;
		}
		if ((*tokenlist)->type == TK_CLOSE_PARENTHESIS)
			return ;
		node->next = node_insert_tokenlist(tokenlist);
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

	nodelist = node_insert_tokenlist(&tokenlist);
	insert_nodes(nodelist, &tokenlist);
	assign_nexuses(nodelist);
	return (nodelist);
}
