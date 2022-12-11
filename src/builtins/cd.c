#include "minishell.h"

static int	check_access(char *path)
{
	if (access(path, F_OK) != EXIT_SUCCESS)
		return (error_argv("cd", path, "No such file or directory"));
	if (access(path, X_OK) != EXIT_SUCCESS)
		return (error_argv("cd", path, "Permission denied"));
	return (EXIT_SUCCESS);
}

static int	change_directory(char *path, bool verbose)
{
	char	*oldpwd;
	char	*pwd;

	if (check_access(path) != EXIT_SUCCESS)
		return (g_exit_status = 1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (free(oldpwd), g_exit_status = 1);
	if (oldpwd != NULL)
		ft_setenv("OLDPWD", oldpwd, 1);
	free(oldpwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (g_exit_status = 1);
	ft_setenv("PWD", pwd, 1);
	if (verbose == true)
		printf("%s\n", pwd);
	free(pwd);
	return (g_exit_status = 0);
}

static	int	cd_home(void)
{
	char	*home;

	home = ft_getenv("HOME");
	if (home == NULL)
		return (error_output("cd", "HOME not set"));
	return (change_directory(home, 0));
}

static	int	cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (oldpwd == NULL)
		return (error_output("cd", "OLDPWD not set"));
	return (change_directory(oldpwd, 1));
}

int	builtin_cd(int argc, char *const argv[])
{
	if (argc == 1)
		return (cd_home());
	if (argc > 2)
		return (error_output("cd", "too many arguments"));
	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_oldpwd());
	if (*argv[1] == '\0')
		return (g_exit_status = 0);
	return (change_directory(argv[1], 0));
}
