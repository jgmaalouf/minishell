#include "minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (g_exit_status = 1);
	printf("%s\n", cwd);
	free(cwd);
	return (g_exit_status = 0);
}
