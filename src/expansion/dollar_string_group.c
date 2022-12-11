#include "minishell.h"

static void	process_brace_substitution(char **substr, t_list **sublist)
{
	char	*variable;
	char	*expanded;

	variable = *substr;
	*substr = ft_strchr(*substr, '}');
	variable = ft_strndup(variable, *substr - variable);
	(*substr)++;
	variable[0] = '$';
	expanded = expand_dollar_variable(variable);
	return (ft_lstadd_back(sublist, ft_lstnew(expanded)));
}

static void	process_dollar_variable(char **substr, t_list **sublist)
{
	char	*variable;
	char	*expanded;

	variable = (*substr)++;
	if (**substr == '{')
		return (process_brace_substitution(substr, sublist));
	if (ft_isdigit(**substr) || **substr == '$' || **substr == '?')
		(*substr)++;
	else
		while (ft_isalnum(**substr) || **substr == '_')
			(*substr)++;
	variable = ft_strndup(variable, *substr - variable);
	expanded = expand_dollar_variable(variable);
	return (ft_lstadd_back(sublist, ft_lstnew(expanded)));
}

static t_list	*process_double_quoted_string(char *string)
{
	t_list	*sublist;
	char	*substr;
	int		i;

	sublist = NULL;
	while (*string != '"')
	{
		if (*string == '$')
		{
			process_dollar_variable(&string, &sublist);
			continue ;
		}
		substr = ft_calloc(ft_strlen(string) + 1, sizeof(char));
		if (substr == NULL)
			exit(fatal_error(ENOMEM));
		i = 0;
		while (*string != '\0' && *string != '$' && *string != '"')
		{
			if (*string == '\\')
				string++;
			substr[i++] = *string++;
		}
		ft_lstadd_back(&sublist, ft_lstnew(substr));
	}
	return (sublist);
}

static t_list	*process_raw_string(char *string)
{
	t_list	*sublist;
	char	*substr;
	int		i;

	sublist = NULL;
	while (*string != '\0')
	{
		if (*string == '$')
		{
			process_dollar_variable(&string, &sublist);
			continue ;
		}
		substr = ft_calloc(ft_strlen(string) + 1, sizeof(char));
		if (substr == NULL)
			exit(fatal_error(ENOMEM));
		i = 0;
		while (*string != '\0' && *string != '$')
		{
			if (*string == '\\')
				string++;
			substr[i++] = *string++;
		}
		ft_lstadd_back(&sublist, ft_lstnew(substr));
	}
	return (sublist);
}

char	*process_dollar_string_group(char *group)
{
	char	*result;
	t_list	*sublist;

	if (*group == '\'')
		return (quote_removal(group));
	if (ft_strchr(group, '$') == NULL)
		return (quote_removal(group));
	if (*group == '\"')
		sublist = process_double_quoted_string(group + 1);
	else
		sublist = process_raw_string(group);
	result = concatenate_subwords(sublist);
	ft_lstclear(&sublist, &free);
	return (free(group), result);
}
