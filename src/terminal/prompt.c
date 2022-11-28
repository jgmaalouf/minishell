#include "minishell.h"

#include <sys/ioctl.h>
int	terminal_dimensions(char *size)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	// printf ("columns %d\n", w.ws_col);
	// printf ("lines %d\n", w.ws_row);
	if (strcmp(size, "cols") == 0)
		return (w.ws_col);
	if (strcmp(size, "lines") == 0)
		return (w.ws_row);
	return (-1);
}

static char	*replace_home_with_tilde(char *cwd)
{
	char	*result;
	size_t	path_length;
	int		i;

	if (strncmp(cwd, "/Users/", 7) != 0)
		return (cwd);
	i = 7;
	while (cwd[i] != '\0' && cwd[i] != '/')
		i++;
	path_length = strlen(cwd + i);
	result = malloc(1 + path_length + 1);
	if (result == NULL)
		return (cwd);
	result[0] = '~';
	memcpy(result + 1, cwd + i, path_length + 1);
	return (free(cwd), result);
}

char	*generate_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*status;
	char	*c;
	int		columns;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (strdup(GRN "minishell$ " NOC));
	cwd = replace_home_with_tilde(cwd);
	c = "$";
	// c = "❯";
	if (g_exit_status != 0)
	{
		columns = terminal_dimensions("cols");
		// printf ("columns %d\n", columns);
		asprintf(&status, "✘ %d", g_exit_status);
		asprintf(&prompt, RED "%*s" BLU "\r%s\n" RED "%s " NOC, columns, status, cwd, c);
		free(status);
	}
	else
		asprintf(&prompt, BLU "%s\n" GRN "%s " NOC, cwd, c);
	free(cwd);
	return (prompt);
}
