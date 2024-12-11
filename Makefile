# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 19:49:02 by npolack           #+#    #+#              #
#    Updated: 2024/12/11 11:30:25 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= pipex
OBJ_DIR = obj
SRC_DIR = srcs
SRCS 	= pipex.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
LIBFT = libft/bin/libft.a
OBJS = $(SRCS: $(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = cc

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $< -o $(NAME) -L./libft/bin -lft 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

$(LIBFT) :
	make -C libft

clean :
	make clean -C libft
	rm -fr $(OBJ_DIR)

fclean : clean
	make fclean -C libft
	rm $(NAME)

re		: fclean all

.PHONY : all clean fclean re
