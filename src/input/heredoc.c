#include "minishell.h"

static int	close_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	return (-1);
}

int	heredoc(const char *delimiter)
{
	int		heredoc_wfd;
	int		heredoc_rfd;
	char	*input;

	heredoc_wfd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	heredoc_rfd = open(".heredoc_tmp", O_RDONLY);
	if (heredoc_wfd == -1 || heredoc_rfd == -1)
		return (close_fds(heredoc_wfd, heredoc_rfd));
	while (1)
	{
		input = readline(BOLD YELLOW "> " RESET);
		if (strlen(input) == strlen(delimiter)
			&& strncmp(input, delimiter, strlen(delimiter)) == 0)
			break ;
		write(heredoc_wfd, input, strlen(input));
		free(input);
	}
	free(input);
	close(heredoc_wfd);
	return (heredoc_rfd);
}
