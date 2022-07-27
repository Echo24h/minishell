# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gborne <gborne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 18:17:20 by gborne            #+#    #+#              #
#    Updated: 2022/07/27 21:22:14 by gborne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $(OBJ)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
