#include "minishell.h"

char	*process_brace_substitution(char **word)
{
	char	*variable;

	variable = *word;
	*word = strchr(*word, '}');
	variable = strndup(variable, *word - variable);
	// printf("%s\n", variable);
	variable[0] = '$';
	(*word)++;
	return (variable);
}

/* echo $'single_quote' $"double_quote" [>> single_quote double_quote] */
char	*process_dollar_sign(char **word)
{
	char	*variable;

	variable = (*word)++;
	if (**word == '{')
		return (process_brace_substitution(word));
	if (**word == '\'' || **word == '\"')
		return (strdup(""));
	if (isdigit(**word) || **word == '?')
		(*word)++;
	else
		while (isalnum(**word) || **word == '_')
			(*word)++;
	return (strndup(variable, *word - variable));
}

char	*process_next_dollar_subword(char **word)
{
	char	*subword;
	char	*dollar;
	char	*single;

	if (**word == '$')
		return (process_dollar_sign(word));
	subword = *word;
	dollar = strchr(*word, '$');
	single = strchr(*word, '\'');
	if (dollar == NULL)
		*word = strchr(*word, '\0');
	else if (single != NULL && single < dollar)
		*word = strchr(single + 1, '\'') + 1;
	else
		*word = dollar + (dollar[-1] == '\\');
	return (strndup(subword, *word - subword));
}

// void	partition_subwords(char *word)
t_list	*subdivide_dollar_word(char *word)
{
	t_list	*list;
	char	*subword;

	list = NULL;
	while (*word)
	{
		subword = process_next_dollar_subword(&word);
		ft_lstadd_back(&list, ft_lstnew(subword));
	}
	return (list);
}

// char	*join_subwords(t_list *subwords)
// char	*merge_subwords(t_list *subwords)
char	*concatenate_subwords(t_list *subwords)
{
	char	*result;
	int		total_size;
	t_list	*lptr;

	lptr = subwords;
	total_size = 0;
	while (lptr)
	{
		total_size += strlen(lptr->content);
		lptr = lptr->next;
	}
	result = calloc(total_size + 1, sizeof(char));
	lptr = subwords;
	while (lptr)
	{
		strlcat(result, lptr->content, total_size + 1);
		lptr = lptr->next;
	}
	return (result);
}

char	*last_exit_status(void)
{
	char	*exit_status;

	asprintf(&exit_status, "%d", g_exit_status); //itoa()
	return (exit_status);
}

/*
// char	*look_up_env_variable(char *key, t_env *env)
char	*find_env_variable(char *key, t_env *env)
{
	while (env)
	{
		if (strcmp(key, env->key) == 0)
			return (strdup(env->val));
		env = env->next;
	}
	return (strdup(""));
}
 */

char	*find_env_variable(char *key)
{
	char	*value;

	value = getenv(key);
	if (value == NULL)
		return (strdup(""));
	return (strdup(value));
}

char	*expand_env_variable(char *key, t_env *env)
{
	char	*value;

	if (strcmp(key, "$") == 0)
		return (key);
	if (strncmp(key, "$?", 2) == 0)
		value = last_exit_status();
	else
		value = find_env_variable(key + 1);
		// value = find_env_variable(key + 1, env);
	if (env)
		env = NULL;
	free(key);
	return (value);
}

char	*parameter_expansion(char *word, t_env *env)
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
			lptr->content = expand_env_variable(lptr->content, env);
		lptr = lptr->next;
	}
	result = concatenate_subwords(subwords);
	ft_lstclear(&subwords, &free);
	return (result);
}
