#include "minishell.h"

typedef enum e_pipe_action {
	CLOSE_PIPE_READ_END,
	CLOSE_PIPE_WRITE_END,
	CLOSE_PIPE_FILEDES,
	OPEN_PIPE_FILEDES,
	DUP_PIPE_STDIN,
	DUP_PIPE_STDOUT,
}	t_pipe_action;

static int	close_pipe_read_end(int pipe_fd[2])
{
	return (close(pipe_fd[0]));
}

static int	close_pipe_write_end(int pipe_fd[2])
{
	return (close(pipe_fd[1]));
}

static int	close_pipe_filedes(int pipe_fd[2])
{
	int	status;

	status = 0;
	if (close(pipe_fd[0]) == -1)
		status = -1;
	if (close(pipe_fd[1]) == -1)
		status = -1;
	return (status);
}

static int	open_pipe_filedes(int pipe_fd[2])
{
	return (pipe(pipe_fd));
}

static int	dup_pipe_stdin(int pipe_fd[2])
{
	return (dup2(pipe_fd[0], STDIN_FILENO));
}

static int	dup_pipe_stdout(int pipe_fd[2])
{
	return (dup2(pipe_fd[1], STDOUT_FILENO));
}

int	pipe_handler(int action)
{
	static int	pipe_fd[2];

	if (action == CLOSE_PIPE_READ_END)
		return (close_pipe_read_end(pipe_fd));
	if (action == CLOSE_PIPE_WRITE_END)
		return (close_pipe_write_end(pipe_fd));
	if (action == CLOSE_PIPE_FILEDES)
		return (close_pipe_filedes(pipe_fd));
	if (action == OPEN_PIPE_FILEDES)
		return (open_pipe_filedes(pipe_fd));
	if (action == DUP_PIPE_STDIN)
		return (dup_pipe_stdin(pipe_fd));
	if (action == DUP_PIPE_STDOUT)
		return (dup_pipe_stdout(pipe_fd));
	return (errno = EINVAL, -1);
}
