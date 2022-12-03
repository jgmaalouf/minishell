#include "minishell.h"

static int	valid_first_token(t_tk_type type)
{
	return (!token_is_logical_operand(type) && type != TK_CLOSE_PARENTHESIS);
}

static int	valid_token_list(t_token *tokens)
{
	if (!valid_first_token(tokens->type))
		return (syntax_error_unexpected_token(tokens->val), false);
	while (tokens)
	{
		if (!valid_token(tokens))
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

static int	match_parentheses(t_token *tokens)
{
	int	unmatched;

	unmatched = 0;
	while (tokens)
	{
		if (tokens->type == TK_OPEN_PARENTHESIS)
			unmatched++;
		if (tokens->type == TK_CLOSE_PARENTHESIS)
			unmatched--;
		if (unmatched < 0)
			return (syntax_error_unexpected_token(")"), false);
		tokens = tokens->next;
	}
	if (unmatched != 0)
		return (syntax_error_end_of_file(), false);
	return (true);
}

int	syntax_validator(t_token *tokens)
{
	if (!valid_token_list(tokens))
		return (EXIT_FAILURE);
	if (!match_parentheses(tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
