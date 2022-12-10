#include "minishell.h"

t_node	*subshell_extract_nodelist(t_node *nodelist)
{
	t_node	*subshell;

	subshell = nodelist->sub;
	free_nodelist(nodelist->next);
	free(nodelist);
	return (subshell);
}

int	launch_subshell(t_node *nodelist)
{
	nodelist->pid = fork();
	if (nodelist->pid < 0)
		return (-1);
	if (nodelist->pid == 0)
	{
		/* stdio_fildes_handler(RESTORE_STD_FILDES); */
		exit(executor(subshell_extract_nodelist(nodelist)));
	}
	waitpid_exit_status(nodelist->pid);
	return (EXIT_SUCCESS);
}
