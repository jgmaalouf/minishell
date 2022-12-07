#include "minishell.h"

int	valid_variable_name(const char *name)
{
	if (ft_isdigit(*name))
		return (false);
	while (*name != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

int	valid_variable_identifier(const char *name)
{
	if (ft_isdigit(*name))
		return (false);
	while (*name != '\0' && *name != '=')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

int	valid_parameter_assignment(const char *word)
{
	if (find_unquoted_char(word, '=') == NULL)
		return (false);
	return (valid_variable_identifier(word));
}