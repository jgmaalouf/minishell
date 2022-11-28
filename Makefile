NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra -g3
# CFLAGS := -g3
# LFLAGS := -lreadline -L/opt/homebrew/opt/readline/lib
LFLAGS := -lreadline -L ~/.brew/opt/readline/lib

INCDIR := src/
# HFLAGS := -I $(INCDIR) -I/opt/homebrew/opt/readline/include
HFLAGS := -I $(INCDIR) -I ~/.brew/opt/readline/include
HFILES := $(INCDIR)minishell.h

vpath %.c src/		\
	src/builtins	\
	src/env			\
	src/executor	\
	src/expansion	\
	src/input		\
	src/lexer		\
	src/output		\
	src/parser		\
	src/signals		\
	src/syntax		\
	src/utils

SRCDIR := src/
SRCS := $(wildcard src/**/*.c)
SRCS += src/main.c

OBJDIR := obj/
OBJS := $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
#OBJS := $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

# echo:
# 	@echo $(SRCS)
# 	@echo $(OBJS)

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HFILES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HFLAGS) -c $< -o $@

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
