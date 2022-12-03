#include "minishell.h"

static char	*bad_substitution(const char *line)
{
	char	*dollar;

	dollar = ft_strchr(line, '$');
	if (dollar == NULL)
		return (false);
	if (dollar[1] != '{')
		return (bad_substitution(dollar + 1));
	if (dollar[2] == '}')
		return (dollar);
	if (ft_strchr(dollar, '}') == NULL)
		return (dollar);
	line = &dollar[2];
	while (*line != '\0')
	{
		if (*line == '}')
			return (bad_substitution(line + 1));
		if (!ft_isalnum(*line) && *line != '_')
			if (*line != '?')
				return (dollar);
		line++;
	}
	return (NULL);
}

int	find_bad_substitution(char *line)
{
	char	*found;
	char	*rbrace;

	found = bad_substitution(line);
	if (found == NULL)
		return (false);
	rbrace = ft_strchr(found, '}');
	if (rbrace == NULL)
		return (syntax_error_matching('}'), true);
	while (*rbrace != '\0' && !ft_isspace(*rbrace))
		rbrace++;
	*rbrace = '\0';
	return (syntax_error_bad_substitution(found), true);
}
