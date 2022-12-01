#include "minishell.h"

static t_token	*tokenize_redirection(char **line)
{
	if (**line == '<' && (*line)++)
	{
		if (**line == '<' && (*line)++)
			return (new_token_node(REDIRECT_INPUT_HEREDOC, "<<"));
		if (**line == '>' && (*line)++)
			return (new_token_node(REDIRECT_INPUT_OUTPUT, "<>"));
		return (new_token_node(REDIRECT_INPUT, "<"));
	}
	if (**line == '>' && (*line)++)
	{
		if (**line == '>' && (*line)++)
			return (new_token_node(REDIRECT_OUTPUT_APPEND, ">>"));
		if (**line == '|' && (*line)++)
			return (new_token_node(REDIRECT_OUTPUT_CLOBBER, ">|"));
		return (new_token_node(REDIRECT_OUTPUT_TRUNC, ">"));
	}
	return (NULL);
}

static t_token	*tokenize_logical_operand(char **line)
{
	if (**line == '|' && (*line)++)
	{
		if (**line == '|' && (*line)++)
			return (new_token_node(LOGICAL_OR, "||"));
		return (new_token_node(PIPE, "|"));
	}
	if (**line == '&' && (*line)++)
	{
		if (**line == '&' && (*line)++)
			return (new_token_node(LOGICAL_AND, "&&"));
	}
	printf("minishell: syntax error near unexpected token `%c'\n", **line);
	return (NULL);
}

static t_token	*tokenize_parenthesis(char **line)
{
	if (**line == '(' && (*line)++)
		return (new_token_node(OPEN_PARENTHESIS, "("));
	if (**line == ')' && (*line)++)
		return (new_token_node(CLOSE_PARENTHESIS, ")"));
	return (NULL);
}

static t_token	*tokenize_word(char **line)
{
	char	*closing_quote;
	char	*word;

	word = *line;
	while (**line != '\0' && !isspace(**line) && !reserved_shell_char(**line))
	{
		if (ft_isquote(**line))
		{
			closing_quote = find_closing_quote(*line);
			if (closing_quote == NULL)
				return (syntax_error_matching(**line), NULL);
			*line = closing_quote + 1;
		}
		else if (*(*line)++ == '\\')
			(*line)++;
	}
	return (new_token_node(WORD, strndup(word, *line - word)));
}

t_token	*tokenizer(char **line)
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
