# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 20:50:01 by nileempo          #+#    #+#              #
#    Updated: 2024/04/20 10:53:38 by nileempo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		./redirections/check_redirections.c \
		./redirections/manage_redirection.c \
		./protected_functions/protected_open.c \

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