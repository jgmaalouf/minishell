#include "minishell.h"

int	token_is_semicolon(t_tk_type type)
{
	return (type == TK_SEMICOLON || type == TK_DSEMICOLON);
}
