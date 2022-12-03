#include "minishell.h"

void	delete_entry(int i)
{
	extern char	**environ;

	free(environ[i]);
	environ[i] = environ[i + 1];
	i++;
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
}

void	rem_from_env(char *key)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(key, environ[i], strlen(key)) == 0)
			return (delete_entry(i));
		i++;
	}
}

int	check_key_unset(char *arg)
{
	if (ft_isdigit(*arg))
		return (0);
	while (*arg != '\0')
	{
		if (!isalnum(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	rem_arg_from_env(char *arg)
{
	if (!check_key_unset(arg))
		output_error_arg("unset", arg, "not a valid identifier");
	else
		rem_from_env(strsep(&arg, "="));
}

void	builtin_unset(int argc, char *const argv[])
{
	(void)argc;
	argv++;
	while (*argv != NULL)
	{
		rem_arg_from_env(*argv);
		argv++;
	}
}
