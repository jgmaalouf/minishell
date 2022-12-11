#include "minishell.h"

static int	count_lexicon_export_entries(t_local *lexicon)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (lexicon[i].name != NULL)
	{
		if (lexicon[i].export == true)
			count++;
		i++;
	}
	return (count);
}

static char	**sort_all_exported_variables(void)
{
	char	**environ;
	char	**array;
	t_local	*lexicon;
	size_t	size[2];
	int		i;

	environ = ft_environ(ENVIRON_GET, NULL);
	lexicon = export_lexicon(EXPORT_GET_LEXICON, NULL);
	size[0] = strarr_len(environ);
	size[1] = count_lexicon_export_entries(lexicon);
	array = ft_calloc(size[0] + size[1] + 1, sizeof(char *));
	if (array == NULL)
		exit(fatal_error(ENOMEM));
	ft_memcpy((char *)array, (char *)environ, size[0] * sizeof(char *));
	i = size[0];
	while (lexicon->name != NULL)
	{
		if (lexicon->export == true)
			array[i++] = lexicon->entry;
		lexicon++;
	}
	strarr_sort(array);
	return (array);
}

static void	output_export_value(char *value)
{
	write(STDOUT_FILENO, "\"", 1);
	while (*value != '\0')
	{
		if (*value == '\"' || *value == '\\')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, value++, 1);
	}
	write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

int	export_display_environ(void)
{
	char	**array;
	char	*equal_sign;
	size_t	len;
	int		i;

	array = sort_all_exported_variables();
	i = 0;
	while (array[i] != NULL)
	{
		equal_sign = ft_strchr(array[i], '=');
		if (equal_sign != NULL)
		{
			len = equal_sign - array[i] + 1;
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, array[i], len);
			output_export_value(array[i] + len);
		}
		else
			printf("declare -x %s\n", array[i]);
		i++;
	}
	free(array);
	return (g_exit_status = 0);
}
