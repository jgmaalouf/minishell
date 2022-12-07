#include "minishell.h"

static t_redir	*new_redirection_node(t_tk_type type)
{
	t_redir	*new;

	new = calloc(1, sizeof(t_cmd));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_token	*find_next_redirection(t_token *tokenlist)
{
	while (tokenlist != NULL)
	{
		if (token_is_command_separator(tokenlist->type))
			return (NULL);
		if (token_is_redirection(tokenlist->type))
			return (tokenlist);
		if (tokenlist->type == TK_IO_NUMBER)
			return (tokenlist);
		tokenlist = tokenlist->next;
	}
	return (NULL);
}

t_redir	*parse_redirections(t_token *tokenlist)
{
	t_redir	*redirlist;
	t_redir	*rlp;
	t_token	*found;

	found = find_next_redirection(tokenlist);
	if (found == NULL)
		return (NULL);
	redirlist = new_redirection_node(found->type);
	rlp = redirlist;
	while (1)
	{
		found = find_next_redirection(tokenlist);
		if (found == NULL)
			return (redirlist);
		rlp->next = new_redirection_node(found->type);
		rlp = rlp->next;
	}
}
