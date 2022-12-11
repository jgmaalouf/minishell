#include "minishell.h"

char	*get_lexicon_entry(const char *name)
{
	t_local	*lexicon;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (errno = EINVAL, NULL);
	lexicon = export_lexicon(EXPORT_GET_LEXICON, NULL);
	while (lexicon->name != NULL)
	{
		if (ft_strcmp(lexicon->name, name) == 0)
			return (lexicon->value);
		lexicon++;
	}
	return (NULL);
}
