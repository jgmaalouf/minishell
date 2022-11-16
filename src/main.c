#include "minishell.h"

static int	usage(void)
{
	printf(RED "Usage: ./minishell\n" NOC);
	return (EXIT_FAILURE);
}

/*
static int	command_history(char *command_line)
{
	int	i;

	i = 0;
	if (command_line == NULL)
		return (EXIT_FAILURE);
	while (isspace(command_line[i]))
		i++;
	if (command_line[i] == '\0')
		return (EXIT_FAILURE);
	// if (strcmp(command_line, previous_line))
	//	return (EXIT_FAILURE);
	add_history(command_line);
	return (EXIT_SUCCESS);
}
 */

void	free_env(t_env *env)
{
	t_env	*next;

	while (env != NULL)
	{
		next = env->next;
		free(env);
		env = next;
	}
}

int	exit_routine(t_env *env)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	free_env(env);
	return (EXIT_SUCCESS);
}

static void	minishell(t_env *env)
{
	char	*cmdline;
	t_cmd	*table;
	// t_token	*tokens;

	while (42)
	{
		/* cmdline = readline(get_prompt(env)); */
		// cmdline = readline(GRN "minishell$ " NOC);
		// cmdline = strdup("echo hello world");
		cmdline = strdup("echo ${SHELL}");
		// debugging_log_print_env(env);
		// printf("%s\n", getenv("PATH"));
		if (cmdline == NULL)
		{
			printf(BLU "\tC-d" NOC "\n");
			exit_routine(env);
			// exit(EXIT_SUCCESS);
			return;
		}
		if (*cmdline != '\0')
			add_history(cmdline);
		// tokens = lexer(cmdline);
		// if (tokens == NULL)
		// 	printf(BLU "Failure or empty line\n" NOC);
		// log_print_tokens(tokens);
		// tokens = free_tokens(tokens);

		table = parser(cmdline, env);
		if (table != NULL)
			executor(table);

		free(cmdline);
		// exit_routine(env); return;
		/* printf(RED "cmdline: '%s'\n" NOC, cmdline); */
	}
}

/* int	main(void) */
int	main(int argc, char const *argv[], char const **envp)
{
	if (argc != 1 && argv != NULL)
		return (usage());
	// signal(SIGINT, ctrl_c);
	// signal(SIGQUIT, SIG_IGN);
	t_env *env = preprocess_environment((char **)envp);
	minishell(env);
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
