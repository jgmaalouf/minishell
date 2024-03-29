#include "minishell.h"

static int	match_string(t_pat *groups, const char **filename)
{
	if (ft_strncmp(*filename, groups->str, groups->len) != 0)
		return (false);
	*filename += groups->len;
	return (true);
}

static int	match_question_mark(int question_mark, const char **filename)
{
	while (question_mark--)
	{
		if (**filename == '\0')
			return (false);
		(*filename)++;
	}
	return (true);
}

static int	match_after_asterisk(t_pat *groups, const char **filename)
{
	char	*next_match;

	next_match = ft_strstr(*filename, groups->str);
	if (next_match == NULL)
		return (false);
	*filename = next_match + groups->len;
	return (true);
}

static int	recursive_matching(t_pat groups[], const char *filename)
{
	while (groups->str != NULL)
	{
		if (!groups->wildcard)
			if (!match_string(groups, &filename))
				return (false);
		if (groups->question_mark > 0)
			if (!match_question_mark(groups->question_mark, &filename))
				return (false);
		if (groups->asterisk > 0)
		{
			if ((groups + 1)->str == NULL)
				return (true);
			if (!match_after_asterisk(groups + 1, &filename))
				return (false);
			if (recursive_matching(groups + 2, filename))
				return (true);
		}
		else
			groups++;
	}
	if (*filename == '\0')
		return (true);
	return (false);
}

int	globbing(t_pat groups[], const char *filename)
{
	if (*filename == '.' && groups[0].ptr[0] != '.')
		return (false);
	if (ft_strcmp(groups[0].ptr, "*") == 0)
		return (true);
	if (ft_strcmp(groups[0].ptr, ".*") == 0 && *filename == '.')
		return (true);
	return (recursive_matching(groups, filename));
}
