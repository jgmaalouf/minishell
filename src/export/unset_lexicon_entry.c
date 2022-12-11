#include "minishell.h"

void	remove_entry(t_local *lexicon)
{
	int	i;

	i = 0;
	free(lexicon[i].entry);
	free(lexicon[i].name);
	free(lexicon[i].value);
	lexicon[i] = lexicon[i + 1];
	while (lexicon[i].name != NULL)
	{
		lexicon[i] = lexicon[i + 1];
		i++;
	}
}

int	unset_lexicon_entry(const char *name)
{
	t_local	*lexicon;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (errno = EINVAL, -1);
	lexicon = export_lexicon(EXPORT_GET_LEXICON, NULL);
	while (lexicon->name != NULL)
	{
		if (ft_strcmp(lexicon->name, name) == 0)
			remove_entry(lexicon);
		else
			lexicon++;
	}
	return (EXIT_SUCCESS);
}
