#include "minishell.h"

static int	count_heredocs(t_token *tokenlist)
{
	int	count;

	count = 0;
	while (tokenlist != NULL)
	{
		if (tokenlist->type == TK_REDIRECT_INPUT_HEREDOC)
			count++;
		tokenlist = tokenlist->next;
	}
	return (count);
}

static int	*collect_heredocs(int count, t_token *tokenlist)
{
	int		*fd;
	char	**delim;
	int		id;

	fd = ft_calloc(count, sizeof(int *));
	delim = ft_calloc(count + 1, sizeof(char *));
	if (fd == NULL || delim == NULL)
		exit(fatal_error(ENOMEM));
	id = 0;
	while (tokenlist != NULL)
	{
		if (tokenlist->type == TK_REDIRECT_INPUT_HEREDOC)
			delim[id++] = tokenlist->next->val;
		tokenlist = tokenlist->next;
	}
	id = 0;
	while (delim[id] != NULL)
	{
		fd[id] = heredoc(delim[id], id);
		id++;
	}
	free(delim);
	return (fd);
}

static int	destroy_heredocs(int *fd[], int *count)
{
	char	file[42];

	free(*fd);
	*fd = NULL;
	while ((*count)--)
	{
		ft_snprintf(file, 42, "/tmp/sh-thd-%d", *count);
		unlink(file);
	}
	return (*count = 0, EXIT_SUCCESS);
}

int	heredoc_handler(int action, t_token *tokenlist)
{
	static int	*fd;
	static int	count;
	static int	id;

	if (action == HEREDOC_COLLECT)
	{
		count = count_heredocs(tokenlist);
		if (count != 0)
			fd = collect_heredocs(count, tokenlist);
		return (EXIT_SUCCESS);
	}
	if (action == HEREDOC_RECEIVE)
		return (fd[id++]);
	if (action == HEREDOC_DESTROY)
	{
		id = 0;
		if (count == 0)
			return (EXIT_SUCCESS);
		return (destroy_heredocs(&fd, &count));
	}
	return (errno = EINVAL, -1);
}
