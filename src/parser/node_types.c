#include "minishell.h"

t_node_type	convert_tk_type(t_tk_type type)
{
	if (type == TK_WORD)
		return (NODE_COMMAND);
	if (type == TK_ASSIGNMENT_WORD)
		return (NODE_ASSIGNMENT);
	if (token_is_redirection(type))
		return (NODE_COMMAND);
	if (type == TK_PIPE)
		return (NODE_PIPE);
	if (type == TK_LOGICAL_AND)
		return (NODE_AND_IF);
	if (type == TK_LOGICAL_OR)
		return (NODE_OR_IF);
	if (type == TK_OPEN_PARENTHESIS)
		return (NODE_SUBSHELL);
	if (type == TK_SEMICOLON)
		return (NODE_SEMICOLON);
	return (NODE_NULL);
}

bool	node_is_block_separator(t_node_type type)
{
	return (node_is_conditional(type) || type == NODE_SEMICOLON);
}

bool	node_is_command_separator(t_node_type type)
{
	return (type != NODE_COMMAND && type != NODE_ASSIGNMENT);
}

bool	token_is_command_separator(t_tk_type type)
{
	return (!token_is_word(type) && !token_is_redirection(type));
}

bool	node_is_conditional(t_node_type type)
{
	return (type == NODE_AND_IF || type == NODE_OR_IF);
}
