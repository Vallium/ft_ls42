# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#    Updated: 2014/11/09 20:20:03 by adoussau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRC		= ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c \
		ft_strdup.c ft_strlen.c \
		ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
		ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strncmp.c \
		ft_strnstr.c ft_strcmp.c \
		ft_islower.c ft_isupper.c \
		ft_atoi.c \
		ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c \
		ft_isdigit.c ft_isalnum.c ft_isalpha.c ft_isspace.c \
		ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strclr.c ft_strdel.c ft_strequ.c ft_striter.c \
		ft_striteri.c ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strnequ.c \
		ft_strsplit.c ft_strsub.c ft_strtrim.c ft_itoa.c \
		ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		ft_lstmap.c
OBJ		= $(SRC:.c=.o)
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
ifeq ($(SYSTEM),Linux)
	FBSD_addons=strlcat.c strnstr.c
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) -I . -o $@ -c $? $(FLAGS)

.PHONY: clean fclean re test test2 testall

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

testall: test test2

test: re $(NAME)
	@curl -s http://pastebin.com/raw.php?i=p3BBP70K > main.c
	gcc -I . main.c $(FBSD_addons) libft.a
	@rm main.c
	./a.out

test2: re
	@curl http://pastebin.com/raw.php\?i\=KQRs4L2H > main.c
	gcc -I . main.c $(FBSD_addons) libft.a
	@rm main.c
	./a.out

re: fclean all
