# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by aalliot           #+#    #+#              #
#    Updated: 2014/11/28 15:13:43 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= ft_ls
DEBUG_EXE	= ft_ls_debug

SRC		=	main.c				\
			ft_get_opt.c		\
			file_name_cmp.c		\
			file_r_name_cmp.c	\
			file_size_cmp.c		\
			file_r_size_cmp.c	\
			ls_l.c				\
			print1.c			\
			print2.c			\
			tab1.c				\
			tab2.c				\
			to_wedge.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)

SRC	+= 							\
		file_r_time_cmp_linux.c	\
		file_time_cmp_linux.c	\
		printacl_linux.c		\
		print_date_linux.c

endif
ifeq ($(UNAME_S),Darwin)
SRC	+=							\
		file_r_time_cmp_macos.c	\
		file_time_cmp_macos.c	\
		printacl_macos.c		\
		print_date_macos.c
endif

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
LIBFT_STATIC= libft/libft.a
LIBFT_DEBUG	= libft/libft_debug.a
LIBFT_HEAD	= libft/includes/

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NORMINETTE	= ~/project/colorminette/colorminette

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)

debug: $(DEBUG_EXE)

$(DEBUG_EXE): $(DEBUG_OBJ) $(LIBFT_DEBUG)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT_DEBUG) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ) $(LIBFT_STATIC)
	$(CC) -O3 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT_STATIC) $(FLAGS)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -O3 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS) -g

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re debug norme normeLibft

clean:
	@make -C libft clean
	@rm -f $(STATIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(STATIC_EXE) $(DEBUG_EXE)

normeLibft:
		@make -C libft norme

norme: normeLibft
	@$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/

re: fclean
	make
