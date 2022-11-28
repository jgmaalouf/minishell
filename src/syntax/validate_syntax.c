#include "minishell.h"

int	valid_first_token(t_token_type type)
{
	return (!token_is_logical_operand(type) && type != CLOSE_PARENTHESIS);
}

int	validate_token_list(t_token *tokens)
{
	if (!valid_first_token(tokens->type))
		return (syntax_error_unexpected_token(tokens->val));
	while (tokens)
	{
		if (!validate_token(tokens))
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

int	match_parentheses(t_token *tokens)
{
	int	unmatched;

	unmatched = 0;
	while (tokens)
	{
		if (tokens->type == OPEN_PARENTHESIS)
			unmatched++;
		if (tokens->type == CLOSE_PARENTHESIS)
			unmatched--;
		if (unmatched < 0)
			return (syntax_error_unexpected_token(")"));
		tokens = tokens->next;
	}
	if (unmatched != 0)
			return (syntax_error_end_of_file());
	return (true);
}

int	validate_syntax(t_token *tokens)
{
	if (!validate_token_list(tokens))
		return (false);
	if (!match_parentheses(tokens))
		return (false);
	return (true);
}
