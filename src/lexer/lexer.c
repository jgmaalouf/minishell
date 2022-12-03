#include "minishell.h"

static int	valid_assignment(char *word)
{
	if (find_unquoted_char(word, '=') == NULL)
		return (false);
	if (ft_isdigit(*word))
		return (false);
	while (*word != '=')
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (false);
		word++;
	}
	return (true);
}

static void	tokenize_assignments(t_token *tokens)
{
	bool	eligible;

	eligible = true;
	while (tokens != NULL)
	{
		if (eligible && token_is_basic_word(tokens->type))
		{
			if (valid_assignment(tokens->val))
				tokens->type = TK_ASSIGNMENT_WORD;
			else
				eligible = false;
		}
		else if (token_is_redirection(tokens->type))
			eligible = false;
		else if (!token_is_word(tokens->type))
			eligible = true;
		tokens = tokens->next;
	}
}

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
	tokenize_assignments(tokens);
	return (tokens);
}
