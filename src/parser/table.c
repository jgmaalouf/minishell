#include "minishell.h"

static t_cmd	*new_cmd_table(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	return (new);
}

static t_cmd	*parse_assignments(t_token *tokenlist)
{
	t_cmd	*table;
	int		i;

	table = new_cmd_table();
	table->cmd_argc = count_assignment_argc(tokenlist);
	table->cmd_argv = ft_calloc(table->cmd_argc + 1, sizeof(char *));
	if (table->cmd_argv == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (tokenlist != NULL)
	{
		if (token_is_redirection(tokenlist->type))
			parse_redirection(&tokenlist, table);
		if (tokenlist->type != TK_ASSIGNMENT_WORD)
			return (table);
		((char **)table->cmd_argv)[i++] = tokenlist->val;
		tokenlist = tokenlist->next;
	}
	return (table);
}

static t_cmd	*redirection_without_command(t_token *tokenlist, t_cmd *table)
{
	while (tokenlist != NULL)
	{
		if (token_is_command_separator(tokenlist->type))
			return (table);
		else if (token_is_redirection(tokenlist->type))
			parse_redirection(&tokenlist, table);
		tokenlist = tokenlist->next;
	}
	return (table);
}

t_cmd	*create_command_table(t_token *tokenlist)
{
	t_cmd	*table;
	int		i;

	if (tokenlist->type == TK_ASSIGNMENT_WORD)
		return (parse_assignments(tokenlist));
	table = new_cmd_table();
	table->cmd_argc = count_command_argc(tokenlist);
	if (table->cmd_argc == 0)
		return (redirection_without_command(tokenlist, table));
	table->cmd_argv = ft_calloc(table->cmd_argc + 1, sizeof(char *));
	if (table->cmd_argv == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (tokenlist != NULL)
	{
		if (token_is_command_separator(tokenlist->type))
			break ;
		else if (token_is_redirection(tokenlist->type))
			parse_redirection(&tokenlist, table);
		else if (token_is_simple_word(tokenlist->type))
			((char **)table->cmd_argv)[i++] = tokenlist->val;
		tokenlist = tokenlist->next;
	}
	table->builtin_id = identify_builtin(table->cmd_argv[0]);
	return (table);
}
