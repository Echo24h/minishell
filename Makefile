# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gborne <gborne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 14:38:38 by gborne            #+#    #+#              #
#    Updated: 2022/07/27 23:32:37 by gborne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

TXT_BOLD = tput bold
TXT_NORMAL = tput sgr0

LIBFT = libft/libft.a
READLINE = -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = $(LIBFT) $(READLINE) -lreadline

VALGRIND = valgrind --suppressions=valgrind_readline.supp --leak-check=full --show-leak-kinds=definite

SRC = $(wildcard src/*.c src/*/*.c)
OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)


$(NAME) : $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@echo -e '\033[1mmake success\033[0m'

run: all
	./$(NAME)

leaks: all
	$(VALGRIND) ./$(NAME)

clean:
	@make clean -C libft
	@rm -f src/*.o src/*/*.o
	@echo -e '\033[1mclean success\033[0m'

fclean: clean
	@make fclean -C libft
	@rm -f minishell
	@echo -e '\033[1mfclean success\033[0m'

re: fclean all
	@make re -C libft
	@echo -e '\033[1mreboot success\033[0m'

.PHONY: all init_libft run leaks clean fclean re

#make -C libft
#$(OBJ)

#$(OBJ)
#$(call OBJ_LST $(OBJ))
#$(addprefix $(DIR_OBJ),$(lastword $(subst /, ,$(OBJ))))
#$(addprefix $(DIR_OBJ),$(lastword $(subst /, ,$(OBJ))))
#@echo ${addprefix $(DIR_OBJ),$(subst /,,$(OBJ))}
#@echo ${addprefix $(DIR_OBJ),$(shell echo $(OBJ) | tr ' ' '\n')}
#make -C libft
#@echo $(OBJ)

#@echo $(addprefix $(DIR_OBJ),$(lastword $(subst /, ,${<:$(DIR_SRC)%.c=%.o})))
#@echo $(addprefix $(DIR_OBJ),$(lastword $(subst /, ,$(<:%.c=%.o))))
#$(CC) $(CFLAGS) -c $< -o $(addprefix $(DIR_OBJ),$(lastword $(subst /, ,$(<:%.c=%.o))))


# $@ nom cible
# $< nom premiere dependance
# $^ liste depandances
# $? liste dependances plus recentes que la cible
# $* nom fichier, sans extension

#FUNCTION

#CLEAR_PATH = $(shell $1 rev | cut -d'/' -f-1 | rev)
#OBJ_LST = $(addprefix $(DIR_OBJ),$(subst builtin/,,$(subst parser/,,$(subst src/,,$1))))
#@echo ${addprefix $(DIR_OBJ), $(shell ${<:$(DIR_SRC)%.c=%.o} rev | cut -d'/' -f-1 | rev)}
#$(addprefix $(DIR_OBJ),$(subst builtin/,,$(subst parser/,,$(subst src/,,$(SRC:.c=.o)))))

