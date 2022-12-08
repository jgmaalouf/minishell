#include "minishell.h"

static t_token	*tokenize_redirection(char **line)
{
	if (**line == '<' && (*line)++)
	{
		if (**line == '<' && (*line)++)
			return (new_token_node(TK_REDIRECT_INPUT_HEREDOC, "<<"));
		if (**line == '>' && (*line)++)
			return (new_token_node(TK_REDIRECT_INPUT_OUTPUT, "<>"));
		return (new_token_node(TK_REDIRECT_INPUT, "<"));
	}
	if (**line == '>' && (*line)++)
	{
		if (**line == '>' && (*line)++)
			return (new_token_node(TK_REDIRECT_OUTPUT_APPEND, ">>"));
		if (**line == '|' && (*line)++)
			return (new_token_node(TK_REDIRECT_OUTPUT_CLOBBER, ">|"));
		return (new_token_node(TK_REDIRECT_OUTPUT_TRUNC, ">"));
	}
	return (NULL);
}

static t_token	*tokenize_logical_operand(char **line)
{
	if (**line == '|' && (*line)++)
	{
		if (**line == '|' && (*line)++)
			return (new_token_node(TK_LOGICAL_OR, "||"));
		if (**line == '&' && (*line)++)
			return (new_token_node(TK_PIPE_STDERR, "|&"));
		return (new_token_node(TK_PIPE, "|"));
	}
	if (**line == '&' && (*line)++)
	{
		if (**line == '&' && (*line)++)
			return (new_token_node(TK_LOGICAL_AND, "&&"));
		return (new_token_node(TK_BACKGROUND, "&"));
	}
	printf("minishell: syntax error near unexpected token `%c'\n", **line);
	return (NULL);
}

static t_token	*tokenize_special(char **line)
{
	if (**line == '(' && (*line)++)
		return (new_token_node(TK_OPEN_PARENTHESIS, "("));
	if (**line == ')' && (*line)++)
		return (new_token_node(TK_CLOSE_PARENTHESIS, ")"));
	if (**line == ';' && (*line)++)
		return (new_token_node(TK_SEMICOLON, ";"));
	return (NULL);
}

static t_token	*tokenize_word(char **line)
{
	char	*closing_quote;
	char	*word;

	word = *line;
	while (**line != '\0' && !reserved_shell_char(**line))
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
	word = strndup(word, *line - word);
	if (word == NULL)
		exit(fatal_error(ENOMEM));
	if ((**line == '<' || **line == '>') && ft_isnumber(word))
		return (new_token_node(TK_IO_NUMBER, word));
	return (new_token_node(TK_WORD, word));
}

t_token	*tokenizer(char **line)
{
	if (**line == '<' || **line == '>')
		return (tokenize_redirection(line));
	if (**line == '|' || **line == '&')
		return (tokenize_logical_operand(line));
	if (**line == '(' || **line == ')' || **line == ';')
		return (tokenize_special(line));
	if (isascii(**line))
		return (tokenize_word(line));
	return (NULL);
}
