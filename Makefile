NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra
DFLAGS := -g3 -fsanitize=address

#READLINE := $(shell brew --prefix readline)
LFLAGS := -lreadline -L/opt/homebrew/opt/readline/lib
#LFLAGS := -lreadline -L ~/.brew/opt/readline/lib
#LFLAGS := -lreadline -L $(READLINE)/lib

INCDIR := src/
HFLAGS := -I $(INCDIR) -I/opt/homebrew/opt/readline/include
HFLAGS += -I $(INCDIR)utils/libftprintf
#HFLAGS := -I $(INCDIR) -I ~/.brew/opt/readline/include
#HFLAGS := -I $(INCDIR) -I $(READLINE)/include
HFILES := $(INCDIR)minishell.h $(INCDIR)utilities.h
HFILES += $(INCDIR)utils/libftprintf/libftprintf.h
HFILES += $(INCDIR)utils/libftprintf/format_output.h

vpath %.c src/		\
	src/builtins	\
	src/executor	\
	src/expansion	\
	src/input		\
	src/lexer		\
	src/output		\
	src/parser		\
	src/syntax		\
	src/terminal	\
	src/utils

SRCDIR := src/
SRCS := $(wildcard src/**/*.c)
SRCS += $(wildcard src/utils/libftprintf/*.c)
SRCS += $(wildcard src/utils/libftprintf/**/*.c)
SRCS += $(wildcard src/utils/libftprintf/**/**/*.c)
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
	@$(CC) $(CFLAGS) $(DFLAGS) $(HFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HFILES)
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
