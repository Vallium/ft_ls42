# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#    Updated: 2014/11/06 10:35:24 by adoussau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRC		= ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c \
		ft_strdup.c ft_strlen.c \
		ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
		ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strncmp.c \
		ft_strnstr.c ft_strcmp.c \
		ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c \
		ft_isdigit.c ft_isalnum.c ft_isalpha.c ft_isspace.c \

OBJ		= $(SRC:.c=.o)
CMP		= gcc
FLAGS	= -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CMP) -I . -o $@ -c $? $(FLAGS)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
