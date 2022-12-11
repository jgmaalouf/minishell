#include "minishell.h"

static void	split_word_variable(char *word, char **name, char **value)
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

static int	export_variable(char *word)
{
	char	*name;
	char	*value;

	if (!valid_export_identifier(word))
		return (error_argv_quoted("export", word, "not a valid identifier"));
	split_word_variable(word, &name, &value);
	if (value == NULL)
	{
		if (ft_getenv(name) != NULL)
			return (free(name), EXIT_SUCCESS);
		return (add_to_lexicon(name, NULL, true), EXIT_SUCCESS);
	}
	if (value[0] == '~')
		value = tilde_expansion(value);
	if (ft_setenv(name, value, 1) != EXIT_SUCCESS)
		return (free(name), free(value), EXIT_FAILURE);
	return (free(name), free(value), EXIT_SUCCESS);
}

int	builtin_export(int argc, char *const argv[])
{
	int	status;

	status = 0;
	if (argc == 1)
		return (export_display_environ());
	while (*(++argv) != NULL)
		if (export_variable(*argv) != EXIT_SUCCESS)
			status = 1;
	return (g_exit_status = status);
}
