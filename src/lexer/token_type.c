#include "minishell.h"

int	reserved_shell_char(int c)
{
	if (c == '<' || c == '>')
		return (c);
	if (c == '|' || c == '&')
		return (c);
	if (c == '(' || c == ')')
		return (c);
	return (0);
}

bool	token_is_word(t_tk_type type)
{
	return (type == WORD);
}

bool	token_is_logical_operand(t_tk_type type)
{
	return (type == PIPE || type == LOGICAL_AND || type == LOGICAL_OR);
}

bool	token_is_redirection(t_tk_type type)
{
	if (type == REDIRECT_INPUT || type == REDIRECT_INPUT_HEREDOC)
		return (true);
	if (type == REDIRECT_OUTPUT_TRUNC || type == REDIRECT_OUTPUT_APPEND)
		return (true);
	return (false);
}

bool	token_is_parenthesis(t_tk_type type)
{
	return (type == OPEN_PARENTHESIS || type == CLOSE_PARENTHESIS);
}
