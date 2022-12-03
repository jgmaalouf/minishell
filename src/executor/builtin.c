#include "minishell.h"

int	builtin_command(char *cmd_name)
{
	if (strcmp(cmd_name, "cd") == 0)
		return (BUILTIN_CD);
	if (strcmp(cmd_name, "echo") == 0)
		return (BUILTIN_ECHO);
	if (strcmp(cmd_name, "env") == 0)
		return (BUILTIN_ENV);
	if (strcmp(cmd_name, "exit") == 0)
		return (BUILTIN_EXIT);
	if (strcmp(cmd_name, "export") == 0)
		return (BUILTIN_EXPORT);
	if (strcmp(cmd_name, "pwd") == 0)
		return (BUILTIN_PWD);
	if (strcmp(cmd_name, "unset") == 0)
		return (BUILTIN_UNSET);
	return (NO_BUILTIN);
}

int	execute_builtin(t_cmd *table)
{
	int	id;

	id = table->builtin_id;
	if (id == NO_BUILTIN)
		return (EXIT_FAILURE);
	else if (id == BUILTIN_CD)
		builtin_cd(table->cmd_argc, table->cmd_argv);
	else if (id == BUILTIN_ECHO)
		builtin_echo(table->cmd_argc, table->cmd_argv);
	else if (id == BUILTIN_ENV)
		builtin_env();
	else if (id == BUILTIN_EXIT)
		builtin_exit(table->cmd_argc, table->cmd_argv, table);
	else if (id == BUILTIN_EXPORT)
		builtin_export(table->cmd_argc, table->cmd_argv);
	else if (id == BUILTIN_PWD)
		builtin_pwd();
	else if (id == BUILTIN_UNSET)
		builtin_unset(table->cmd_argc, table->cmd_argv);
	return (EXIT_SUCCESS);
}
