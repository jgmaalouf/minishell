#include "minishell.h"

static t_redir	*new_redirection_node(void)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (new == NULL)
		exit(fatal_error(ENOMEM));
	return (new);
}

static void	redirlist_add_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	parse_redirection_flags(t_tk_type type)
{
	if (type == TK_REDIRECT_INPUT)
		return (O_RDONLY);
	if (type == TK_REDIRECT_INPUT_OUTPUT)
		return (O_RDWR);
	if (type == TK_REDIRECT_OUTPUT_TRUNC)
		return (O_WRONLY | O_CREAT | O_TRUNC | O_EXCL);
	if (type == TK_REDIRECT_OUTPUT_CLOBBER)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == TK_REDIRECT_OUTPUT_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (0);
}

static int	input_output(t_redir *redir, t_tk_type type)
{
	redir->type = type;
	if (redir->type == TK_REDIRECT_INPUT)
		return (redir->input = 1);
	if (redir->type == TK_REDIRECT_INPUT_HEREDOC)
		return (redir->input = 1);
	if (redir->type == TK_REDIRECT_INPUT_OUTPUT)
		return (redir->input = 1, redir->output = 1);
	if (redir->type == TK_REDIRECT_OUTPUT_TRUNC)
		return (redir->output = 1);
	if (redir->type == TK_REDIRECT_OUTPUT_CLOBBER)
		return (redir->output = 1);
	if (redir->type == TK_REDIRECT_OUTPUT_APPEND)
		return (redir->output = 1);
	return (0);
}

void	parse_redirection(t_token **tokenlist, t_cmd *table)
{
	t_redir	*new;

	new = new_redirection_node();
	if ((*tokenlist)->type == TK_IO_NUMBER)
	{
		new->n = (*tokenlist)->val;
		*tokenlist = (*tokenlist)->next;
	}
	input_output(new, (*tokenlist)->type);
	if (new->type == TK_REDIRECT_INPUT_HEREDOC)
	{
		new->fd = heredoc_handler(HEREDOC_RECEIVE, NULL);
		new->heredoc = true;
	}
	new->oflag = parse_redirection_flags(new->type);
	*tokenlist = (*tokenlist)->next;
	new->path = (*tokenlist)->val;
	if (new->output == true)
	{
		new->fd = 1;
		new->mode = 0644;
	}
	if (new->n != NULL)
		new->fd = ft_strtol(new->n, NULL, 10);
	return (redirlist_add_back(&table->redirlist, new));
}
