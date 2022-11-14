#include "minishell.h"

t_token	*new_token_node(int type, char *val)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = type;
	new->val = val;
	new->next = NULL;
	return (new);
}

void	*free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (tokens->type == WORD)
			free(tokens->val);
		free(tokens);
		tokens = next;
	}
	return (NULL);
}

t_token	*tokenize_redirection(char **line)
{
	if (**line == '<' && (*line)++)
	{
		if (**line == '<' && (*line)++)
			return (new_token_node(REDIRECT_INPUT_HEREDOC, "<<"));
		else
			return (new_token_node(REDIRECT_INPUT_FILE, "<"));
	}
	if (**line == '>' && (*line)++)
	{
		if (**line == '>' && (*line)++)
			return (new_token_node(REDIRECT_OUTPUT_APPEND, ">>"));
		else
			return (new_token_node(REDIRECT_OUTPUT_TRUNC, ">"));
	}
	return (NULL);
}

t_token	*tokenize_logical_operand(char **line)
{
	if (**line == '|' && (*line)++)
	{
		if (**line == '|' && (*line)++)
			return (new_token_node(LOGICAL_OR, "||"));
		else
			return (new_token_node(PIPE, "|"));
	}
	if (**line == '&' && (*line)++)
	{
		if (**line == '&' && (*line)++)
			return (new_token_node(LOGICAL_AND, "&&"));
	}
	syntax_error_unexpected_token(*line);
	return (NULL);
}

t_token	*tokenize_parenthesis(char **line)
{
	if (**line == '(' && (*line)++)
		return (new_token_node(OPEN_PARENTHESIS, "("));
	if (**line == ')' && (*line)++)
		return (new_token_node(CLOSE_PARENTHESIS, ")"));
	return (NULL);
}

int reserved_shell_char(int c)
{
	if (c == '<' || c == '>')
		return (c);
	if (c == '|' || c == '&')
		return (c);
	if (c == '(' || c == ')')
		return (c);
	return (0);
}

int	ft_isquote(char c)
{
	return (c == '\'' || c == '\"');
}

char *find_next_match(char *input)
{
	return (strchr(input + 1, *input));
}

t_token	*tokenize_word(char **line)
{
	char	*closing_quote;
	char	*word;

	word = *line;
	while (**line != '\0' && !isspace(**line) && !reserved_shell_char(**line))
	{
		if (ft_isquote(**line))
		{
			closing_quote = find_next_match(*line);
			if (closing_quote == NULL)
			{
				syntax_error_matching(**line);
				return (NULL);
			}
			*line = closing_quote;
		}
		(*line)++;
	}
	return (new_token_node(WORD, strndup(word, *line - word)));
}

t_token	*get_next_token(char **line)
{
	char	c;

	c = **line;
	if (c == '<' || c == '>')
		return (tokenize_redirection(line));
	if (c == '|' || c == '&')
		return (tokenize_logical_operand(line));
	if (c == '(' || c == ')')
		return (tokenize_parenthesis(line));
	if (isascii(c))
		return (tokenize_word(line));
	return (NULL);
}

void	token_list_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (list == NULL)
		return ;
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

void	log_print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("type:%d,\t", tokens->type);
		printf("val: '%s'\n", tokens->val);
		printf("\n");
		tokens = tokens->next;
	}
}

/* char *line = command_line_input */
t_token	*lexer(char *line)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	while (*line != '\0')
	{
		while (isspace(*line))
			line++;
		if (*line == '\0')
			return (tokens);
		new = get_next_token(&line);
		if (new == NULL)
			return (free_tokens(tokens));
		token_list_add_back(&tokens, new);
	}
	return (tokens);
}
