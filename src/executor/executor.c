#include "minishell.h"



char	**extract_env_path(void)
{
	char	**path;
	char	*env_path;
	int		count;
	int		i;

	env_path = strdup(getenv("PATH"));
	count = 0;
	i = 0;
	while (env_path[i] != '\0')
		if (env_path[i++] == ':')
			count++;
	path = calloc(count + 1, sizeof(char *));
	i = 0;
	path[i] = strsep(&env_path, ":");
	while (path[i++] != NULL)
		path[i] = strsep(&env_path, ":");
	return (path);
}

char	*full_cmd_path(char *path, char *cmd_name)
{
	char *join_wslash;
	char *full_path;

	join_wslash = ft_concat(path, "/");
	full_path = ft_concat(join_wslash, cmd_name);
	free(join_wslash);
	return(full_path);
}

int	cmd_not_found(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	return (0);
}

char const	*find_cmd_path(char *cmd_name)
{
	char	*cmd_path;
	char	**path;
	int		i;

	if (access(cmd_name, F_OK) == 0)
		return (strdup(cmd_name));
	if (cmd_name[0] == '/')
		return (NULL);
	path = extract_env_path();
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = full_cmd_path(path[i++], cmd_name);
		if (access(cmd_path, F_OK) == 0)
			break;
		free(cmd_path);
		cmd_path = NULL;
	}
	free(*path);
	free(path);
	if (cmd_path == NULL)
		cmd_not_found(cmd_name);
	return (cmd_path);
}

int cmd_argc(t_token *tokens)
{
	t_token	*tptr;
	int		count;

	tptr = tokens;
	count = 0;
	while (tptr != NULL && token_is_word(tptr->type))
	{
		count++;
		tptr = tptr->next;
	}
	return (count);
}

void	add_cmd(t_token **tokens, t_cmd *table)
{
	int		count;
	int		i;

	table->cmd_name = strdup((*tokens)->val);
	table->cmd_path = find_cmd_path(table->cmd_name);
	count = cmd_argc(*tokens);
	table->cmd_argv = calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		((char **)(table->cmd_argv))[i++] = strdup((*tokens)->val);
		*tokens = (*tokens)->next;
	}
}

void	redirect_cmd_input_file(t_token **tokens, t_cmd *table)
{
	
}

void	redirect_cmd(t_token **tokens, t_cmd *table)
{
	if ((*tokens)->type == REDIRECT_INPUT_FILE)
		redirect_cmd_input_file(tokens, table);
	// if ((*tokens)->type == REDIRECT_INPUT_HEREDOC)
	// 	redirect_cmd_input_heredoc();
	// if ((*tokens)->type == REDIRECT_OUTPUT_APPEND)
	// 	redirect_cmd_output_append();
	// if ((*tokens)->type == REDIRECT_OUTPUT_TRUNC)
	// 	redirect_cmd_output_trunc();
}

t_cmd	*create_cmd_table(t_token *tokens)
{
	t_cmd	*table;

	while (tokens != NULL)
	{
		if (token_is_word(tokens->type))
			add_cmd(&tokens, table);
		if (token_is_redirection(tokens->type))
			redirect_cmd(&tokens, table);
		// if (token_is_logical_operand())
		// if (token_is_parenthesis())
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (table);
}

void	executor(t_cmd *table)
{
	pid_t	pid;
	// extern char	**environ;

	pid = fork();
	if (pid == 0)
		if (execve(table->cmd_path, table->cmd_argv, NULL) == -1)
			exit(EXIT_FAILURE);
	waitpid(pid, NULL, 0);
}
