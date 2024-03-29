#include "minishell.h"

static char	*last_exit_status(void)
{
	char	*exit_status;

	ft_asprintf(&exit_status, "%d", g_exit_status);
	return (exit_status);
}

static char	*find_variable(char *name)
{
	char	*value;

	value = ft_getenv(name);
	if (value != NULL)
		return (value);
	return (get_lexicon_entry(name));
}

char	*expand_dollar_variable(char *name)
{
	char	*value;

	if (ft_strcmp(name, "$") == 0)
		return (name);
	if (ft_strcmp(name, "$$") == 0)
		return (free(name), ft_strdup("getpid()"));
	if (ft_strncmp(name, "$?", 2) == 0)
		return (free(name), last_exit_status());
	value = find_variable(name + 1);
	if (value == NULL)
		value = "";
	return (free(name), ft_strdup(value));
}
