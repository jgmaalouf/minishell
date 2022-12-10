#include "minishell.h"

int	valid_first_token(t_token *token)
{
	if (token_is_logical_operand(token->type)
		|| token->type == TK_CLOSE_PARENTHESIS || token->type == TK_SEMICOLON)
		return (syntax_error_unexpected_token(token->val), false);
	return (true);
}

static int	valid_tokenlist(t_token *tokenlist)
{
	if (!valid_first_token(tokenlist))
		return (false);
	while (tokenlist != NULL)
	{
		if (!valid_token(tokenlist))
			return (false);
		tokenlist = tokenlist->next;
	}
	return (true);
}

static int	match_parentheses(t_token *tokenlist)
{
	int	unmatched;

	unmatched = 0;
	while (tokenlist != NULL)
	{
		if (tokenlist->type == TK_OPEN_PARENTHESIS)
			unmatched++;
		if (tokenlist->type == TK_CLOSE_PARENTHESIS)
			unmatched--;
		if (unmatched < 0)
			return (syntax_error_unexpected_token(")"), false);
		tokenlist = tokenlist->next;
	}
	if (unmatched != 0)
		return (syntax_error_end_of_file(), false);
	return (true);
}

int	syntax_validator(t_token *tokenlist)
{
	if (!valid_tokenlist(tokenlist))
		return (EXIT_FAILURE);
	if (!match_parentheses(tokenlist))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
