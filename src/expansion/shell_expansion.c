#include "minishell.h"

static int	valid_glob_pattern(char *word)
{
	while (*word != '\0')
	{
		if (*word == '*' || *word == '?')
			return (true);
		else if (ft_isquote(*word))
			word = find_closing_quote(word) + 1;
		else if (*word++ == '\\')
			word++;
	}
	return (false);
}

void	shell_expansion(t_token *tokenlist)
{
	while (tokenlist != NULL)
	{
		if (token_is_word(tokenlist->type) && !tokenlist->expanded)
		{
			if (tokenlist->val[0] == '~')
				tokenlist->val = tilde_expansion(tokenlist->val);
			if (ft_strchr(tokenlist->val, '$') && ++(tokenlist->expanded))
				tokenlist->val = parameter_expansion(tokenlist->val);
			if (valid_glob_pattern(tokenlist->val))
				tokenlist = filename_expansion(tokenlist);
			if (!tokenlist->expanded)
				tokenlist->val = quote_removal(tokenlist->val);
		}
		tokenlist = tokenlist->next;
	}
}
