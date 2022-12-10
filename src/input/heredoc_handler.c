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

static int	*collect_heredocs(t_token *tokenlist)
{
	int		*fd;
	char	**delim;
	int		count;
	int		i;

	count = count_heredocs(tokenlist);
	fd = ft_calloc(count, sizeof(int *));
	delim = ft_calloc(count + 1, sizeof(char *));
	if (fd == NULL || delim == NULL)
		exit(fatal_error(ENOMEM));
	i = 0;
	while (tokenlist != NULL)
	{
		if (tokenlist->type == TK_REDIRECT_INPUT_HEREDOC)
			delim[i++] = tokenlist->next->val;
		tokenlist = tokenlist->next;
	}
	i = 0;
	while (delim[i] != NULL)
	{
		fd[i] = heredoc(delim[i]);
		i++;
	}
	free(delim);
	return (fd);
}

int	heredoc_handler(int action, t_token *tokenlist)
{
	static int	*fd;
	static int	id;

	if (action == HEREDOC_COLLECT)
	{
		fd = collect_heredocs(tokenlist);
		return (EXIT_SUCCESS);
	}
	if (action == HEREDOC_OBTAINE)
		return (fd[id++]);
	if (action == HEREDOC_DESTROY)
	{
		/* unlink */
		free(fd);
		fd = NULL;
		id = 0;
		return (EXIT_SUCCESS);
	}
	return (errno = EINVAL, -1);
}
