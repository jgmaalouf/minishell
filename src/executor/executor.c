#include "minishell.h"

char	**extract_env_path(void)
{
	char	**env_path;
	char	*var_path;
	int		count;
	int		i;

	var_path = getenv("PATH");
	if (var_path == NULL)
		return (NULL);
	var_path = strdup(var_path);
	count = 1;
	i = 0;
	while (var_path[i] != '\0')
		if (var_path[i++] == ':')
			count++;
	env_path = calloc(count + 1, sizeof(char *));
	i = 0;
	env_path[i] = strsep(&var_path, ":");
	while (env_path[i++] != NULL)
		env_path[i] = strsep(&var_path, ":");
	return (env_path);
}

char	*full_cmd_path(char *env_path, char *cmd_name)
{
	char *full_path;
	char *path_slash;

	path_slash = ft_concat(env_path, "/");
	full_path = ft_concat(path_slash, cmd_name);
	free(path_slash);
	return(full_path);
}

int	cmd_not_found(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	return (g_exit_status = 1);
}

char const	*find_cmd_path(char *cmd_name)
{
	char	*cmd_path;
	char	**env_path;
	int		i;

	if (access(cmd_name, F_OK) == 0)
		return (strdup(cmd_name));
	if (cmd_name[0] == '/')
		return (NULL);
	env_path = extract_env_path();
	if (env_path == NULL)
		return (NULL);
	i = 0;
	while (env_path[i] != NULL)
	{
		cmd_path = full_cmd_path(env_path[i++], cmd_name);
		if (access(cmd_path, F_OK) == 0)
			break;
		free(cmd_path);
		cmd_path = NULL;
	}
	free(*env_path);
	free(env_path);
	return (cmd_path);
}

int cmd_argc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && token_is_word(tokens->type))
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
		if (token_is_word(tokens->type))
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

int	execute_builtin(t_cmd *table)
{
	int	id;

	id = table->builtin_id;
	if (id == NO_BUILTIN)
		return (EXIT_FAILURE);
	// else if (id == BUILTIN_CD)
	// 	builtin_cd();
	else if (id == BUILTIN_EXIT)
		builtin_exit(table);
	return (EXIT_SUCCESS);
}

int	builtin_command(char *cmd_name)
{
	if (strcmp(cmd_name, "cd") == 0)
		return (BUILTIN_CD);
	// if (strcmp(cmd_name, "echo") == 0)
	// 	return (BUILTIN_ECHO);
	if (strcmp(cmd_name, "env") == 0)
		return (BUILTIN_ENV);
	if (strcmp(cmd_name, "exit") == 0)
		return (BUILTIN_EXIT);
	if (strcmp(cmd_name, "export") == 0)
		return (BUILTIN_EXPORT);
	if (strcmp(cmd_name, "pwd") == 0)
		return (BUILTIN_PWD);
	if (strcmp(cmd_name, "unset") == 0)
		return (BUILTIN_UNSET);
	return (NO_BUILTIN);
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
		return;
	}

	if (table->cmd_path == NULL)
	{
		cmd_not_found(table->cmd_name);
		/* free_cmd_table(table); */
		return;
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
