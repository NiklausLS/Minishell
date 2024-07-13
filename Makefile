# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 20:50:01 by nileempo          #+#    #+#              #
#    Updated: 2024/07/13 13:12:13 by nileempo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		./builtins/echo.c \
		./builtins/exit.c \
		./builtins/export.c \
		./builtins/export2.c \
		./builtins/pwd.c \
		./builtins/unset.c \
		./cleans/cleans_parsing.c \
		./cleans/free_exec.c \
		./debug/debug_parsing.c \
		./debug/errors_messages.c \
		./inits/add_data_structure.c \
		./inits/init_execution.c \
		./inits/init_parsing_1.c \
		./inits/init_signals.c \
		./inits/inits_tests_parsing.c \
		./mallocs/malloc_parsing.c \
		./parsing/dollar.c \
		./parsing/split_1_4.c \
		./parsing/split_5_6.c \
		./parsing/parse_args.c \
		./redirections/check_redirections.c \
		./redirections/heredoc.c \
		./redirections/parsing_redirections.c \
		./redirections/redirections_errors.c \
		./redirections/redirections_makechild.c \
		./redirections/make_redirections.c \
		./redirections/opens.c \
		./utils/ft_lstnew.c \
		./utils/utils_parsing.c \
		./executions/path.c \
		./executions/pipes.c \
		./executions/execution.c \
		

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
INC_PATH = ./includes

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)

$(NAME): $(OBJS)
	make -C ./LIBFT
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) LIBFT/libft.a -lreadline

all: $(NAME)

clean:
	make clean -C ./LIBFT
	rm -f $(NAME)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./LIBFT

re: fclean all

.PHONY: all clean fclean re