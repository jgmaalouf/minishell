#include "minishell.h"

char	*find_closing_quote(const char *input)
{
	if (*input == '\'')
		return (ft_strchr(input + 1, '\''));
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

char	*find_unquoted_char(const char *input, int c)
{
	if (c == '\\')
		return (NULL);
	while (*input != '\0')
	{
		if (*input == c)
			return ((char *)input);
		else if (ft_isquote(*input))
			input = find_closing_quote(input) + 1;
		else if (*input++ == '\\')
			input++;
	}
	if (c == '\0')
		return ((char *)input);
	return (NULL);
}
