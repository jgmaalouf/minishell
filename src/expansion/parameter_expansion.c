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
		total_size += ft_strlen(lp->content);
		lp = lp->next;
	}
	result = ft_calloc(total_size + 1, sizeof(char));
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

char	*longtostr(long number)
{
	char	*str;

	asprintf(&str, "%ld", number);
	return (str);
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
/*
pid_t	find_child_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		exit(EXIT_SUCCESS);
	return (pid);
}
 */
static char	*expand_variable(char *name)
{
	char	*value;

	if (ft_strcmp(name, "$") == 0)
		return (name);
	if (ft_strcmp(name, "$$") == 0)
		return (free(name), ft_strdup("getpid()"));
	if (ft_strncmp(name, "$?", 2) == 0)
		return (free(name), last_exit_status());
	value = find_variable(name + 1);
	if (value == NULL)
		value = "";
	return (free(name), ft_strdup(value));
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
