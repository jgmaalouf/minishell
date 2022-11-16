#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <dirent.h>

# include <readline/readline.h>
# include <readline/history.h>

/* malloc exit(EXIT_FAILURE) */

/* TERMINAL COLOR CODES */
# define NOC "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"

# define DELIMITERS "\"'$ =@(*)#:/"
# define WORDCHARS  ""    // '*?_-.[]~&;!#$%^(){}<>' WORDCHARS='~!#$%^&*(){}[]<>?.+;-'

# define ASCII_DELIMITERS "\t\n\v\f\r !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*cmd_name;

	char const		*cmd_path;
	char *const		*cmd_argv;


	int				stdinput;
	int				stdoutput;
	int				stderror;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token_type{
	/* NONE, */
	/* NEW_LINE, */
	WORD,
	PIPE,
	REDIRECT_INPUT_FILE,
	REDIRECT_INPUT_HEREDOC,
	REDIRECT_OUTPUT_TRUNC,
	REDIRECT_OUTPUT_APPEND,
	LOGICAL_AND,
	LOGICAL_OR,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*val;
	struct s_token	*next;
}	t_token;


/* PROHIBITED */
#include <ctype.h>
#include <string.h>
/* PROHIBITED */

t_env	*preprocess_environment(char **envp);
t_cmd	*parser(char *line, t_env *env);

bool	token_is_word(t_token_type type);
bool	token_is_logical_operand(t_token_type type);
bool	token_is_redirection(t_token_type type);
bool	token_is_parenthesis(t_token_type type);

char	*tilde_expansion(char *word);
char	*parameter_expansion(char *word, t_env *env);
t_token	*filename_expansion(t_token	*token);
t_token	*lexer(char *line);
int	validate_syntax(t_token *tokens);
void	*free_tokens(t_token *tokens);

int	syntax_error_end_of_file(void);
int	syntax_error_unexpected_token(char *c);
int	syntax_error_matching(char c);
int	syntax_error_bad_substitution(char *word);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));

char*	ft_concat(const char *s1, const char *s2);
int		find_bad_substitution(char *line);
t_cmd	*create_cmd_table(t_token *tokens);
void	executor(t_cmd *table);

void	debugging_log_print_env(t_env *env);

#endif
