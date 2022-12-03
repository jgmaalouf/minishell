#include "minishell.h"

int	cmd_not_found(char *cmd)
{
	output_error(cmd, "command not found");
	return (g_exit_status = 127);
}

int	cmd_argc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && token_is_basic_word(tokens->type))
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

void	add_cmd(t_token **tokens, t_cmd *table)
{
	int	i;

	table->cmd_name = strdup((*tokens)->val);
	table->cmd_path = find_cmd_path(table->cmd_name);
	table->cmd_argc = cmd_argc(*tokens);
	table->cmd_argv = calloc(table->cmd_argc + 1, sizeof(char *));
	if (table->cmd_argv == NULL)
		exit(fatal_error());
	i = 0;
	while (i < table->cmd_argc)
	{
		((char **)(table->cmd_argv))[i++] = strdup((*tokens)->val);
		*tokens = (*tokens)->next;
	}
}

t_cmd	*create_cmd_table(t_token *tokens)
{
	t_cmd	*table;
	t_cmd	*head;

	table = calloc(1, sizeof(t_cmd));
	head = table;
	while (tokens != NULL)
	{
		if (token_is_basic_word(tokens->type))
			add_cmd(&tokens, table);
		// if (token_is_redirection())
		// if (token_is_logical_operand())
		// if (token_is_parenthesis())
		if (tokens != NULL)
			tokens = tokens->next;
		table = table->next;
		table = calloc(1, sizeof(t_cmd));
	}
	return (head);
}

int	update_exit_status(int status)
{
	/* man waitpid */
	// printf("%d\n", status);

	// printf("%d\n", WIFEXITED(status));
	// printf("%d\n", WIFSIGNALED(status));
	// printf("%d\n", WIFSTOPPED(status));
	// printf("%d\n", WEXITSTATUS(status));
	// printf("%d\n", WTERMSIG(status));
	// printf("%d\n", WSTOPSIG(status));
	return (g_exit_status = WEXITSTATUS(status));
}

void	executor(t_cmd *table)
{
	extern char	**environ;
	pid_t		pid;
	int			stat_loc;

	table->builtin_id = builtin_command(table->cmd_name);
	if (table->builtin_id > 0)
	{
		execute_builtin(table);
		return ;
	}

	if (table->cmd_path == NULL)
	{
		cmd_not_found(table->cmd_name);
		/* free_cmd_table(table); */
		return ;
	}

	pid = fork();
	if (pid == 0)
		if (execve(table->cmd_path, table->cmd_argv, environ) == -1)
			exit(EXIT_FAILURE);

	signal(SIGINT, &signal_ctrl_c_runtime);
	signal(SIGQUIT, &signal_ctrl_backslash); /* fix */

	waitpid(pid, &stat_loc, 0);

	signal(SIGINT, &signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	update_exit_status(stat_loc);
}
