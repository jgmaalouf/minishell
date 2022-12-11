#include "minishell.h"

static char	**extract_env_path(void)
{
	char	**env_path;
	char	*var_path;
	int		count;
	int		i;

	var_path = ft_getenv("PATH");
	if (var_path == NULL)
		return (NULL);
	var_path = ft_strdup(var_path);
	if (var_path == NULL)
		exit(fatal_error(ENOMEM));
	count = 1;
	i = 0;
	while (var_path[i] != '\0')
		if (var_path[i++] == ':')
			count++;
	env_path = ft_calloc(count + 1, sizeof(char *));
	if (env_path == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	env_path[i] = ft_strsep(&var_path, ":");
	while (env_path[i++] != NULL)
		env_path[i] = ft_strsep(&var_path, ":");
	return (env_path);
}

char	*find_cmd_path(char *cmd_name)
{
	char	*cmd_path;
	char	**env_path;
	int		i;

	if (access(cmd_name, F_OK) == EXIT_SUCCESS)
		return (ft_strdup(cmd_name));
	if (cmd_name[0] == '/')
		return (NULL);
	env_path = extract_env_path();
	if (env_path == NULL)
		return (NULL);
	i = 0;
	while (env_path[i] != NULL)
	{
		cmd_path = ft_concat3(env_path[i++], "/", cmd_name);
		if (cmd_path == NULL)
			exit(fatal_error(ENOMEM));
		if (access(cmd_path, F_OK) == EXIT_SUCCESS)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free(*env_path);
	free(env_path);
	return (cmd_path);
}
