# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 20:50:01 by nileempo          #+#    #+#              #
#    Updated: 2024/09/10 18:52:32 by nileempo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		./builtins/echo.c \
		./builtins/exit.c \
		./builtins/export.c \
		./builtins/export2.c \
		./builtins/sort_export.c \
		./builtins/pwd.c \
		./builtins/unset.c \
		./builtins/built_in.c \
		./builtins/cd.c \
		./cleans/free_exec.c \
		./debug/errors_messages.c \
		./inits/init_execution.c \
		./parsing/parse_args.c \
		./parsing/check_redirections.c \
		./redirections/heredoc.c \
		./redirections/parsing_redirections.c \
		./redirections/redirections_errors.c \
		./redirections/make_redirections.c \
		./redirections/opens.c \
		./utils/ft_lstnew.c \
		./executions/path.c \
		./executions/pipes.c \
		./executions/execution.c \
		./executions/exec_utils.c \
		./protected_functions/protected_open.c \
		./signals/heredoc_signal.c \
		./executions/exec_all.c \
		

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