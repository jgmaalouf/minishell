#include "minishell.h"

int	env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
	return (g_exit_status = 0);
}
