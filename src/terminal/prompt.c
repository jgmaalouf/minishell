#include "minishell.h"

int	terminal_dimensions(char *size)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (ft_strcmp(size, "cols") == 0)
		return (w.ws_col);
	if (ft_strcmp(size, "lines") == 0)
		return (w.ws_row);
	return (-1);
}

static char	*replace_home_with_tilde(char *path)
{
	char	*result;
	size_t	path_length;
	int		i;

	if (ft_strncmp(path, "/Users/", 7) != 0)
		return (path);
	i = 7;
	while (path[i] != '\0' && path[i] != '/')
		i++;
	path_length = ft_strlen(path + i);
	result = malloc(1 + path_length + 1);
	if (result == NULL)
		return (path);
	result[0] = '~';
	ft_memcpy(result + 1, path + i, path_length + 1);
	return (free(path), result);
}

static char	*bold_cwd(char *path)
{
	char	*result;
	char	*cwd;

	cwd = ft_strrchr(path, '/');
	if (cwd == NULL || *(cwd + 1) == '\0')
		return (path);
	// result = malloc(cwd - path + ft_strlen(BLD) + ft_strlen(cwd) + ft_strlen(RESET) + 1);
	path[cwd - path] = '\0';
	asprintf(&result, "%s/" BOLD "%s" RESET, path, ++cwd);
	if (result == NULL)
		return (path);
	return (free(path), result);
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
		return (ft_strdup(GREEN "minishell$ " RESET));
	cwd = replace_home_with_tilde(cwd);
	cwd = bold_cwd(cwd);
	c = "$";
	// c = "❯";
	if (g_exit_status != 0)
	{
		columns = terminal_dimensions("cols");
		// printf ("columns %d\n", columns);
		asprintf(&status, "✘ %d", g_exit_status);
		asprintf(&prompt, BOLD RED "%*s" RESET
			BLUE "\r%s\n" RED "%s " RESET, columns, status, cwd, c);
		free(status);
	}
	else
		asprintf(&prompt, BLUE "%s\n" GREEN "%s " RESET, cwd, c);
	free(cwd);
	return (prompt);
}
