#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/history.h>
# include <readline/readline.h>

# include "utilities.h"
# include "garbage.h"

/* TERMINAL COLOR CODES */
# define RESET	"\001\e[0m\002"
# define BOLD	"\001\e[1m\002"
# define THIN	"\001\e[2m\002"
# define ITALIC	"\001\e[3m\002"
# define UNDRLN	"\001\e[4m\002"
# define RED	"\001\e[31m\002"
# define GREEN	"\001\e[32m\002"
# define YELLOW	"\001\e[33m\002"
# define BLUE	"\001\e[34m\002"
# define PINK	"\001\e[35m\002"
# define CYAN	"\001\e[36m\002"

/* PERSISTENT HISTORY FILE */
# define HISTFILE_RDONLY ".minishell_history"
# define HISTFILE_WRONLY ".minishell_history"

/* GLOBAL VARIABLE */
int	g_exit_status;

# pragma region enums

typedef enum e_builtin {
	NO_BUILTIN,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
}	t_builtin;

typedef enum e_token_type {
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
}	t_tk_type;

# pragma endregion enums

# pragma region structs

typedef struct s_token
{
	t_tk_type		type;
	char			*val;
	bool			expanded;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd_name;
	const char		*cmd_path;
	char *const		*cmd_argv;
	int				cmd_argc;
	t_builtin		builtin_id;

	int				stdinput;
	int				stdoutput;
	// int				stderror;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pattern
{
	char		*str;
	const char	*ptr;
	int			len;
	int			asterisk;
	int			question_mark;
	bool		wildcard;
}	t_pat;

# pragma endregion structs

# pragma region functions

/* BUILTINS */
int		cd(int argc, char *const argv[]);
int		echo(int argc, char *const argv[]);
int		env(void);
int		builtin_exit(t_cmd *table);
void	export(int argc, char *const argv[]);
int		pwd(void);
void	unset(char *argv[]);

/* EXECUTOR */
void	executor(t_cmd *table);

/* PARSER */
t_cmd	*parser(char *line);
t_cmd	*create_cmd_table(t_token *tokens);

/* LEXER */
t_token	*lexer(char *line);
t_token	*tokenizer(char **line);
t_token	*new_token_node(int type, char *val);
void	token_list_add_back(t_token **list, t_token *new);
void	*free_token_list(t_token *tokens);
int		reserved_shell_char(int c);
bool	token_is_word(t_tk_type type);
bool	token_is_logical_operand(t_tk_type type);
bool	token_is_redirection(t_tk_type type);
bool	token_is_parenthesis(t_tk_type type);

/* EXPANSION */
int		globbing(t_pat groups[], const char *filename);
t_pat	*group_subpatterns(const char *pattern);
void	free_pattern_groups(t_pat groups[]);
t_token	*filename_expansion(t_token	*token);
char	*parameter_expansion(char *word);
t_list	*subdivide_dollar_word(char *word);
char	*quote_removal(char *word);
void	shell_expansion(t_token *tokens);
char	*tilde_expansion(char *word);

/* HISTORY */
int		set_history_file_path(const char *filename);
int		read_history_file(const char *filename);
int		command_history(const char *line);

/* SYNTAX */
int		find_bad_substitution(char *line);
char	*find_closing_quote(const char *input);
int		syntax_validator(t_token *tokens);
int		valid_token(t_token *token);

/* SIGNALS */
void	signal_handler(int signal);
void	signal_ctrl_c(int signal);
void	signal_ctrl_c_runtime(int signal);
void	signal_ctrl_backslash(int signal);

/* ERROR */
int		syntax_error_end_of_file(void);
int		syntax_error_unexpected_token(char *c);
int		syntax_error_matching(char c);
int		syntax_error_bad_substitution(char *word);
int		output_error(char *cmd, char *msg);
int		output_error_arg(char *cmd, char *arg, char *msg);
int		output_error_quoted_arg(char *cmd, char *arg, char *msg);
int		fatal_error(void);

/* TERMINAL */
char	*generate_prompt(void);

/* DEBUGGING */
void	debugging_log_token_list(t_token *tokens);
void	debugging_log_pattern_groups(t_pat groups[]);

# pragma endregion functions

#endif
