#include "minishell.h"

char	*remove_quotes(char *word)
{
	char	*result;
	int		i;

	i = 0;
	result = calloc(strlen(word) + 1, sizeof(char));
	while (*word)
	{
		if (*word == '\'' && word++)
		{
			while (*word != '\'')
				result[i++] = *word++;
			word++;
		}
		if (*word == '\"' && word++)
		{
			while (*word != '\"')
			{
				if (*word == '\\')
					word++;
				result[i++] = *word++;
			}
			word++;
		}
		else if (*word == '\\' && word++)
		{
			result[i++] = *word;
			if (*word != '\0')
				word++;
		}
		else
			result[i++] = *word++;
	}
	return (result);
}

/* export MYVAR='this is a "quoted" string' */
char	*quote_removal(char *word)
{
	char	*result;

	result = remove_quotes(word);
	free(word);
	return (result);
}
