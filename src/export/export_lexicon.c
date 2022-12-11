#include "minishell.h"

t_local	*create_new_lexicon(size_t size)
{
	t_local	*new;

	new = ft_calloc(size, sizeof(t_local));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	return (new);
}

static void	*free_lexicon(t_local *lexicon)
{
	int	i;

	i = 0;
	while (lexicon[i].name != NULL)
	{
		free(lexicon[i].entry);
		free(lexicon[i].name);
		free(lexicon[i].value);
		i++;
	}
	free(lexicon);
	return (NULL);
}

t_local	*export_lexicon(int action, t_local *new_lexicon)
{
	static t_local	*last_lexicon;

	if (action == EXPORT_SAVE_LEXICON)
	{
		if (last_lexicon == new_lexicon)
			return (new_lexicon);
		last_lexicon = new_lexicon;
		return (new_lexicon);
	}
	if (action == EXPORT_GET_LEXICON)
	{
		if (last_lexicon == NULL)
			last_lexicon = create_new_lexicon(2);
		return (last_lexicon);
	}
	if (action == EXPORT_DESTROY_LEXICON)
		return (last_lexicon = free_lexicon(last_lexicon));
	return (errno = EINVAL, NULL);
}
