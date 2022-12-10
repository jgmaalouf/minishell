#include "minishell.h"

int	set_history_file_path(const char *filename)
{
	char	*cwd;
	char	*full_path;

	if (*filename == '/' || *filename == '~')
		return (ft_setenv("HISTFILE", filename, 1));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (EXIT_FAILURE);
	full_path = ft_concat3(cwd, "/", filename);
	free(cwd);
	if (full_path == NULL)
		return (EXIT_FAILURE);
	ft_setenv("HISTFILE", full_path, 1);
	free(full_path);
	return (EXIT_SUCCESS);
}

int	read_history_file(const char *filename)
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
		if (buffer[i] != '\n')
			if (++i + 1 < 1024)
				continue ;
		buffer[i] = '\0';
		add_history(buffer);
		i = 0;
	}
	if (i > 0)
	{
		buffer[i] = '\0';
		add_history(buffer);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	command_history(const char *line)
{
	static char	prev_line[1024];
	size_t		line_length;
	const char	*histfile;
	int			fd;

	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (EXIT_SUCCESS);
	if (ft_strcmp(line, prev_line) == 0)
		return (EXIT_SUCCESS);
	add_history(line);
	line_length = ft_strlen(line);
	if (line_length < 1024)
		ft_memcpy(prev_line, line, line_length + 1);
	histfile = getenv("HISTFILE");
	if (histfile == NULL)
		return (EXIT_FAILURE);
	fd = open(histfile, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd == -1)
		return (EXIT_FAILURE);
	write(fd, line, line_length);
	write(fd, "\n", 1);
	return (close(fd), EXIT_SUCCESS);
}
