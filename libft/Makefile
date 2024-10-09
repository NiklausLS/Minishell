# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makepipex                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 11:18:08 by nileempo          #+#    #+#              #
#    Updated: 2023/12/11 14:07:53 by nileempo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_strlen.c ft_strlen_ptr.c \
	  ft_bzero.c \
	  ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  ft_toupper.c ft_tolower.c \
	  ft_atoi.c ft_itoa.c \
	  ft_strcmp.c ft_strncmp.c \
	  ft_strcpy.c ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_strdup.c \
	  ft_strchr.c ft_strrchr.c ft_strnstr.c ft_substr.c \
	  ft_strjoin.c \
	  ft_putchar_fd.c ft_putstr_fd.c \
	  ft_calloc.c \
	  ft_split.c \
	  ft_errorexit.c \
	  ft_strndup.c \
	  ft_putendl_fd.c \
	  ft_ischarset.c \

INC_PATH = ./includes

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra

NAME = libft.a

HEADER = libft.h

OBJ = $(SRC:.c=.o)

.c.o: $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_PATH)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
