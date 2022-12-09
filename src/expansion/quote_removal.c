#include "minishell.h"

// char	*remove_single_quotes(char *word);
// char	*remove_double_quotes(char *word);

char	*remove_quotes(char *word)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_calloc(ft_strlen(word) + 1, sizeof(char));
	if (result == NULL)
		exit(fatal_error(ENOMEM));
	while (*word != '\0')
	{
		if (*word == '\\' && word++)
			result[i++] = *word++;
		else if (*word == '\'' && word++)
		{
			while (*word != '\'')
				result[i++] = *word++;
			word++;
		}
		else if (*word == '\"' && word++)
		{
			while (*word != '\"')
			{
				if (*word == '\\')
					if (*(word + 1) == '\"' || *(word + 1) == '\\')
						word++;
				result[i++] = *word++;
			}
			word++;
		}
		else
			result[i++] = *word++;
	}
	return (result);
}

char	*quote_removal(char *word)
{
	char	*result;

	if (ft_strchr(word, '\"') == NULL && ft_strchr(word, '\'') == NULL)
		if (ft_strchr(word, '\\') == NULL)
			return (word);
	result = remove_quotes(word);
	return (free(word), result);
}
