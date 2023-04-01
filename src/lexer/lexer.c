#include "minishell.h"

static void	tokenize_assignments(t_token *tokenlist)
{
	bool	eligible;

	eligible = true;
	while (tokenlist != NULL)
	{
		if (eligible && token_is_simple_word(tokenlist->type))
		{
			if (valid_parameter_assignment(tokenlist->val))
				tokenlist->type = TK_ASSIGNMENT_WORD;
			else
				eligible = false;
		}
		else if (token_is_redirection(tokenlist->type))
			eligible = false;
		else if (!token_is_word(tokenlist->type))
			eligible = true;
		tokenlist = tokenlist->next;
	}
}

t_token	*lexer(char *cmdline)
{
	t_token	*tokenlist;
	t_token	*new;

	tokenlist = NULL;
	while (*cmdline != '\0')
	{
		while (ft_isspace(*cmdline))
			cmdline++;
		if (*cmdline == '\0')
			return (tokenlist);
		new = tokenizer(&cmdline);
		if (new == NULL)
			return (free_tokenlist(tokenlist, 1));
		tokenlist_add_back(&tokenlist, new);
	}
	tokenize_assignments(tokenlist);
	return (tokenlist);
}
