#include "minishell.h"

static void	change_entry(t_local *lexicon, char *name, char *value, bool export)
{
	free(lexicon->entry);
	free(lexicon->name);
	free(lexicon->value);
	lexicon->name = name;
	lexicon->value = value;
	lexicon->export = export;
}

static t_local	create_entry(char *name, char *value, bool export)
{
	t_local	lexicon;
	char	*entry;

	if (value != NULL)
		entry = ft_concat3(name, "=", value);
	else
		entry = ft_strdup(name);
	if (entry == NULL)
		exit(fatal_error(ENOMEM));
	lexicon.entry = entry;
	lexicon.name = name;
	lexicon.value = value;
	lexicon.export = export;
	return (lexicon);
}

static void	add_new_entry(char *name, char *value, bool export)
{
	t_local	*old_lexicon;
	t_local	*new_lexicon;
	size_t	i;

	old_lexicon = export_lexicon(EXPORT_GET_LEXICON, NULL);
	i = 0;
	while (old_lexicon[i].name != NULL)
		i++;
	new_lexicon = create_new_lexicon(i + 2);
	i = 0;
	while (old_lexicon[i].name != NULL)
	{
		new_lexicon[i].entry = old_lexicon[i].entry;
		new_lexicon[i].name = old_lexicon[i].name;
		new_lexicon[i].value = old_lexicon[i].value;
		new_lexicon[i].export = old_lexicon[i].export;
		i++;
	}
	new_lexicon[i] = create_entry(name, value, export);
	free(old_lexicon);
	export_lexicon(EXPORT_SAVE_LEXICON, new_lexicon);
}

int	set_lexicon_entry(char *name, char *value, bool export)
{
	t_local	*lexicon;
	int		i;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (errno = EINVAL, -1);
	lexicon = export_lexicon(EXPORT_GET_LEXICON, NULL);
	i = 0;
	while (lexicon[i].name != NULL)
	{
		if (ft_strcmp(lexicon[i].name, name) == 0)
		{
			if (value == NULL)
				return (free(name), EXIT_SUCCESS);
			if (export == true)
			{
				ft_setenv(lexicon[i].name, lexicon[i].value, 1);
				remove_entry(&lexicon[i]);
			}
			change_entry(&lexicon[i], name, value, export);
		}
		i++;
	}
	add_new_entry(name, value, export);
	return (EXIT_SUCCESS);
}
