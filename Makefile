# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 15:42:27 by macampos          #+#    #+#              #
#    Updated: 2024/04/26 15:14:06 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/starting_shell.c parsing/parsargs.c parsing/pars_helpers.c parsing/builtins/cd.c parsing/builtins/echo.c parsing/builtins/env.c parsing/builtins/pwd.c parsing/builtins/export.c \
		parsing/builtins/unset.c parsing/builtins/exit.c parsing/utils.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

$(NAME): $(OBJ)
	$(MAKE) -C ./includes/libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./includes/libft -lft -lm -lreadline

all: $(NAME)

clean:
	cd includes/libft && make clean
	rm -rf $(OBJ)

fclean: clean
	cd includes/libft && make fclean
	rm -rf $(NAME)

re: fclean all