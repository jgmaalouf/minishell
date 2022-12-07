#include "minishell.h"

static int	count_subpatterns(const char *pattern)
{
	int	count;

	count = 0;
	while (*pattern != '\0')
	{
		if ((*pattern != '*' && *pattern != '?') && ++count)
		{
			while (*pattern != '\0' && *pattern != '*' && *pattern != '?')
			{
				if (ft_isquote(*pattern))
					pattern = find_closing_quote(pattern) + 1;
				else if (*pattern++ == '\\')
					pattern++;
			}
		}
		else if ((*pattern == '*' || *pattern == '?') && ++count)
		{
			while (*pattern == '*' || *pattern == '?')
				pattern++;
		}
	}
	return (count);
}

static void	group_wildcards(const char **pattern, t_pat *group)
{
	group->wildcard = true;
	while (**pattern == '*' || **pattern == '?')
	{
		group->len++;
		if (**pattern == '*')
			group->asterisk++;
		else if (**pattern == '?')
			group->question_mark++;
		(*pattern)++;
	}
	group->str = strndup(group->ptr, group->len);
	if (group->str == NULL)
		exit(fatal_error(ENOMEM));
}

static void	group_string(const char **pattern, t_pat *group)
{
	while (**pattern != '\0' && **pattern != '*' && **pattern != '?')
	{
		if (ft_isquote(**pattern))
			*pattern = find_closing_quote(*pattern) + 1;
		else if (*(*pattern)++ == '\\')
			(*pattern)++;
	}
	group->str = strndup(group->ptr, *pattern - group->ptr);
	if (group->str == NULL)
		exit(fatal_error(ENOMEM));
	group->str = quote_removal(group->str);
	group->len = strlen(group->str);
}

t_pat	*group_subpatterns(const char *pattern)
{
	t_pat	*groups;
	int		count;
	int		i;

	count = count_subpatterns(pattern);
	groups = calloc(count + 1, sizeof(t_pat));
	if (groups == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (*pattern != '\0')
	{
		groups[i].ptr = pattern;
		if (*pattern == '*' || *pattern == '?')
			group_wildcards(&pattern, &groups[i]);
		else if (*pattern != '*' && *pattern != '?')
			group_string(&pattern, &groups[i]);
		i++;
	}
	return (groups);
}

void	free_pattern_groups(t_pat groups[])
{
	int	i;

	i = 0;
	while (groups[i].str != NULL)
		free(groups[i++].str);
	free(groups);
}
