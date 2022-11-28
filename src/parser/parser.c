#include "minishell.h"

t_cmd	*parser(char *line)
{
	t_token	*tokens;
	t_cmd	*table;

	if (find_bad_substitution(line))
		return (NULL);
	tokens = lexer(line);
	if (tokens == NULL)
		return (NULL);
	// printf("TOKENIZED:\n");
	// debugging_log_token_list(tokens);
	if (!validate_syntax(tokens))
		return (free_tokens(tokens));
	shell_expansion(tokens);
	// printf("EXPANDED:\n");
	// debugging_log_token_list(tokens);
	table = create_cmd_table(tokens);
	free_tokens(tokens);
	return (table);
}
