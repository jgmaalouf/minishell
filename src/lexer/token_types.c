#include "minishell.h"

bool	token_is_simple_word(t_tk_type type)
{
	return (type == TK_WORD);
}

bool	token_is_word(t_tk_type type)
{
	if (type == TK_WORD)
		return (true);
	if (type == TK_ASSIGNMENT_WORD)
		return (true);
	return (false);
}

bool	token_is_redirection(t_tk_type type)
{
	if (type == TK_IO_NUMBER)
		return (true);
	if (type == TK_REDIRECT_INPUT)
		return (true);
	if (type == TK_REDIRECT_INPUT_HEREDOC)
		return (true);
	if (type == TK_REDIRECT_INPUT_OUTPUT)
		return (true);
	if (type == TK_REDIRECT_OUTPUT_TRUNC)
		return (true);
	if (type == TK_REDIRECT_OUTPUT_APPEND)
		return (true);
	if (type == TK_REDIRECT_OUTPUT_CLOBBER)
		return (true);
	return (false);
}

bool	token_is_logical_operand(t_tk_type type)
{
	if (type == TK_BACKGROUND || type == TK_PIPE)
		return (true);
	if (type == TK_LOGICAL_AND || type == TK_LOGICAL_OR)
		return (true);
	return (false);
}

bool	token_is_parenthesis(t_tk_type type)
{
	return (type == TK_OPEN_PARENTHESIS || type == TK_CLOSE_PARENTHESIS);
}
