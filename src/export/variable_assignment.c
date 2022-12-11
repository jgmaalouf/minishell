#include "minishell.h"

int	variable_assignment(const char *assignment)
{
	char	*name;
	char	*value;

	split_variable((char *)assignment, &name, &value);
	if (ft_getenv(name) == NULL)
		return (set_lexicon_entry(name, value, false));
	ft_setenv(name, value, 1);
	return (free(name), free(value), EXIT_SUCCESS);
}
