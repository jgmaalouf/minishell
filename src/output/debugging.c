#include "minishell.h"

static void	print_token_type(t_tk_type type)
{
	if (type == WORD)
		printf("WORD");
	if (type == PIPE)
		printf("PIPE");
	if (type == LOGICAL_AND)
		printf("LOGICAL_AND");
	if (type == LOGICAL_OR)
		printf("LOGICAL_OR");
	if (type == REDIRECT_INPUT)
		printf("REDIRECT_INPUT");
	if (type == REDIRECT_INPUT_HEREDOC)
		printf("REDIRECT_INPUT_HEREDOC");
	if (type == REDIRECT_OUTPUT_TRUNC)
		printf("REDIRECT_OUTPUT_TRUNC");
	if (type == REDIRECT_OUTPUT_APPEND)
		printf("REDIRECT_OUTPUT_APPEND");
	if (type == OPEN_PARENTHESIS)
		printf("OPEN_PARENTHESIS");
	if (type == CLOSE_PARENTHESIS)
		printf("CLOSE_PARENTHESIS");
	printf(": ");
}

void	debugging_log_token_list(t_token *tokens)
{
	while (tokens != NULL)
	{
		print_token_type(tokens->type);
		printf("[[    %s    ]]\n", tokens->val);
		tokens = tokens->next;
	}
	printf("\n");
}

void	debugging_log_pattern_groups(t_pat groups[])
{
	int	bytes;

	printf("valid glob pattern: %s\n", groups->ptr);
	while (groups->ptr != NULL)
	{
		printf("------------------------\n");
		if (groups->wildcard == true)
		{
			printf("(wildcard)\n");
			printf("group: %s\n", groups->str);
			printf("len:   %d\n", groups->question_mark);
			groups++;
			continue ;
		}
		printf("(string)\n");
		if ((groups + 1)->ptr == NULL)
			bytes = ft_strlen(groups->ptr);
		else
			bytes = (groups + 1)->ptr - groups->ptr;
		printf("group: %.*s\n", bytes, groups->ptr);
		printf("match: %s\n", groups->str);
		printf("len:   %d\n", groups->len);
		groups++;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
