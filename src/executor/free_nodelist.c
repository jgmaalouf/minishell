#include "minishell.h"

static void	free_redirlist(t_redir *redirlist)
{
	t_redir	*next;

	while (redirlist != NULL)
	{
		next = redirlist->next;
		free(redirlist);
		redirlist = next;
	}
}

static void	free_command_table(t_cmd *table)
{
	free((char *)table->cmd_path);
	free((char **)table->cmd_argv);
	free_redirlist(table->redirlist);
	free(table);
}

void	*free_nodelist(t_node *nodelist)
{
	t_node	*next;

	while (nodelist != NULL)
	{
		next = nodelist->next;
		if (nodelist->sub != NULL)
			free_nodelist(nodelist->sub);
		if (nodelist->table != NULL)
			free_command_table(nodelist->table);
		free_tokenlist(nodelist->tokenlist, 1);
		free(nodelist);
		nodelist = next;
	}
	return (NULL);
}

t_node	*free_node(t_node *node)
{
	t_node	*next;

	next = node->next;
	if (node->sub != NULL)
		free_nodelist(node->sub);
	else if (node->table != NULL)
		free_command_table(node->table);
	free_tokenlist(node->tokenlist, 1);
	return (free(node), next);
}
