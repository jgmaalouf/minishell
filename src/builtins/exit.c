#include "minishell.h"

static int	builtin_exit_routine(t_node *nodelist)
{
	rl_clear_history();
	free_nodelist(nodelist);
	heredoc_handler(HEREDOC_DESTROY, NULL);
	export_lexicon(EXPORT_DESTROY_LEXICON, NULL);
	ft_environ(ENVIRON_DESTROY, NULL);
	exit(g_exit_status);
}

int	builtin_exit(int argc, char *const argv[], t_node *nodelist)
{
	ft_dwrite(2, "exit\n");
	if (argc == 1)
		return (builtin_exit_routine(nodelist));
	errno = 0;
	g_exit_status = ft_strtol(argv[1], NULL, 10);
	if (!ft_isnumber(argv[1]) || errno == ERANGE)
	{
		error_argv("exit", argv[1], "numeric argument required");
		return (g_exit_status = -1, builtin_exit_routine(nodelist));
	}
	if (argc == 2)
		return (builtin_exit_routine(nodelist));
	return (error_output("exit", "too many arguments"));
}
