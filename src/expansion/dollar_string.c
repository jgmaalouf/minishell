#include "minishell.h"

static t_list	*group_quoted_strings(char *word)
{
	t_list	*grouplist;
	char	*group;
	char	*quote;
	size_t	len;

	grouplist = NULL;
	while (*word != '\0')
	{
		if (ft_isquote(*word))
			len = find_closing_quote(word) - word + 1;
		else
		{
			quote = find_next_quote(word);
			if (quote == NULL)
				len = ft_strlen(word);
			else
				len = quote - word;
		}
		group = ft_strndup(word, len);
		if (group == NULL)
			exit(fatal_error(ENOMEM));
		ft_lstadd_back(&grouplist, ft_lstnew(group));
		word += len;
	}
	return (grouplist);
}

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

char	*parameter_expansion(char *word)
{
	char	*result;
	t_list	*grouplist;
	t_list	*lp;

	grouplist = group_quoted_strings(word);
	free(word);
	lp = grouplist;
	while (lp != NULL)
	{
		lp->content = process_dollar_string_group(lp->content);
		lp = lp->next;
	}
	result = concatenate_subwords(grouplist);
	ft_lstclear(&grouplist, &free);
	return (result);
}
