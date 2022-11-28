#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <dirent.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "utilities.h"
# include "garbage.h"

/* TERMINAL COLOR CODES */
# define NOC "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"

# define HISTFILE        ".minishell"
# define HISTFILE_RDONLY ".minishell_history"
# define HISTFILE_WRONLY ".minishell_history"

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

typedef struct s_cmd
{
	char			*cmd_name;
	const char		*cmd_path;
	char *const		*cmd_argv;


	int				stdinput;
	int				stdoutput;
	// int				stderror;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token_type {
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

int	g_exit_status;


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
bool	token_is_word(t_token_type type);
bool	token_is_logical_operand(t_token_type type);
bool	token_is_redirection(t_token_type type);
bool	token_is_parenthesis(t_token_type type);
void	*free_tokens(t_token *tokens);

/* EXPANSION */
t_token	*filename_expansion(t_token	*token);
char	*parameter_expansion(char *word);
char	*quote_removal(char *word);
void	shell_expansion(t_token *tokens);
char	*tilde_expansion(char *word);

/* HISTORY */
int		set_history_file_path(const char *filename);
int		read_history_file(const char *filename);
int		command_history(const char *line);

/* SYNTAX */
int		find_bad_substitution(char *line);
char	*find_closing_quote(char *input);
int		validate_syntax(t_token *tokens);
int		validate_token(t_token *token);

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

/* TERMINAL */
char	*generate_prompt(void);

/* DEBUGGING */
void	debugging_log_token_list(t_token *tokens);

#endif
