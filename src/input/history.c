#include "minishell.h"

int	read_history_file(char const *filename)
{
	char	buffer[1024];
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	i = 0;
	while (read(fd, &buffer[i], 1) > 0)
	{
		if (buffer[i++] != '\n')
			continue ;
		buffer[i - 1] = '\0';
		// printf("%s\n", buffer);
		add_history(buffer);
		i = 0;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	command_history(char const *line)
{
	int	fd;

	if (line == NULL)
		return (EXIT_FAILURE);
	while (isspace(*line))
		line++;
	if (*line == '\0')
		return (EXIT_FAILURE);
	// if (strcmp(line, previous_line))
	//	return (EXIT_FAILURE);
	add_history(line);
	fd = open(HISTFILE_WRONLY, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd == -1)
		return (EXIT_FAILURE);
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);
}
