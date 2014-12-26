# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 12:03:10 by aalliot           #+#    #+#              #
#    Updated: 2014/12/16 20:58:42 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
SRC		= main.c ft_get_opt.c ft_lst_bbl_sort.c
OBJ		= $(SRC:.c=.o)
HDR		= libft/includes/
FLAGS	= #-Wall -Wextra -Werror
CC		= gcc

.PHONY: test clean cleanlib fclean re 42

%.o: %.c
	@$(CC) $(FLAGS) -I $(HDR) -I . -o $@ -c $?

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[H\033[2J"
	@echo "\033[36m...\033[33m╦ ╦╔═╗╦  ╦  ╔═╗  ╦  ╦╔═╗╦  ╦  ╦╦ ╦╔╦╗\033[36m...";
	@echo "\033[36m───\033[33m╠═╣║╣ ║  ║  ║ ║  ╚╗╔╝╠═╣║  ║  ║║ ║║║║\033[36m───";
	@echo "\033[36m   \033[33m╩ ╩╚═╝╩═╝╩═╝╚═╝   ╚╝ ╩ ╩╩═╝╩═╝╩╚═╝╩ ╩\033[0m   ";
	@echo "\033[01m\033[32m\n\xf0\x9f\x91\x8c  COMPILATION OF FDF \xf0\x9f\x91\x8c\n\033[0m"
	@echo "\033[31mCompilation time detail:"
	@time make -C libft/ fclean && make -C libft/ && $(CC) $(FLAGS) -o $(NAME)\
		$(OBJ) libft/libft.a
	@echo "\033[01m\033[32m\n\xf0\x9f\x91\x8c  PROGRAM COMPILED ! \xf0\x9f\x91\x8c\n\033[0m"

clean:
	@rm -f $(OBJ)

cleanlib:
	@make -C libft/ fclean

fclean: clean cleanlib
	@rm -f $(NAME)

re: fclean all
