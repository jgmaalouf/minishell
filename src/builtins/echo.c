#include "minishell.h"

static bool	test_single_flag(char flag, char *s)
{
	if (*s++ != '-')
		return (false);
	// if (*s++ != flag)
	// 	return (false);
	// while (*s != '\0')
	// 	if (*s++ != flag)
	// 		return (false);
	// return (true);
	while (*s++ == flag)
		if (*s == '\0')
			return (true);
	return (false);
}

int	echo(int argc, char *const argv[])
{
	bool	n_flag;

	(void)argc;
	n_flag = false;
	while (*(++argv) != NULL && test_single_flag('n', *argv))
		n_flag = true;
	if (*argv != NULL)
	{
		while (*(argv + 1) != NULL)
			printf("%s ", *argv++);
		printf("%s", *argv);
	}
	if (n_flag == false)
		printf("\n");
	return (g_exit_status = 0);
}
