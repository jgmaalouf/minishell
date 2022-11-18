#include "minishell.h"

void	debugging_log_env_list(t_env *env)
{
	while (env->next != NULL)
	{
		printf(BLU "key: " NOC "%s, ", env->key);
		printf(GRN "val: " NOC "%s  ", env->val);
		printf("\n");
		env = env->next;
	}
}

void	print_token_type(t_token_type type)
{
	if (type == WORD)
		printf("WORD");
	if (type == PIPE)
		printf("PIPE");
	if (type == LOGICAL_AND)
		printf("LOGICAL_AND");
	if (type == LOGICAL_OR)
		printf("LOGICAL_OR");
	if (type == REDIRECT_INPUT_FILE)
		printf("REDIRECT_INPUT_FILE");
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
