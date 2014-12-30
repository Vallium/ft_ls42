# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#    Updated: 2014/11/28 15:13:43 by adoussau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= ft_ls
DEBUG_EXE	= ft_ls_debug

SRC		=	main.c			\
			ft_get_opt.c

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

HEAD_DIR	= .
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
LIBFT		= libft/libft.a
LIBFT_HEAD	= libft/includes/

CC			= gcc
FLAGS		= -Wall -Wextra -Werror

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)

$(DEBUG_EXE): $(DEBUG_OBJ)
	@$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(DEBUG_OBJ) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ)
	@$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT) $(FLAGS) -g

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	@$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	@$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS) -g

$(LIBFT):
	@make -C libft

.PHONY: clean fclean re

clean:
	@make -C libft clean
	@rm -f $(STATIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(STATIC_EXE) $(DEBUG_EXE)

re: fclean all
