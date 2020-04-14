# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguillot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 17:11:35 by aguillot          #+#    #+#              #
#    Updated: 2018/11/29 11:52:50 by aguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = src/

SRC_NAME = main.c\
		ft_draw.c\
		ft_fatal_exit.c\
		ft_fdf.c\
		ft_map_reader.c\

OBJ_PATH = build/

CPPFLAGS = -I include -I libft

LDLIBS = libft/libft.a mlx/libmlx_Linux.a -lXext -lX11

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) -fPIC $^ $(LDLIBS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -DFOO -o $@ -c $<

clean:
	rm -fv $(OBJ)
	make clean -C libft
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C libft
	rm -fv $(NAME)

re: fclean all

norme:
	norminette src/*
	norminette libft/**.[ch]
	norminette include/ft_select.h
.PHONY: all, clean, fclean, re