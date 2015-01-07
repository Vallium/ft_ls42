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

statsIC_EXE	= ft_ls
DEBUG_EXE	= ft_ls_debug

SRC		=	main.c					\
			ft_get_opt.c			\
			file_name_cmp.c			\
			file_r_name_cmp.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)

SRC	+= 							\
		file_r_time_cmp_linux.c	\
		file_time_cmp_linux.c	\
		print_date_linux.c

endif
ifeq ($(UNAME_S),Darwin)
SRC	+=							\
		file_r_time_cmp_macos.c	\
		file_time_cmp_macos.c	\
		print_date_macos.c
endif

statsIC_OBJ	= $(patsubst %.c,$(statsIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
statsIC_DIR	= statsic
LIBFT		= libft/libft.a
LIBFT_HEAD	= libft/includes/

CC			= gcc
FLAGS		= -Wall -Wextra -Werror

$(shell mkdir -p $(statsIC_DIR) $(DEBUG_DIR))

all: $(statsIC_EXE)

debug: $(DEBUG_OBJ)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT) $(FLAGS) -g

$(statsIC_EXE): $(statsIC_OBJ)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(statsIC_OBJ) $(LIBFT) $(FLAGS)

$(statsIC_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS) -g

$(LIBFT):
	make -C libft

.PHONY: clean fclean re debug norme

clean:
	make -C libft clean
	rm -f $(statsIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(statsIC_EXE) $(DEBUG_EXE)

norme:
	make -C libft norme
	norminette $(patsubst %,$(SRC_DIR)/%,$(SRC)) $(HEAD_DIR)/ft_ls.h

re: fclean all
