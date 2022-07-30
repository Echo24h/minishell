# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gborne <gborne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 20:36:50 by gborne            #+#    #+#              #
#    Updated: 2022/07/30 20:36:52 by gborne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $@ $(OBJ)
	@echo -e '\033[1mmake libft success\033[0m'

clean:
	@rm -f src/*.o
	@echo -e '\033[1mclean libft success\033[0m'

fclean: clean
	@rm -f $(NAME)
	@echo -e '\033[1mfclean libft success\033[0m'

re: fclean all
	@echo -e '\033[1mreboot libft success\033[0m'

.PHONY: all clean fclean re
