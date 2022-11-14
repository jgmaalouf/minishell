#include "minishell.h"

bool	token_is_word(t_token_type type)
{
	return (type == WORD);
}

bool	token_is_logical_operand(t_token_type type)
{
	return (type == PIPE || type == LOGICAL_AND || type == LOGICAL_OR);
}

bool	token_is_redirection(t_token_type type)
{
	if (type == REDIRECT_INPUT_FILE || type == REDIRECT_INPUT_HEREDOC)
		return (true);
	if (type == REDIRECT_OUTPUT_TRUNC || type == REDIRECT_OUTPUT_APPEND)
		return (true);
	return (false);
}

bool	token_is_parenthesis(t_token_type type)
{
	return (type == OPEN_PARENTHESIS || type == CLOSE_PARENTHESIS);
}
