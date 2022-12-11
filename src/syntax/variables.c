#include "minishell.h"

int	valid_variable_name(const char *name)
{
	if (ft_isdigit(*name))
		return (false);
	while (*name != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

int	valid_export_identifier(const char *word)
{
	if (ft_isdigit(*word))
		return (false);
	if (*word == '=')
		return (false);
	while (*word != '\0' && *word != '=')
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (false);
		word++;
	}
	return (true);
}

int	valid_parameter_assignment(const char *word)
{
	if (find_unquoted_char(word, '=') == NULL)
		return (false);
	return (valid_export_identifier(word));
}

void	split_variable(char *word, char **name, char **value)
{
	*name = word;
	while (*word != '\0')
	{
		if (*word == '=')
		{
			*name = ft_strndup(*name, word - *name);
			*value = ft_strdup(word + 1);
			if (*name == NULL || *value == NULL)
				exit(fatal_error(ENOMEM));
			return ;
		}
		word++;
	}
	*name = ft_strdup(*name);
	if (*name == NULL)
		exit(fatal_error(ENOMEM));
	*value = NULL;
}
