#include "minishell.h"

void	print_key_value_export(char *key, char *val)
{
	if (strncmp(key, "_", strlen(key)) == 0)
		return ;
	if (val == NULL)
		printf("declare -x %s\n", key);
	else
		printf("declare -x %s=\"%s\"\n", key, val);
}

void	display_all_env_vars(void)
{
	extern char	**environ;
	char		**env_cpy;
	char		*tmp;
	int			i;

	env_cpy = strarr_dup(environ);
	strarr_sort(env_cpy);
	i = 0;
	while (env_cpy[i] != NULL)
	{
		tmp = strsep(&(env_cpy[i]), "=");
		print_key_value_export(tmp, env_cpy[i]);
		env_cpy[i] = tmp;
		i++;
	}
	strarr_free(env_cpy);
}

int	check_key_export(char *arg)
{
	if (ft_isdigit(*arg))
		return (0);
	while (*arg != '\0' && *arg != '=')
	{
		if (!isalnum(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	add_to_env(char *arg)
{
	char	*arg_cpy;
	char	*key;
	char	*val;

	arg_cpy = strdup(arg);
	if (arg_cpy == NULL)
		exit(EXIT_FAILURE);
	key = strsep(&arg_cpy, "=");
	val = arg_cpy;
	ft_setenv(key, val, 1);
	free(key);
}

void	add_arg_to_env(char *arg)
{
	if (!check_key_export(arg))
		output_error_quoted_arg("export", arg, "not a valid identifier");
	else
		add_to_env(arg);
}

/* export desktop=~/Desktop/ */
void	export(int argc, char *const argv[])
{
	extern char	**environ;

	if (argc == 1)
		display_all_env_vars();
	else
	{
		argv++;
		while (*argv != NULL)
		{
			add_arg_to_env(*argv);
			argv++;
		}
	}
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	extern char	**environ;
	char		*list[] = {"PROGRAM_NAME", "\"\"\"zzz\"\"\"", NULL};
	char		*list2[] = {"PROGRAM_NAME", "zzz=SHMANDAR", NULL};

	environ = strarr_dup(environ);

	// export(2, list);
	export(2, list2);
	export(1, NULL);
	unset(list);
	export(1, NULL);
}
 */
