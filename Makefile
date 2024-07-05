# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 20:50:01 by nileempo          #+#    #+#              #
#    Updated: 2024/07/05 22:10:42 by nileempo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		./inits/init_struc.c \
		./redirections/check_redirections.c \
		./redirections/manage_redirection.c \
		./redirections/redirection_errors.c \
		./redirections/heredoc_redir.c \
		./redirections/pipes_redirection.c \
		./protected_functions/protected_open.c \
		./builtin/built_in.c \
		./builtin/cd.c \
		./builtin/env.c \
		./builtin/exit.c \
		./executions/commands.c \
		./executions/check_path.c \
		./debug/print.c \
		./parsing/get_args.c \
		./utils/ft_lstnew.c \
		./utils/errors_messages.c \

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC_PATH = ./includes

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)

$(NAME): $(OBJS)
	MAKE -C ./LIBFT
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) LIBFT/libft.a

all: $(NAME)

clean:
	make clean -C ./LIBFT
	rm -f $(NAME)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./LIBFT

re: fclean all

.PHONY: all clean fclean re