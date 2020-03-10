# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguillot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 17:11:35 by aguillot          #+#    #+#              #
#    Updated: 2020/03/10 16:36:56 by schakor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = src/

SRC_NAME = main.c \
		   ft_fdf.c \
		   ft_map_reader.c \
		   ft_fatal_exit.c \
		   ft_draw.c \


INC = include/

OBJ_PATH = build/

CPPFLAGS = -Wall -Wextra -Werror

LDLIBS = -I include libft/libft.a -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit

NAME = fdf

CC = gcc

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(LDLIBS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -I include $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	rm -fv $(NAME)

lftclean:
	make clean -C libft

lftfclean:
	make fclean -C libft

re: fclean all

norme:
	norminette src/*
	norminette libft/**.[ch]
	norminette include/.h
.PHONY: all, clean, fclean, re
