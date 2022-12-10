#include "minishell.h"

static void	free_redirlist(t_redir *redirlist)
{
	t_redir	*next;

	while (redirlist != NULL)
	{
		next = redirlist->next;
		free((char *)redirlist->n);
		free((char *)redirlist->path);
		free(redirlist);
		redirlist = next;
	}
}

static void	free_command_table(t_cmd *table)
{
	free((char *)table->cmd_path);
	if (table->cmd_argc > 0)
		strarr_free((char **)table->cmd_argv);
	free_redirlist(table->redirlist);
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
		free_tokenlist(nodelist->tokenlist, 0);
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
	free_tokenlist(node->tokenlist, 0);
	return (free(node), next);
}
