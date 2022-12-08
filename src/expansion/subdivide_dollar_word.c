#include "minishell.h"

static char	*process_brace_substitution(char **word)
{
	char	*variable;

	variable = *word;
	*word = strchr(*word, '}');
	variable = strndup(variable, *word - variable);
	variable[0] = '$';
	(*word)++;
	return (variable);
}

static char	*process_dollar_sign(char **word)
{
	char	*variable;

	variable = (*word)++;
	if (**word == '{')
		return (process_brace_substitution(word));
	if (**word == '\'' || **word == '\"')
		return (strdup(""));
	if (isdigit(**word) || **word == '$' || **word == '?')
		(*word)++;
	else
		while (isalnum(**word) || **word == '_')
			(*word)++;
	return (strndup(variable, *word - variable));
}

static char	*process_next_dollar_subword(char **word)
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
	while (*word != '\0')
	{
		subword = process_next_dollar_subword(&word);
		if (subword == NULL)
			exit(fatal_error(ENOMEM));
		ft_lstadd_back(&list, ft_lstnew(subword));
	}
	return (list);
}
