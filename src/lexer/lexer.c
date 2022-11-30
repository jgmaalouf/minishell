#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	while (*line != '\0')
	{
		while (isspace(*line))
			line++;
		if (*line == '\0')
			return (tokens);
		new = tokenizer(&line);
		if (new == NULL)
			return (free_token_list(tokens));
		token_list_add_back(&tokens, new);
	}
	return (tokens);
}
