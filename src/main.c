#include "minishell.h"

static int	usage(void)
{
	printf(RED "Usage: ./minishell\n" NOC);
	return (EXIT_FAILURE);
}

int	exit_ctrl_d(t_env *env)
{
	// rl_replace_line("", 0);
	printf("\e[1A");
	rl_on_new_line();
	rl_redisplay();
	write(2, "exit\n", 5);
	rl_clear_history();
	free_env(env);
	return (g_exit_status);
}

// int	escaped_newline(char *line)
int	trailing_backslash(char *line)
{
	int	count;
	int	len;
	int	i;

	len = strlen(line);
	if (len == 0)
		return (false);
	i = len - 1;
	if (line[i] != '\\')
		return (false);
	count = 1;
	while (--i > 0 && line[i] == '\\')
		count++;
	if (count % 2 == 0)
		return (false);
	line[len - 1] = '\0';
	return (true);
}

char *command_line_input(void)
{
	char	*command_line;
	char	*next_line;
	char	*concat;

	command_line = readline(GRN "minishell$ " NOC);
	if (command_line == NULL)
		return (NULL);
	while (trailing_backslash(command_line))
	{
		next_line = readline("> ");
		if (next_line == NULL)
			return (free(command_line), NULL);
		concat = ft_concat(command_line, next_line);
		free(command_line);
		free(next_line);
		command_line = concat;
	}
	return (command_line);
}

static int	minishell(t_env *env)
{
	char	*cmdline;
	t_cmd	*table;

	while (42)
	{
		/* cmdline = readline(get_prompt(env)); */
		/* cmdline = readline(GRN "minishell$ " NOC); */
		cmdline = command_line_input();
		// cmdline = strdup("echo ${SHELL}");
		// cmdline = strdup("ls \"test\\*\\*\'*'\"");
		// cmdline = strdup("\"this\\\" this\"");
		// cmdline = strdup("'this\\'\\\\\\\\\\\\\\\\\"\\\"\\\"''");
		// printf("%s\n", cmdline);

		if (cmdline == NULL)
			return (exit_ctrl_d(env));
		command_history(cmdline);
		table = parser(cmdline, env);
		if (table != NULL)
			executor(table);
		free(cmdline);

		// exit_ctrl_d(env); return (0);
	}
}

/* int	main(void) */
int	main(int argc, char const *argv[], char const **envp)
{
	g_exit_status = 0;
	if (argc != 1 && argv != NULL)
		return (usage());
	read_history_file(HISTFILE_RDONLY);
	signal(SIGINT, &signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	t_env *env = preprocess_environment((char **)envp);
	minishell(env);
	// system("leaks minishell");
	// exit(EXIT_SUCCESS);
	return (g_exit_status);
}
