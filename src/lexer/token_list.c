#include "minishell.h"

t_token	*new_token_node(int type, char *val)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		exit(fatal_error());
	new->type = type;
	new->val = val;
	new->expanded = false;
	new->next = NULL;
	return (new);
}

void	token_list_add_back(t_token **list, t_token *new)
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

void	*free_token_list(t_token *tokens)
{
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (token_is_word(tokens->type))
			free(tokens->val);
		free(tokens);
		tokens = next;
	}
	return (NULL);
}
