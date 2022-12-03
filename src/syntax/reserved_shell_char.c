#include "minishell.h"

int	reserved_shell_char(int c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '<' || c == '>')
		return (1);
	if (c == '|' || c == '&')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}
