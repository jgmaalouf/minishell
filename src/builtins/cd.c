#include "minishell.h"

static int	update_pwd(const char *name)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (EXIT_FAILURE);
	ft_setenv(name, cwd, 1);
	free(cwd);
	return (EXIT_SUCCESS);
}

static int	change_directory(char *path, bool verbose)
{
	if (access(path, F_OK) != 0)
		return (output_error_arg("cd", path, "No such file or directory"));
	if (access(path, X_OK) != 0)
		return (output_error_arg("cd", path, "Permission denied"));
	update_pwd("OLDPWD");
	if (chdir(path) == -1)
		return (g_exit_status = 1);
	if (verbose == true)
		printf("%s\n", path);
	update_pwd("PWD");
	return (g_exit_status = 0);
}

static	int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	// printf("%s\n", home);
	if (home == NULL)
		return (output_error("cd", "HOME not set"));
	return (change_directory(home, 0));
}

static	int	cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd == NULL)
		return (output_error("cd", "OLDPWD not set"));
	return (change_directory(oldpwd, 1));
}

int	cd(int argc, char *const argv[])
{
	if (argc == 1)
		return (cd_home());
	if (strcmp(argv[1], "-") == 0)
		return (cd_oldpwd());
	return (change_directory(argv[1], 0));
}
