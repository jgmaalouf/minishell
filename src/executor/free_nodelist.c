#include "minishell.h"

static void	free_redirlist(t_redir *list)
{
	t_redir	*next;

	while (list != NULL)
	{
		next = list->next;
		free((char *)list->n);
		free((char *)list->path);
		free(list);
		list = next;
	}
}

static void	free_command_table(t_cmd *table)
{
	free((char *)table->cmd_path);
	if (table->cmd_argc > 0)
		strarr_free((char **)table->cmd_argv);
	free_redirlist(table->redirlist);
}

void	*free_nodelist(t_node *list)
{
	t_node	*next;

	while (list != NULL)
	{
		next = list->next;
		if (list->sub != NULL)
			free_nodelist(list->sub);
		if (list->table != NULL)
			free_command_table(list->table);
		free(list);
		list = next;
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
	return (free(node), next);
}
