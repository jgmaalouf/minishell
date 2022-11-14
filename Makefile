NAME := minishell

CC := gcc
# CFLAGS := -Wall -Werror -Wextra # -g3
LFLAGS := -lreadline -L/Users/rmeuth/.brew/opt/readline/lib

INCDIR := src/
HFLAGS := -I $(INCDIR) -I/Users/rmeuth/.brew/opt/readline/include
HFILES := $(INCDIR)minishell.h


vpath %.c src/		\
	src/env			\
	src/expansion	\
	src/lexer		\
	src/output		\
	src/parser		\
	src/utils

SRCS := src/*.c			\
	src/env/*.c			\
	src/expansion/*.c	\
	src/lexer/*.c		\
	src/output/*.c		\
	src/parser/*.c		\
	src/utils/*.c

# SRCS := src/*.c src/env/*.c
# SRCS := src/**/*.c

OBJDIR := obj/
# OBJS := $(SRCS:src/%.c=obj/%.o)
# OBJS := $(SRCS:src/%.c=$(OBJDIR)%.o)
# OBJS := $(addprefix $(OBJDIR), $(SRCS:src/%.c=.o))
OBJS = $(patsubst ./src/%.c, $(OBJDIR)%.o, $(SRCS))


all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: src/%.c
# obj/%.o: src/%.c $(HFILES)
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
	./$(NAME)

.PHONY: all bonus clean fclean re exe
