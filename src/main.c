#include "minishell.h"

static int	usage(void)
{
	printf(BOLD RED "Usage: ./minishell\n" RESET);
	return (EXIT_FAILURE);
}

int	exit_ctrl_d(void)
{
	extern char	**environ;

	// rl_replace_line("", 0);
	printf("\e[1A");
	rl_on_new_line();
	rl_redisplay();
	ft_dwrite(2, "exit\n");
	rl_clear_history();
	strarr_free(environ);
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

char	*command_line_input(void)
{
	char	*command_line;
	char	*next_line;
	char	*concat;
	char	*prompt;

	prompt = generate_prompt();
	command_line = readline(prompt);
	free(prompt);
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

static int	minishell(void)
{
	char	*cmdline;
	t_node	*nodelist;

	while (42)
	{
		/* cmdline = readline(GREEN "minishell$ " RESET); */
		cmdline = command_line_input();
		if (cmdline == NULL)
			return (exit_ctrl_d());
		command_history(cmdline);
		nodelist = parser(cmdline);
		if (nodelist != NULL)
			executor(nodelist);
		free(cmdline);
	}
}

/* int	main(void) */
int	main(int argc, char *const argv[])
{
	extern char	**environ;

	g_exit_status = 0;
	if (argc != 1 && argv != NULL)
		return (usage());
	environ = strarr_dup(environ);
	if (environ == NULL)
		exit(EXIT_FAILURE);
	/* ft_setenv("SHELL", argv[0], 1); */
	/* ft_setenv("COLUMNS", "", 1); */
	/* ft_setenv("LINES", "", 1); */
	set_history_file_path(HISTFILE_WRONLY);
	read_history_file(HISTFILE_RDONLY);
	signal(SIGINT, &signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	minishell();
	// system("leaks minishell");
	// exit(EXIT_SUCCESS);
	return (g_exit_status);
}
