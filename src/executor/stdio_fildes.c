#include "minishell.h"

static int	save_std_filedes(int std_fd[3])
{
	std_fd[0] = dup2(STDIN_FILENO, 10);
	if (std_fd[0] == -1)
		return (-1);
	std_fd[1] = dup2(STDOUT_FILENO, 11);
	if (std_fd[1] == -1)
		return (-1);
	std_fd[2] = dup2(STDERR_FILENO, 12);
	if (std_fd[2] == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

static int	restore_std_filedes(int std_fd[3])
{
	int	status;

	status = 0;
	if (dup2(std_fd[0], STDIN_FILENO) == -1)
		status = -1;
	if (dup2(std_fd[1], STDOUT_FILENO) == -1)
		status = -1;
	if (dup2(std_fd[2], STDERR_FILENO) == -1)
		status = -1;
	return (status);
}

static int	close_std_filedes_dups(int std_fd[3])
{
	int	status;

	status = 0;
	if (close(std_fd[0]) == -1)
		status = -1;
	if (close(std_fd[1]) == -1)
		status = -1;
	if (close(std_fd[2]) == -1)
		status = -1;
	return (status);
}

int	stdio_fildes_handler(int action)
{
	static int	std_fd[3];
	static int	state;

	if (action == SAVE_STD_FILDES)
		return (state = 1, save_std_filedes(std_fd));
	if (state != 1)
		return (EXIT_FAILURE);
	if (action == RESTORE_STD_FILDES)
		return (restore_std_filedes(std_fd));
	if (action == CLOSE_STD_FILDES_DUPS)
		return (state = 0, close_std_filedes_dups(std_fd));
	return (errno = EINVAL, -1);
}
