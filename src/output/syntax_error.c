#include "minishell.h"

/* STDERR ? */

int	syntax_error_bad_substitution(char *word)
{
	printf("minishell: %s: bad substitution\n", word);
	return (g_exit_status = 258);
}

int	syntax_error_end_of_file(void)
{
	printf("minishell: syntax error: unexpected end of file\n");
	return (g_exit_status = 258);
}

int	syntax_error_matching(char c)
{
	printf("minishell: unexpected EOF while looking for matching `%c'\n", c);
	return (syntax_error_end_of_file());
}

int	syntax_error_unexpected_token(char *c)
{
	printf("minishell: syntax error near unexpected token `%s'\n", c);
	return (g_exit_status = 258);
}
