#include "minishell.h"

static char	*bad_substitution(const char *line)
{
	char	*dollar;

	dollar = strchr(line, '$');
	if (dollar == NULL)
		return (false);
	if (dollar[1] != '{')
		return (bad_substitution(dollar + 1));
	if (dollar[2] == '}')
		return (dollar);
	if (strchr(dollar, '}') == NULL)
		return (dollar);
	line = &dollar[2];
	while (*line)
	{
		if (*line == '}')
			return (bad_substitution(line + 1));
		if (!isalnum(*line) && *line != '_')
			if (*line != '?')
				return (dollar);
		line++;
	}
	return (NULL);
}

int	find_bad_substitution(char *line)
{
	char	*found;
	char	*closing;

	found = bad_substitution(line);
	if (found == NULL)
		return (false);
	closing = strchr(found, '}');
	if (closing == NULL)
		return (syntax_error_matching('}'), true);
	while (*closing != '\0' && !isspace(*closing))
		closing++;
	*closing = '\0';
	return (syntax_error_bad_substitution(found), true);
}
