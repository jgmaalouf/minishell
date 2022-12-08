#include "minishell.h"

int	set_local_variable(const char *name, const char *value)
{
	char	**dict;

	if (getenv(name) != NULL)
		return (ft_setenv(name, value, 1));
	dict = dict_open();
	dict_set_val(dict, name, value);
	return (EXIT_SUCCESS);
}

int	variable_assignment(const char *assignment)
{
	char	*name;
	char	*value;

	value = (char *)assignment;
	name = ft_strsep(&value, "=");
	set_local_variable(name, value);
	return (EXIT_SUCCESS);
}
