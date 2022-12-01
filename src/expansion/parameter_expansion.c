#include "minishell.h"

// char	*join_subwords(t_list *subwords)
// char	*merge_subwords(t_list *subwords)
char	*concatenate_subwords(t_list *subwords)
{
	char	*result;
	int		total_size;
	t_list	*lptr;

	total_size = 0;
	lptr = subwords;
	while (lptr != NULL)
	{
		total_size += strlen(lptr->content);
		lptr = lptr->next;
	}
	result = calloc(total_size + 1, sizeof(char));
	if (result == NULL)
		exit(fatal_error());
	lptr = subwords;
	while (lptr != NULL)
	{
		strlcat(result, lptr->content, total_size + 1);
		lptr = lptr->next;
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

static char	*find_env_variable(char *key)
{
	char	*value;

	value = getenv(key);
	if (value == NULL)
		return (strdup(""));
	return (strdup(value));
}

static char	*expand_env_variable(char *key)
{
	char	*value;

	if (strcmp(key, "$") == 0)
		return (key);
	if (strncmp(key, "$?", 2) == 0)
		value = last_exit_status();
	else
		value = find_env_variable(key + 1);
	if (value == NULL)
		exit(fatal_error());
	return (free(key), value);
}

char	*parameter_expansion(char *word)
{
	char	*result;
	t_list	*subwords;
	t_list	*lptr;

	subwords = subdivide_dollar_word(word);
	free(word);
	lptr = subwords;
	while (lptr)
	{
		if (((char *)lptr->content)[0] == '$')
			lptr->content = expand_env_variable(lptr->content);
		lptr = lptr->next;
	}
	result = concatenate_subwords(subwords);
	ft_lstclear(&subwords, &free);
	return (result);
}
