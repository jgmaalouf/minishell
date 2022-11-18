#include "../minishell.h"

typedef struct s_pattern
{
	char		*string;
	char const	*ptr;
	int			len;
	int			asterisk;
	int			question_mark;
	bool		wildcard;
}	t_pattern;

int	count_subpatterns(char const *pattern)
{
	int	count;

	count = 0;
	while (*pattern != '\0')
	{
		if (*pattern == '*' || *pattern == '?')
		{
			count++;
			while (*pattern == '*' || *pattern == '?')
				pattern++;
		}
		if (*pattern != '\0' && *pattern != '*' && *pattern != '?')
		{
			count++;
			while (*pattern != '\0' && *pattern != '*' && *pattern != '?')
				pattern++;
		}
	}
	return (count);
}

void	group_wildcard(char const **pattern, t_pattern *group)
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
}

void	group_string(char const **pattern, t_pattern *group)
{
	while (**pattern != '\0' && **pattern != '*' && **pattern != '?')
	{
		group->len++;
		(*pattern)++;
	}
}

t_pattern	*group_subpatterns(char const *pattern)
{
	t_pattern	*groups;
	int			count;
	int			i;

	count = count_subpatterns(pattern);
	// groups = malloc(sizeof(t_pattern) * (count + 1));
	groups = calloc(count + 1, sizeof(t_pattern));
	i = 0;
	while (*pattern != '\0')
	{
		groups[i].ptr = pattern;
		groups[i].len = 0;
		groups[i].asterisk = 0;
		groups[i].question_mark = 0;
		groups[i].wildcard = false;
		if (*pattern == '*' || *pattern == '?')
			group_wildcard(&pattern, &groups[i]);
		else if (*pattern != '*' && *pattern != '?')
			group_string(&pattern, &groups[i]);
		groups[i].string = strndup(groups[i].ptr, groups[i].len);
		i++;
	}
	groups[i].ptr = NULL;
	groups[i].string = NULL;
	return (groups);
}

int	match_string(t_pattern *groups, char const **filename)
{
	if (strncmp(*filename, groups->ptr, groups->len) != 0)
		return (false);
	*filename += groups->len;
	return (true);
}

int	match_question_mark(int question_mark, char const **filename)
{
	while (question_mark--)
	{
		if (**filename == '\0')
			return (false);
		(*filename)++;
	}
	return (true);
}

int	match_after_asterisk(t_pattern *groups, char const **filename)
{
	char *next_match;

	next_match = strstr(*filename, groups->string);
	if (next_match == NULL)
		return (false);
	*filename = next_match + groups->len;
	return (true);
}

int	recursive_matching(t_pattern *groups, char const *filename)
{
	while (groups->ptr != NULL)
	{
		if (!groups->wildcard)
			if (!match_string(groups, &filename))
				return (false);
		if (groups->question_mark > 0)
			if (!match_question_mark(groups->question_mark, &filename))
				return (false);
		if (groups->asterisk > 0)
		{
			if ((groups + 1)->ptr == NULL)
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

void	free_pattern_groups(t_pattern *groups)
{
	int	i;

	i = 0;
	while (groups[i].ptr != NULL)
		free(groups[i++].string);
	free(groups);
}

int	globbing(char const *pattern, char const *filename)
{
	t_pattern	*groups;
	int			result;

	if (*filename == '.' && *pattern != '.')
		return (false);
	if (strcmp(pattern, "*") == 0)
		return (true);
	if (strcmp(pattern, ".*") == 0 && *filename == '.')
		return (true);
	groups = group_subpatterns(pattern);
	result = recursive_matching(groups, filename);
	free_pattern_groups(groups);
	return (result);
}


void	debugging_log_pattern_groups(t_pattern *groups, char const *filename)
{
	printf("pattern: '%s'\n\n", groups->ptr);
	while (groups->ptr != NULL)
	{
		printf("---\n");
		printf("%.*s, ", groups->len, groups->ptr);
		printf("%d, ", groups->len);
		printf("%d\n", groups->question_mark);
		if (groups->wildcard == false)
		{
			printf("...\n");
			char *needle = groups->string;
			printf("haystack: %s\n", filename);
			printf("needle:   %s\n", needle);
			printf("%s\n", strstr(filename, needle));
		}
		groups++;
	}
	printf("---\n\n");
}

/*
int	main(int argc, char *argv[])
{
	char *pattern  = "test*?";
	char *filename = "test";
	// char *pattern  = "test*a*b";
	// char *filename = "testabbab";

	// char *pattern  = "TEST_*a???_b_c";
	// char *filename = "TEST_a12_b_ca321_b_c";

	// char *pattern  = ".*";
	// char *filename = ".";

	// char *pattern  = "*aaa*zz*cc";
	// char *filename = "qq_aaatabzzbccqcc";

	int match = globbing(pattern, filename);
	if (match)
		printf("MATCH:   \n pattern  <%s> \n filename <%s>\n", pattern, filename);
	else
		printf("CONFLICT:\n pattern  <%s> \n filename <%s>\n", pattern, filename);
	return (0);
}
 */
