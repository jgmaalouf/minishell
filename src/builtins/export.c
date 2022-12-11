#include "minishell.h"

static int	display_environ(void)
{
	char	**environ;
	char		**env_dup;
	char		*name;
	int			i;

	environ = ft_environ(ENVIRON_GET, NULL);
	env_dup = strarr_dup(environ);
	if (env_dup == NULL)
		return (g_exit_status = 1);
	strarr_sort(env_dup);
	i = 0;
	while (env_dup[i] != NULL)
	{
		name = ft_strsep(env_dup + i, "=");
		printf("declare -x %s=\"%s\"\n", name, env_dup[i]);
		env_dup[i] = name;
		i++;
	}
	strarr_free(env_dup);
	return (g_exit_status = 0);
}

static int	export_name(char *identifer)
{
	char	*name;
	char	*value;
	char	*dup;

	if (!valid_variable_identifier(identifer))
		return (error_argv_quoted("export", identifer, "not a valid identifier"));
	if (ft_strchr(identifer, '=') == NULL)
		return (printf("unhandled\n"));
	dup = ft_strdup(identifer);
	if (dup == NULL)
		return (EXIT_FAILURE);
	name = ft_strsep(&dup, "=");
	value = dup;
	if (value[0] == '~')
		value = tilde_expansion(ft_strdup(value));
	if (ft_setenv(name, value, 1) != EXIT_SUCCESS)
		return (free(name), EXIT_FAILURE);
	free(name);
	return (EXIT_SUCCESS);
}

int	builtin_export(int argc, char *const argv[])
{
	int	status;

	status = 0;
	if (argc == 1)
		return (display_environ());
	while (*(++argv) != NULL)
		if (export_name(*argv) != EXIT_SUCCESS)
			status = 1;
	return (g_exit_status = status);
}
