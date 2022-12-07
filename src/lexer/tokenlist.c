#include "minishell.h"

t_token	*new_token_node(int type, char *val)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	new->type = type;
	new->val = val;
	new->expanded = false;
	new->next = NULL;
	return (new);
}

void	tokenlist_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	*free_tokenlist(t_token *list, bool content)
{
	t_token	*next;

	while (list != NULL)
	{
		next = list->next;
		if (content == true)
			if (token_is_word(list->type))
				free(list->val);
		free(list);
		list = next;
	}
	return (NULL);
}
