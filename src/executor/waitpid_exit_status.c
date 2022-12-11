#include "minishell.h"

int	waitpid_exit_status(pid_t pid)
{
	int	stat_loc;

	waitpid(pid, &stat_loc, 0);
	if (WIFSIGNALED(stat_loc))
	{
		if (WTERMSIG(stat_loc) == 2)
			return (g_exit_status = 130);
		if (WTERMSIG(stat_loc) == 3)
			return (g_exit_status = 131);
		if (WTERMSIG(stat_loc) == 9)
			return (g_exit_status = 1);
		if (WTERMSIG(stat_loc) == 13)
			return (g_exit_status = 1);
		return (g_exit_status = WTERMSIG(stat_loc));
	}
	return (g_exit_status = WEXITSTATUS(stat_loc));
}
