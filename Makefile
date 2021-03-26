NAME = minishell

SRCS = srcs/main2.c srcs/get_next_line.c srcs/get_next_line_utils.c srcs/env.c \
	srcs/char.c srcs/quote.c srcs/error.c srcs/utils.c srcs/dollar.c \
	srcs/dollar_utils.c srcs/word.c srcs/my_split.c  \
	srcs/process_shell.c srcs/analysis_line.c srcs/char_escaped.c srcs/cmd.c \
	srcs/print.c srcs/built.c

OBJS = $(SRCS:.c=.o)

INCLD = -I includes -I libft

CC = clang

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -L libft

LIBS = -lft

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLD) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/$(NAME)

re: fclean all

.PHONY: all clean fclean re
