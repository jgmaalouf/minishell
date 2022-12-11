#include "minishell.h"

static void	remove_single_quotes(char **word, char *result, int *i)
{
	(*word)++;
	while (**word != '\'')
		result[(*i)++] = *(*word)++;
	(*word)++;
}

static void	remove_double_quotes(char **word, char *result, int *i)
{
	(*word)++;
	while (**word != '\"')
	{
		if (**word == '\\')
			if (*(*word + 1) == '\"' || *(*word + 1) == '\\')
				(*word)++;
		result[(*i)++] = *(*word)++;
	}
	(*word)++;
}

static char	*remove_quotes(char *word)
{
	char	*result;
	int		i;

	result = ft_calloc(ft_strlen(word) + 1, sizeof(char));
	if (result == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (*word != '\0')
	{
		if (*word == '\\' && word++)
			result[i++] = *word++;
		else if (*word == '\'')
			remove_single_quotes(&word, result, &i);
		else if (*word == '\"' && word++)
			remove_double_quotes(&word, result, &i);
		else
			result[i++] = *word++;
	}
	return (result);
}

char	*quote_removal(char *word)
{
	char	*result;

	if (ft_strchr(word, '\"') == NULL)
		if (ft_strchr(word, '\'') == NULL)
			if (ft_strchr(word, '\\') == NULL)
				return (word);
	result = remove_quotes(word);
	return (free(word), result);
}
