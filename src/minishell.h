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
/* PROHIBITED */
#include <ctype.h>
#include <string.h>

/* PERSISTENT HISTORY FILE */
# define HISTFILE_RDONLY ".minishell_history"
# define HISTFILE_WRONLY ".minishell_history"

/* TERMINAL COLOR CODES */
# define RESET   "\001\e[0m\002"
# define BOLD    "\001\e[1m\002"
# define THIN    "\001\e[2m\002"
# define ITALIC  "\001\e[3m\002"
# define UNDRLN  "\001\e[4m\002"
# define BLACK   "\001\e[30m\002"
# define RED     "\001\e[31m\002"
# define GREEN   "\001\e[32m\002"
# define YELLOW  "\001\e[33m\002"
# define BLUE    "\001\e[34m\002"
# define MAGENTA "\001\e[35m\002"
# define CYAN    "\001\e[36m\002"
# define WHITE   "\001\e[37m\002"

/* GLOBAL VARIABLE */
static int	g_exit_status;

# pragma region enums

typedef enum e_builtin {
	NOT_BUILTIN,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
}	t_builtin;

typedef enum e_token_type {
	TK_NULL,
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_IO_NUMBER,
	TK_REDIRECT_INPUT,
	TK_REDIRECT_INPUT_HEREDOC,
	TK_REDIRECT_INPUT_OUTPUT,
	TK_REDIRECT_OUTPUT_TRUNC,
	TK_REDIRECT_OUTPUT_CLOBBER,
	TK_REDIRECT_OUTPUT_APPEND,
	TK_BACKGROUND,
	TK_PIPE,
	TK_PIPE_STDERR,
	TK_LOGICAL_AND,
	TK_LOGICAL_OR,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS,
	TK_SEMICOLON,
	TK_DSEMICOLON,
	TK_NEWLINE,
}	t_tk_type;

typedef enum e_node_type
{
	NODE_NULL,
	NODE_COMMAND,
	NODE_ASSIGNMENT,
	/* NODE_REDIRECTION, */
	NODE_BACKGROUND,
	NODE_PIPE,
	NODE_AND_IF,
	NODE_OR_IF,
	NODE_SUBSHELL,
	NODE_SEMICOLON,
}	t_node_type;

# pragma endregion enums

# pragma region structs

typedef struct s_token
{
	t_tk_type		type;
	char			*val;
	bool			expanded;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_tk_type		type;
	bool			input;
	bool			output;
	bool			heredoc;
	const char		*path;
	int				oflag;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int				cmd_argc;
	char *const		*cmd_argv;
	const char		*cmd_path;
	t_builtin		builtin_id;

	// t_redir			*input;
	// t_redir			*output;
	t_redir			*redirlist;
	int				pipe[2];
	pid_t			pid;

	// int				stdinput;
	// int				stdoutput;
	// int				stderror;
}	t_cmd;

typedef struct s_node
{
	pid_t			pid;
	t_node_type		type;
	t_node_type		nexus; /* relation */
	t_cmd			*table;
	int				pipe[2];
	struct s_node	*sub;
	struct s_node	*next;
}	t_node;

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
int		builtin_cd(int argc, char *const argv[]);
int		builtin_echo(int argc, char *const argv[]);
int		builtin_env(void);
int		builtin_exit(int argc, char *const argv[], t_node *nodelist);
int		builtin_export(int argc, char *const argv[]);
int		builtin_pwd(void);
int		builtin_unset(int argc, char *const argv[]);

/* EXECUTOR */
int		executor(t_node	*parser);
int		identify_builtin(char *cmd_name);
int		execute_builtin(t_node *nodelist);
char	*find_cmd_path(char *cmd_name);
t_node	*create_nodelist(t_token *tokenlist);

/* PARSER */
t_node	*parser(char *cmdline);
t_cmd	*create_cmd_table(t_token *tokenlist);
bool	token_is_command_separator(t_tk_type type);

/* LEXER */
t_token	*lexer(char *line);
t_token	*tokenizer(char **line);
t_token	*new_token_node(int type, char *val);
void	tokenlist_add_back(t_token **list, t_token *new);
void	*free_tokenlist(t_token *list, bool content);
int		reserved_shell_char(int c);
bool	token_is_simple_word(t_tk_type type);
bool	token_is_word(t_tk_type type);
bool	token_is_redirection(t_tk_type type);
bool	token_is_logical_operand(t_tk_type type);
bool	token_is_parenthesis(t_tk_type type);

/* EXPANSION */
int		globbing(t_pat groups[], const char *filename);
t_pat	*group_subpatterns(const char *pattern);
void	free_pattern_groups(t_pat groups[]);
t_token	*filename_expansion(t_token	*token);
char	*parameter_expansion(char *word);
t_list	*subdivide_dollar_word(char *word);
char	*quote_removal(char *word);
void	shell_expansion(t_token *tokenlist);
char	*tilde_expansion(char *word);

/* HISTORY */
int		set_history_file_path(const char *filename);
int		read_history_file(const char *filename);
int		command_history(const char *line);

/* SYNTAX */
int		find_bad_substitution(char *line);
char	*find_closing_quote(const char *input);
char	*find_unquoted_char(const char *input, int c);
int		syntax_validator(t_token *tokenlist);
int		valid_first_token(t_token *token);
int		valid_token(t_token *token);
int		valid_variable_name(const char *name);
int		valid_variable_identifier(const char *name);
int		valid_parameter_assignment(const char *word);

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
int		error_output(char *cmd, char *msg);
int		error(char *cmd, char *msg, int status);
int		error_argv(char *cmd, char *arg, char *msg);
int		error_argv_quoted(char *cmd, char *arg, char *msg);
int		fatal_error(int code);

/* TERMINAL */
char	*generate_prompt(void);

/* DEBUGGING */
void	debugging_log_tokenlist(t_token *tokenlist);
void	debugging_log_pattern_groups(t_pat groups[]);

# pragma endregion functions


# pragma region new

typedef enum e_std_fd_action {
	SAVE_STD_FILDES,
	RESTORE_STD_FILDES,
	CLOSE_STD_FILDES_DUPS,
}	t_std_fd_action;

typedef enum e_pipe_action {
	CLOSE_PIPE_READ_END,
	CLOSE_PIPE_WRITE_END,
	CLOSE_PIPE_FILEDES,
	OPEN_PIPE_FILEDES,
	DUP_PIPE_STDIN,
	DUP_PIPE_STDOUT,
}	t_pipe_action;

int		stdio_fildes_handler(int action);
int		redirect(t_redir *redirlist);
void	*free_nodelist(t_node *list);
t_node	*free_node(t_node *node);
bool	node_is_conditional(t_node_type type);
t_node	*handle_conditional(t_node *nodelist);
int		pipe_handler(int action);
t_cmd	*create_command_table(t_token **tokenlist);
int		token_is_semicolon(t_tk_type type);
t_redir	*parse_redirections(t_token *tokenlist);
void	*free_nodelist(t_node *list);
t_node	*next_node(t_node *nodelist);

# pragma endregion new

#endif
