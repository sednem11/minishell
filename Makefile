# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 15:42:27 by macampos          #+#    #+#              #
#    Updated: 2024/04/15 17:11:35 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/starting_shell.c parcing/parsargs.c parcing/builtins/cd.c parcing/builtins/echo.c parcing/builtins/env.c parcing/builtins/pwd.c parcing/builtins/export.c \
		parcing/builtins/unset.c parcing/builtins/exit.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

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