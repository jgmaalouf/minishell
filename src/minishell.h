#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

# include <readline/history.h>
# include <readline/readline.h>

# include "utilities.h"

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
int	g_exit_status;

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
	TK_NEWLINE,
}	t_tk_type;

typedef enum e_node_type
{
	NODE_NULL,
	NODE_COMMAND,
	NODE_ASSIGNMENT,
	NODE_PIPE,
	NODE_AND_IF,
	NODE_OR_IF,
	NODE_SUBSHELL,
	NODE_SEMICOLON,
}	t_node_type;

typedef enum e_heredoc_action
{
	HEREDOC_COLLECT,
	HEREDOC_OBTAINE,
	HEREDOC_DESTROY,
}	t_heredoc_action;

typedef enum e_stdfd_action
{
	SAVE_STD_FILDES,
	RESTORE_STD_FILDES,
	CLOSE_STD_FILDES_DUPS,
}	t_stdfd_action;

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
	int				fd;
	const char		*n;
	const char		*path;
	int				oflag;
	mode_t			mode;
	bool			heredoc;
	bool			input;
	bool			output;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int				cmd_argc;
	char *const		*cmd_argv;
	const char		*cmd_path;
	t_builtin		builtin_id;
	t_redir			*redirlist;
}	t_cmd;

typedef struct s_node
{
	pid_t			pid;
	t_node_type		type;
	t_node_type		nexus;
	int				pipe[2];
	t_cmd			*table;
	t_token			*tokenlist;
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
int			builtin_cd(int argc, char *const argv[]);
int			builtin_echo(int argc, char *const argv[]);
int			builtin_env(void);
int			builtin_exit(int argc, char *const argv[], t_node *nodelist);
int			builtin_export(int argc, char *const argv[]);
int			builtin_pwd(void);
int			builtin_unset(int argc, char *const argv[]);

/* EXECUTOR */
int			identify_builtin(char *cmd_name);
int			execute_builtin(t_node *nodelist);
int			execute_command(t_cmd *table);
int			launch_command(t_node *nodelist);
t_node		*handle_conditional(t_node *nodelist);
int			waitpid_exit_status(pid_t pid);
t_node		*node_handler(t_node *nodelist);
int			executor(t_node *nodelist);
char		*find_cmd_path(char *cmd_name);
void		*free_nodelist(t_node *nodelist);
t_node		*free_node(t_node *node);
int			handle_redirects(t_redir *redirlist);
int			launch_pipe(t_node *nodelist);
t_node		*handle_pipeline(t_node *nodelist);
int			stdio_fildes_handler(int action);
t_node		*subshell_extract_nodelist(t_node *nodelist);
int			launch_subshell(t_node *nodelist);

/* EXPANSION */
char		*process_dollar_string_group(char *group);
char		*expand_dollar_variable(char *name);
t_token		*filename_expansion(t_token	*token);
int			globbing(t_pat groups[], const char *filename);
char		*concatenate_subwords(t_list *subwords);
t_pat		*group_subpatterns(const char *pattern);
void		free_pattern_groups(t_pat groups[]);
char		*parameter_expansion(char *word);
char		*quote_removal(char *word);
void		shell_expansion(t_token *tokenlist);
char		*tilde_expansion(char *word);

/* INPUT */
int			heredoc_handler(int action, t_token *tokenlist);
int			heredoc(const char *delimiter);
int			set_history_file_path(const char *filename);
int			read_history_file(const char *filename);
int			command_history(const char *line);

/* LEXER */
t_token		*lexer(char *line);
bool		token_is_simple_word(t_tk_type type);
bool		token_is_word(t_tk_type type);
bool		token_is_redirection(t_tk_type type);
bool		token_is_logical_operand(t_tk_type type);
bool		token_is_parenthesis(t_tk_type type);
t_token		*tokenizer(char **line);
t_token		*new_token_node(int type, char *val);
void		tokenlist_add_back(t_token **list, t_token *new);
void		*free_tokenlist(t_token *list, bool content);

/* OUTPUT */
int			error_output(char *cmd, char *msg);
int			error(char *cmd, char *msg, int status);
int			error_argv(char *cmd, char *arg, char *msg);
int			error_argv_quoted(char *cmd, char *arg, char *msg);
int			fatal_error(int code);
int			syntax_error_bad_substitution(char *word);
int			syntax_error_end_of_file(void);
int			syntax_error_matching(char c);
int			syntax_error_unexpected_token(char *c);

/* PARSER */
t_node_type	convert_tk_type(t_tk_type type);
bool		node_is_block_separator(t_node_type type);
bool		node_is_command_separator(t_node_type type);
bool		token_is_command_separator(t_tk_type type);
bool		node_is_conditional(t_node_type type);
t_node		*create_nodelist(t_token *tokenlist);
t_node		*parser(char *cmdline);
void		parse_redirection(t_token **tokenlist, t_cmd *table);
t_cmd		*create_command_table(t_token **tokenlist);

/* SYNTAX */
int			find_bad_substitution(char *line);
char		*find_next_quote(const char *input);
char		*find_closing_quote(const char *input);
char		*find_unquoted_char(const char *input, int c);
int			reserved_shell_char(int c);
int			valid_first_token(t_token *token);
int			syntax_validator(t_token *tokenlist);
int			valid_token(t_token *token);
int			valid_variable_name(const char *name);
int			valid_variable_identifier(const char *name);
int			valid_parameter_assignment(const char *word);

/* TERMINAL */
void		disable_echoctl(void);
char		*generate_prompt(void);
void		signal_ctrl_c_input(int signal);
void		signal_ctrl_c_runtime(int signal);
void		signal_ctrl_backslash(int signal);
int			exit_ctrl_d(void);

# pragma endregion functions

#endif
