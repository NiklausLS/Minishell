# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 20:50:01 by nileempo          #+#    #+#              #
#    Updated: 2024/10/10 05:21:01 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./sources/main.c \
		./sources/builtins/echo.c \
		./sources/builtins/export.c \
		./sources/builtins/export2.c \
		./sources/builtins/sort_export.c \
		./sources/builtins/pwd.c \
		./sources/builtins/unset.c \
		./sources/builtins/built_in.c \
		./sources/builtins/cd.c \
		./sources/builtins/exit.c \
		./sources/builtins/env.c \
		./sources/cleans/free_exec.c \
		./sources/debug/errors_messages.c \
		./sources/inits/init_execution.c \
		./sources/parsing/parse_args.c \
		./sources/parsing/check_redirections.c \
		./sources/redirections/heredoc.c \
		./sources/redirections/redirections_errors.c \
		./sources/redirections/make_redirections.c \
		./sources/redirections/opens.c \
		./sources/redirections/redirection_utils.c \
		./sources/executions/path.c \
		./sources/executions/pipes.c \
		./sources/executions/execution.c \
		./sources/executions/exec_utils.c \
		./sources/protected_functions/protected_open.c \
		./sources/signals/heredoc_signal.c \
		./sources/utils/input_management.c \
		./sources/utils/input_management_2.c \
		./sources/utils/token_utils.c \
		./sources/utils/utils.c \

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=gnu99 -I/opt/homebrew/opt/readline/include #-fsanitize=address
INC_PATH = ./includes
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)

$(NAME): $(OBJS)
	make -C ./LIBFT
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) LIBFT/libft.a $(LDFLAGS)

all: $(NAME)

clean:
	make clean -C ./LIBFT
	rm -f $(NAME)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./LIBFT

re: fclean all

.PHONY: all clean fclean re