#include "minishell.h"

char	*find_closing_quote(const char *input)
{
	if (*input == '\'')
		return (strchr(input + 1, '\''));
	input++;
	while (*input != '\0')
	{
		if (*input == '\"')
			return ((char *)input);
		if (*input++ == '\\')
			input++;
	}
	return (NULL);
}
