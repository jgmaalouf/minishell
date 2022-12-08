#include "minishell.h"

char	*tilde_prefix(char *word)
{
	char	*prefix;

	prefix = word;
	while (*word != '\0' && *word != '/')
		word++;
	return (ft_strndup(prefix, word - prefix));
}

char	*expand_tilde_prefix(char *prefix)
{
	if (ft_strcmp(prefix, "~") == 0)
		return (getenv("HOME"));
	if (ft_strcmp(prefix, "~+") == 0)
		return (getenv("PWD"));
	if (ft_strcmp(prefix, "~-") == 0)
		return (getenv("OLDPWD"));
	return (NULL);
}

char	*tilde_expansion(char *word)
{
	char	*result;
	char	*prefix;
	char	*value;

	prefix = tilde_prefix(word);
	value = expand_tilde_prefix(prefix);
	if (value == NULL)
		result = word;
	else
	{
		result = ft_concat(value, word + ft_strlen(prefix));
		free(word);
	}
	free(prefix);
	return (result);
}
