#include "minishell.h"

static int	handle_heredoc(t_redir *redir)
{
	if (redir != NULL)
		return (EXIT_SUCCESS);
	return (-1);
}

static int	redirect_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->path, redir->oflag);
	if (access(redir->path, R_OK) != EXIT_SUCCESS)
		return (-1);
	if (fd == -1)
		return (-1);
	if (dup2(fd, redir->fd) == -1)
		return (-1);
	return (close(fd));
}

static int	redirect_output(t_redir *redir)
{
	int	fd;

	fd = open(redir->path, redir->oflag, 0644);
	if (access(redir->path, W_OK) != EXIT_SUCCESS)
		return (-1);
	if (fd == -1)
		return (-1);
	if (dup2(fd, redir->fd) == -1)
		return (-1);
	return (close(fd));
}

static int	handle_redirection(t_redir *redirlist)
{
	if (redirlist->heredoc)
		return (handle_heredoc(redirlist));
	if (redirlist->input)
		return (redirect_input(redirlist));
	if (redirlist->output)
		return (redirect_output(redirlist));
	return (errno = EINVAL, -1);
}

int	redirect(t_redir *redirlist)
{
	while (redirlist != NULL)
	{
		if (handle_redirection(redirlist) != EXIT_SUCCESS)
			return (-1);
		redirlist = redirlist->next;
	}
	return (EXIT_SUCCESS);
}
