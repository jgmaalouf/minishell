#include "minishell.h"

static int	match_string(t_pat *groups, const char **filename)
{
	if (strncmp(*filename, groups->str, groups->len) != 0)
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

	next_match = strstr(*filename, groups->str);
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
	if (strcmp(groups[0].ptr, "*") == 0)
		return (true);
	if (strcmp(groups[0].ptr, ".*") == 0 && *filename == '.')
		return (true);
	return (recursive_matching(groups, filename));
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
