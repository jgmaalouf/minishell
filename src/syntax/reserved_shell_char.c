#include "minishell.h"

bool	reserved_shell_char(int c)
{
	if (ft_isspace(c))
		return (true);
	if (c == '<' || c == '>')
		return (true);
	if (c == '|' || c == '&')
		return (true);
	if (c == '(' || c == ')')
		return (true);
	if (c == ';')
		return (true);
	return (false);
}
