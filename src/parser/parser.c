#include "minishell.h"

/* arithmetic_expansion() */

char	*remove_quotes(char *word)
{
	char	*result;
	char	quote;
	int		i;

	i = 0;
	result = calloc(strlen(word) + 1, sizeof(char));
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
		{
			quote = *(word++);
			while (*word != quote)
				result[i++] = *(word++);
			word++;
		}
		else if (*word == '\\' && word++)
		{
			result[i++] = *word;
			if (*word != '\0')
				word++;
		}
		else
			result[i++] = *(word++);
	}
	result[i] = '\0'; /* calloc */
	return (result);
}

/* export TESTVAR=' this is a "quoted" string' */
char	*quote_removal(char *word)
{
	char	*result;

	result = remove_quotes(word);
	free(word);
	return (result);
}

void	shell_expansion(t_token *tokens, t_env *env)
{
	while (tokens)
	{
		if (token_is_word(tokens->type))
		{
			if (tokens->val[0] == '~')
				tokens->val = tilde_expansion(tokens->val);
			if (strchr(tokens->val, '$'))
				tokens->val = parameter_expansion(tokens->val, env);
			if (strchr(tokens->val, '*') || strchr(tokens->val, '?'))
				tokens = filename_expansion(tokens);
			if (strchr(tokens->val, '\'') || strchr(tokens->val, '\"') || strchr(tokens->val, '\\'))
				tokens->val = quote_removal(tokens->val);
		}
		tokens = tokens->next;
	}
}

int	parser(char *line, t_env *env)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	// log_print_tokens(tokens);
	if (validate_syntax(tokens))
		return (free_tokens(tokens), EXIT_FAILURE);
	shell_expansion(tokens, env);
	tokens = free_tokens(tokens);
	return (EXIT_SUCCESS);
}
