NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra
DFLAGS := -g3 -fsanitize=address

READLINE := $(shell brew --prefix readline)
LFLAGS := -lreadline -L $(READLINE)/lib

INCDIR := src/
HFLAGS := -I $(INCDIR) -I $(READLINE)/include
HFILES := $(INCDIR)minishell.h $(INCDIR)utilities.h \
		$(INCDIR)/utils/libftprintf/format_output/format_output.h \
		$(INCDIR)/utils/libftprintf/libftprintf.h

VPATH =	src/		\
		src/builtins	\
		src/executor	\
		src/expansion	\
		src/heredoc		\
		src/input		\
		src/lexer		\
		src/output		\
		src/parser		\
		src/signals		\
		src/syntax		\
		src/terminal	\
		src/utils		\
		src/utils/libftprintf \
		src/utils/libftprintf/format_output \
		src/utils/libftprintf/format_output/count_output \
		src/utils/libftprintf/format_output/fill_output \

SRCS =	cd.c echo.c env.c exit.c export.c pwd.c unset.c \
		assignment.c builtin.c conditional.c executor.c find_cmd_path.c \
		free_nodelist.c handle_redirects.c pipe_handler.c stdio_fildes.c \
		dollar_string_group.c dollar_string.c filename_expansion.c globbing.c \
		group_subpatterns.c parameter_expansion.c quote_removal.c shell_expansion.c \
		tilde_expansion.c heredoc.c history.c lexer.c token_types.c tokenizer.c \
		tokenlist.c output_error.c syntax_error.c nodelist.c parser.c redirections.c \
		table.c find_bad_substitution.c quoting.c reserved_shell_char.c syntax_validator.c \
		valid_token.c variables.c echoctl.c prompt.c signals.c \
		count_output.c count_signed.c count_text.c count_unsigned.c \
		fill_format.c fill_signed.c fill_text.c fill_unsigned.c \
		flags_handling.c format_output.c \
		ft_asprintf.c ft_dprintf.c ft_printf.c ft_vasprintf.c ft_vdprintf.c ft_vprintf.c \
		ft_calloc.c ft_concat.c ft_dict.c ft_dwrite.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isnumber.c ft_isquote.c ft_isspace.c ft_list.c ft_memcpy.c \
		ft_memset.c ft_setenv.c ft_strarr.c ft_strchr.c ft_strcmp.c ft_strdup.c \
		ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strndup.c ft_strrchr.c ft_strsep.c \
		ft_strstr.c ft_strtol.c ft_toupper.c ft_unsetenv.c main.c

OBJDIR := obj/
OBJS :=	$(addprefix $(OBJDIR),$(notdir $(SRCS:.c=.o)))

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(HFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: %.c $(HFILES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DFLAGS) $(HFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME).dSYM

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

exe: $(NAME)
	@./$(NAME)

.PHONY: all bonus clean fclean re exe
