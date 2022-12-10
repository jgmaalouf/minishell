#include "minishell.h"

static int	valid_word(t_token *token)
{
	if (token->next == NULL)
		return (true);
	if (token->next->type == TK_OPEN_PARENTHESIS)
	{
		if (token->next->next == NULL)
			return (syntax_error_unexpected_token("newline"), false);
		return (syntax_error_unexpected_token(token->next->next->val), false);
	}
	return (true);
}

static int	valid_logical_operand(t_token *token)
{
	if (token->next == NULL)
		return (syntax_error_end_of_file(), false);
	if (token_is_logical_operand(token->next->type))
		return (syntax_error_unexpected_token(token->next->val), false);
	if (token->next->type == TK_SEMICOLON)
		return (syntax_error_unexpected_token(token->next->val), false);
	if (token->next->type == TK_CLOSE_PARENTHESIS)
		return (syntax_error_unexpected_token(")"), false);
	return (true);
}

static int	valid_redirection(t_token *token)
{
	if (token->next == NULL)
		return (syntax_error_unexpected_token("newline"), false);
	if (token->type == TK_IO_NUMBER)
		return (true);
	if (token->next->type != TK_WORD)
		return (syntax_error_unexpected_token(token->next->val), false);
	return (true);
}

static int	valid_parenthesis(t_token *token)
{
	if (token->type == TK_OPEN_PARENTHESIS)
	{
		if (token->next == NULL)
			return (syntax_error_end_of_file(), false);
		if (token->next->type == TK_CLOSE_PARENTHESIS)
			return (syntax_error_unexpected_token(")"), false);
		if (token_is_logical_operand(token->next->type))
			return (syntax_error_unexpected_token(token->next->val), false);
		return (true);
	}
	if (token->type == TK_CLOSE_PARENTHESIS)
	{
		if (token->next == NULL)
			return (true);
		if (token->next->type == TK_OPEN_PARENTHESIS)
			return (syntax_error_unexpected_token("("), false);
		if (token_is_word(token->next->type))
			return (syntax_error_unexpected_token(token->next->val), false);
		return (true);
	}
	return (false);
}

int	valid_token(t_token *token)
{
	if (token_is_word(token->type))
		return (valid_word(token));
	if (token_is_logical_operand(token->type))
		return (valid_logical_operand(token));
	if (token_is_redirection(token->type))
		return (valid_redirection(token));
	if (token_is_parenthesis(token->type))
		return (valid_parenthesis(token));
	if (token->type == TK_SEMICOLON)
	{
		if (token->next == NULL)
			return (true);
		return (valid_first_token(token->next));
	}
	return (true);
}
