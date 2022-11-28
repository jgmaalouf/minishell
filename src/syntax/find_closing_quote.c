#include "minishell.h"

char *find_closing_quote(char *input)
{
	if (*input == '\'')
		return (strchr(input + 1, *input));
	input++;
	while (*input != '\0')
	{
		if (*input == '\"')
			return (input);
		if (*input == '\\')
			input += 2;
		else
			input++;
	}
	return (NULL);
}
