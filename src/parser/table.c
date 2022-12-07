#include "minishell.h"

bool	token_is_command_separator(t_tk_type type)
{
	return (!token_is_word(type) && !token_is_redirection(type));
}

static t_cmd	*new_cmd_table(void)
{
	t_cmd	*new;

	new = calloc(1, sizeof(t_cmd));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	return (new);
}

static int	cmd_argc(t_token *tokenlist)
{
	int	count;

	count = 0;
	while (tokenlist != NULL && token_is_simple_word(tokenlist->type))
	{
		count++;
		tokenlist = tokenlist->next;
	}
	return (count);
}

t_cmd	*parse_assignments(t_token **tokenlist)
{
	t_cmd	*assignments;
	t_token	*tlp;
	int		i;

	assignments = new_cmd_table();
	assignments->redirlist = parse_redirections(*tokenlist);
	tlp = *tokenlist;
	while (tlp != NULL && tlp->type == TK_ASSIGNMENT_WORD)
	{
		assignments->cmd_argc++;
		tlp = tlp->next;
	}
	assignments->cmd_argv = calloc(assignments->cmd_argc + 1, sizeof(char *));
	if (assignments->cmd_argv == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (*tokenlist != NULL)
	{
		if ((*tokenlist)->type != TK_ASSIGNMENT_WORD)
			return (assignments);
		((char **)assignments->cmd_argv)[i++] = (*tokenlist)->val;
		*tokenlist = (*tokenlist)->next;
	}
	return (assignments);
}

t_cmd	*create_command_table(t_token **tokenlist)
{
	t_cmd	*table;
	int		i;

	if ((*tokenlist)->type == TK_ASSIGNMENT_WORD)
		return (parse_assignments(tokenlist));
	table = new_cmd_table();
	table->redirlist = parse_redirections(*tokenlist);
	table->cmd_argc = cmd_argc(*tokenlist);
	table->cmd_argv = calloc(table->cmd_argc + 1, sizeof(char *));
	if (table->cmd_argv == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (*tokenlist != NULL)
	{
		if (token_is_command_separator((*tokenlist)->type))
			break ;
		if (token_is_simple_word((*tokenlist)->type))
			((char **)table->cmd_argv)[i++] = (*tokenlist)->val;
		*tokenlist = (*tokenlist)->next;
	}
	table->builtin_id = identify_builtin(table->cmd_argv[0]);
	return (table);
}