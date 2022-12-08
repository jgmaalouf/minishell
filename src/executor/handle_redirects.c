#include "minishell.h"

/* multiple heredocs */
/* bash: warning: here-document at line 1 delimited by end-of-file (wanted `<delimiter>') $?=0 */
static int	handle_heredoc(t_redir *redir)
{
	if (redir != NULL)
		return (EXIT_SUCCESS);
	return (-1);
}

static	int	valid_access_rights(t_redir *redir)
{
	if (access(redir->path, F_OK) != EXIT_SUCCESS)
		return (error((char *)redir->path, "No such file or directory", 1));
	if (redir->input)
		if (access(redir->path, R_OK) != EXIT_SUCCESS)
			return (error((char *)redir->path, "Permission denied", 1));
	if (redir->output)
		if (access(redir->path, W_OK) != EXIT_SUCCESS)
			return (error((char *)redir->path, "Permission denied", 1));
	return (EXIT_SUCCESS);
}

static int	redirect(t_redir *redir)
{
	int	fd;

	if (redir->heredoc)
		return (handle_heredoc(redir));
	fd = open(redir->path, redir->oflag, redir->mode);
	if (valid_access_rights(redir) != EXIT_SUCCESS)
		return (-1);
	if (fd == -1)
		return (-1);
	if (dup2(fd, redir->fd) == -1)
		return (-1);
	return (close(fd));
}

int	handle_redirects(t_redir *redirlist)
{
	while (redirlist != NULL)
	{
		if (redirect(redirlist) != EXIT_SUCCESS)
			return (-1);
		redirlist = redirlist->next;
	}
	return (EXIT_SUCCESS);
}
