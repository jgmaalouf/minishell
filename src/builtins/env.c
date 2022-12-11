#include "minishell.h"

int	builtin_env(void)
{
	char	**environ;
	int		i;

	environ = ft_environ(ENVIRON_GET, NULL);
	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
	return (g_exit_status = 0);
}
