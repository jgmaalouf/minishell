#include "minishell.h"

int	count_command_argc(t_token *tokenlist)
{
	int	count;

	count = 0;
	while (tokenlist != NULL)
	{
		if (token_is_command_separator(tokenlist->type))
			return (count);
		if (token_is_redirection(tokenlist->type))
		{
			if (tokenlist->type == TK_IO_NUMBER)
				tokenlist = tokenlist->next;
			tokenlist = tokenlist->next;
		}
		else if (token_is_simple_word(tokenlist->type))
			count++;
		tokenlist = tokenlist->next;
	}
	return (count);
}

int	count_assignment_argc(t_token *tokenlist)
{
	int	count;

	count = 0;
	while (tokenlist != NULL)
	{
		if (tokenlist->type != TK_ASSIGNMENT_WORD)
			return (count);
		if (token_is_redirection(tokenlist->type))
		{
			if (tokenlist->type == TK_IO_NUMBER)
				tokenlist = tokenlist->next;
			tokenlist = tokenlist->next;
		}
		count++;
		tokenlist = tokenlist->next;
	}
	return (count);
}
