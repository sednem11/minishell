# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 15:42:27 by macampos          #+#    #+#              #
#    Updated: 2024/10/09 18:01:20 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/starting_shell.c parsing/parsargs.c parsing/pars_helpers.c parsing/builtins/cd.c parsing/builtins/echo.c parsing/builtins/env.c parsing/builtins/pwd.c parsing/builtins/export.c \
		parsing/builtins/echo_helpers.c parsing/builtins/echo_helpers2.c parsing/builtins/export_helper.c parsing/builtins/unset.c parsing/builtins/exit.c parsing/parsargs_utils2.c parsing/parsargs_utils3.c parsing/parsargs_utils4.c parsing/parsargs_utils.c parsing/utils.c parsing/split2.c \
		parsing/signals.c parsing/signal2.c src/starting_shell_helper.c src/starting_shell_helper2.c parsing/builtins/utils4.c parsing/utils2.c parsing/utils5.c src/redirections_helpers.c parsing/utils3.c parsing/check_redirections.c src/main_utils.c\

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

norminette:
	python3 -m c_formatter_42 $(SRC) includes/minishell.h
	python3 -m norminette $(SRC) includes/minishell.h

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all ./${NAME}
#valgrind --suppressions=readline.supp --tool=memcheck --tool=callgrind  --track-fds=yes ./${NAME}

re: fclean all