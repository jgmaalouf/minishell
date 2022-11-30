#include "minishell.h"

void	shell_expansion(t_token *tokens)
{
	while (tokens)
	{
		if (token_is_word(tokens->type) && !tokens->expanded)
		{
			if (tokens->val[0] == '~')
				tokens->val = tilde_expansion(tokens->val);
			if (strchr(tokens->val, '$'))
				tokens->val = parameter_expansion(tokens->val);
			if (strchr(tokens->val, '*') || strchr(tokens->val, '?'))
				tokens = filename_expansion(tokens);
			if (!tokens->expanded)
				tokens->val = quote_removal(tokens->val);
		}
		tokens = tokens->next;
	}
}
