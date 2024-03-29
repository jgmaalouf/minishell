#include "minishell.h"

int	identify_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (BUILTIN_EXIT);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (BUILTIN_UNSET);
	return (NOT_BUILTIN);
}

int	execute_builtin(t_node *nodelist)
{
	int			argc;
	char *const	*argv;
	int			id;

	argc = nodelist->table->cmd_argc;
	argv = nodelist->table->cmd_argv;
	if (handle_redirects(nodelist->table->redirlist) != EXIT_SUCCESS)
		return (stdio_fildes_handler(RESTORE_STD_FILDES), EXIT_FAILURE);
	id = nodelist->table->builtin_id;
	if (id == BUILTIN_CD)
		return (builtin_cd(argc, argv));
	if (id == BUILTIN_ECHO)
		return (builtin_echo(argc, argv));
	if (id == BUILTIN_ENV)
		return (builtin_env());
	if (id == BUILTIN_EXIT)
		return (builtin_exit(argc, argv, nodelist));
	if (id == BUILTIN_EXPORT)
		return (builtin_export(argc, argv));
	if (id == BUILTIN_PWD)
		return (builtin_pwd());
	if (id == BUILTIN_UNSET)
		return (builtin_unset(argc, argv));
	return (errno = EINVAL, -1);
}
