#include "minishell.h"

t_node	*parser(char *cmdline)
{
	t_node	*nodelist;
	t_token	*tokenlist;

	if (find_bad_substitution(cmdline))
		return (NULL);
	tokenlist = lexer(cmdline);
	if (tokenlist == NULL)
		return (NULL);
	if (syntax_validator(tokenlist) != EXIT_SUCCESS)
		return (free_tokenlist(tokenlist, 1));
	heredoc_handler(HEREDOC_COLLECT, tokenlist);
	nodelist = create_nodelist(tokenlist);
	return (nodelist);
}
