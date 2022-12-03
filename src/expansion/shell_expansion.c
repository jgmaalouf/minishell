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

void	shell_expansion(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (token_is_word(tokens->type) && !tokens->expanded)
		{
			if (tokens->val[0] == '~')
				tokens->val = tilde_expansion(tokens->val);
			if (find_unquoted_char(tokens->val, '$') != NULL)
				tokens->val = parameter_expansion(tokens->val);
			if (valid_glob_pattern(tokens->val))
				tokens = filename_expansion(tokens);
			if (!tokens->expanded)
				tokens->val = quote_removal(tokens->val);
		}
		tokens = tokens->next;
	}
}
