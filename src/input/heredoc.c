#include "minishell.h"

static int	open_heredoc(int heredoc_fd[2])
{
	static int	id;
	const char	file[42];

	sprintf(file, "/tmp/sh-thd-%d", id);
	heredoc_fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd[1] == -1)
		return(-1);
	heredoc_fd[0] = open(file, O_RDONLY);
	if (heredoc_fd[0] == -1)
		return(close(heredoc_fd[1]), unlink(file), -1);
	id++;
	return (EXIT_SUCCESS);
}

int	heredoc_warning(int line, const char *delimiter)
{
	printf("minishell: warning: here-document at \
		line %d delimited by end-of-file (wanted `%s')\n", 
		line, delimiter);
	return (0);
}

int	heredoc(const char *delimiter)
{
	int		heredoc_fd[2];
	int		line;
	char	*input;

	if (open_heredoc(heredoc_fd) != EXIT_SUCCESS)
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
		free(input);
	}
	free(input);
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}
