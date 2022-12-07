#include "minishell.h"

// char	*join_subwords(t_list *subwords)
// char	*merge_subwords(t_list *subwords)
char	*concatenate_subwords(t_list *subwords)
{
	char	*result;
	int		total_size;
	t_list	*lp;

	total_size = 0;
	lp = subwords;
	while (lp != NULL)
	{
		total_size += strlen(lp->content);
		lp = lp->next;
	}
	result = calloc(total_size + 1, sizeof(char));
	if (result == NULL)
		exit(fatal_error(ENOMEM));
	lp = subwords;
	while (lp != NULL)
	{
		strlcat(result, lp->content, total_size + 1);
		lp = lp->next;
	}
	return (result);
}

/* itoa() */
static char	*last_exit_status(void)
{
	char	*exit_status;

	asprintf(&exit_status, "%d", g_exit_status);
	return (exit_status);
}

static char	*find_variable(char *name)
{
	char	*value;
	char	**dict;

	value = getenv(name);
	if (value != NULL)
		return (value);
	dict = dict_open();
	value = dict_get_val(dict, name);
	if (value != NULL)
		return (value);
	return (NULL);
}

static char	*expand_variable(char *name)
{
	char	*value;

	if (strcmp(name, "$") == 0)
		return (name);
	if (strncmp(name, "$?", 2) == 0)
		return (free(name), last_exit_status());
	value = find_variable(name + 1);
	if (value == NULL)
		value = "";
	return (free(name), strdup(value));
}

char	*parameter_expansion(char *word)
{
	char	*result;
	t_list	*subwords;
	t_list	*lp;

	subwords = subdivide_dollar_word(word);
	free(word);
	lp = subwords;
	while (lp)
	{
		if (((char *)lp->content)[0] == '$')
		{
			lp->content = expand_variable(lp->content);
			if (lp->content == NULL)
				exit(fatal_error(ENOMEM));
		}
		lp = lp->next;
	}
	result = concatenate_subwords(subwords);
	ft_lstclear(&subwords, &free);
	return (result);
}
