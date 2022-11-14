#include "minishell.h"

int	bad_substitution(char *word)
{
	char	*dollar;

	dollar = strchr(word, '$');
	if (dollar == NULL)
		return (false);
	if (dollar[1] != '{')
		return (bad_substitution(dollar + 1));
	if (dollar[2] == '}')
		return (true);
	word = &dollar[2];
	while (*word)
	{
		if (*word == '}')
			return (bad_substitution(word + 1));
		if (!isalnum(*word) && *word != '_')
			return (true);
		word++;
	}
	return (syntax_error_matching('}'), true);
}

int	valid_word(t_token *token)
{
	/* return (token->next->type != OPEN_PARENTHESIS); */
	if (bad_substitution(token->val))
		return (syntax_error_bad_substitution(token->val));
	if (token->next == NULL)
		return (true);
	if (token->next->type == OPEN_PARENTHESIS)
	{
		if (token->next->next == NULL)
			return (syntax_error_unexpected_token("newline"));
		return (syntax_error_unexpected_token(token->next->next->val));
	}
	return (true);
}

int	valid_logical_operand(t_token *token)
{
	if (token->next == NULL)
		return (syntax_error_end_of_file());
	if (token_is_logical_operand(token->next->type))
		return (syntax_error_unexpected_token(token->next->val));
	if (token->next->type == CLOSE_PARENTHESIS)
		return (syntax_error_unexpected_token(")"));
	return (true);
}

int	valid_redirection(t_token *token)
{
	if (token->next == NULL)
		return (syntax_error_unexpected_token("newline"));
	if (token->next->type != WORD)
		return (syntax_error_unexpected_token(token->next->val));
	return (true);
}

int	valid_parenthesis(t_token *token)
{
	if (token->type == OPEN_PARENTHESIS)
	{
		if (token->next == NULL)
			return (syntax_error_end_of_file());
		if (token->next->type == CLOSE_PARENTHESIS)
			return (syntax_error_unexpected_token(")"));
		if (token_is_logical_operand(token->next->type))
			return (syntax_error_unexpected_token(token->next->val));
		return (true);
	}
	if (token->type == CLOSE_PARENTHESIS)
	{
		if (token->next == NULL)
			return (true);
		if (token->next->type == OPEN_PARENTHESIS)
			return (syntax_error_unexpected_token("("));
		if (token->next->type == WORD)
			return (syntax_error_unexpected_token(token->next->val));
		return (true);
	}
	return (false);
}

int	validate_token(t_token *token)
{
	if (token_is_word(token->type))
		return (valid_word(token));
	if (token_is_logical_operand(token->type))
		return (valid_logical_operand(token));
	if (token_is_redirection(token->type))
		return (valid_redirection(token));
	if (token_is_parenthesis(token->type))
		return (valid_parenthesis(token));
	return (false);
}




int	valid_first_token(t_token_type type)
{
	return (!token_is_logical_operand(type) && type != CLOSE_PARENTHESIS);
}

int	valid_last_token(t_token_type type)
{
	return (type == WORD || type == CLOSE_PARENTHESIS);
}

int	validate_token_list(t_token *tokens)
{
	if (!valid_first_token(tokens->type))
		return (syntax_error_unexpected_token(tokens->val));
	while (tokens->next)
	{
		if (!validate_token(tokens))
			return (false);
		tokens = tokens->next;
	}
	if (!valid_last_token(tokens->type))
		return (validate_token(tokens));
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
