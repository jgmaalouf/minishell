#include "minishell.h"

static void	print_token_type(t_tk_type type)
{
	if (type == TK_WORD)
		printf("TK_WORD");
	if (type == TK_ASSIGNMENT_WORD)
		printf("TK_ASSIGNMENT_WORD");
	if (type == TK_IO_NUMBER)
		printf("TK_IO_NUMBER");
	if (type == TK_REDIRECT_INPUT)
		printf("TK_REDIRECT_INPUT");
	if (type == TK_REDIRECT_INPUT_HEREDOC)
		printf("TK_REDIRECT_INPUT_HEREDOC");
	if (type == TK_REDIRECT_INPUT_OUTPUT)
		printf("TK_REDIRECT_INPUT_OUTPUT");
	if (type == TK_REDIRECT_OUTPUT_TRUNC)
		printf("TK_REDIRECT_OUTPUT_TRUNC");
	if (type == TK_REDIRECT_OUTPUT_APPEND)
		printf("TK_REDIRECT_OUTPUT_APPEND");
	if (type == TK_REDIRECT_OUTPUT_CLOBBER)
		printf("TK_REDIRECT_OUTPUT_CLOBBER");
	if (type == TK_BACKGROUND)
		printf("TK_BACKGROUND");
	if (type == TK_PIPE)
		printf("TK_PIPE");
	if (type == TK_LOGICAL_AND)
		printf("TK_LOGICAL_AND");
	if (type == TK_LOGICAL_OR)
		printf("TK_LOGICAL_OR");
	if (type == TK_OPEN_PARENTHESIS)
		printf("TK_OPEN_PARENTHESIS");
	if (type == TK_CLOSE_PARENTHESIS)
		printf("TK_CLOSE_PARENTHESIS");
	if (type == TK_SEMICOLON)
		printf("TK_SEMICOLON");
	if (type == TK_DSEMICOLON)
		printf("TK_DSEMICOLON");
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
