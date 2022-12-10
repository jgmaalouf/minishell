#include "minishell.h"

static int	open_heredoc(int heredoc_fd[2], int id)
{
	char	file[42];

	ft_snprintf(file, 42, "/tmp/sh-thd-%d", id);
	heredoc_fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd[1] == -1)
		return(-1);
	heredoc_fd[0] = open(file, O_RDONLY);
	if (heredoc_fd[0] == -1)
		return(close(heredoc_fd[1]), unlink(file), -1);
	return (EXIT_SUCCESS);
}

static int	heredoc_warning(int line, const char *delimiter)
{
	printf("minishell: warning: here-document at "
		"line %d delimited by end-of-file (wanted `%s')\n",
		line, delimiter);
	return (EXIT_SUCCESS);
}

int	heredoc(const char *delimiter, int id)
{
	int		heredoc_fd[2];
	int		line;
	char	*input;

	if (open_heredoc(heredoc_fd, id) != EXIT_SUCCESS)
		return (-1);
	line = 0;
	while (1)
	{
		line++;
		input = readline(BOLD YELLOW "> " RESET);
		if (input == NULL)
		{
			heredoc_warning(line, delimiter);
			break ;
		}
		if (ft_strcmp(input, delimiter) == 0)
			break ;
		write(heredoc_fd[1], input, ft_strlen(input));
		write(heredoc_fd[1], "\n", 1);
		free(input);
	}
	free(input);
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}
