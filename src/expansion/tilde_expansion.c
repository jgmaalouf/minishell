#include "minishell.h"

char	*tilde_prefix(char *word)
{
	char	*prefix;

	prefix = word;
	while (*word != '\0' && *word != '/')
		word++;
	return (strndup(prefix, word - prefix));
}

char	*expand_tilde_prefix(char *prefix)
{
	if (strcmp(prefix, "~") == 0)
		return (getenv("HOME"));
	if (strcmp(prefix, "~+") == 0)
		return (getenv("PWD"));
	if (strcmp(prefix, "~-") == 0)
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
		result = ft_concat(value, word + strlen(prefix));
		free(word);
	}
	free(prefix);
	return (result);
}
