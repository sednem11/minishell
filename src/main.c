/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by macampos          #+#    #+#             */
/*   Updated: 2024/08/21 00:06:50 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(char *input)
{
	int	i;

	i = 1;
	if (input[0] == '"' || input[0] == 39)
	{
		if (input[0] == input[1] && !input[2])
			return (i);
		while (input[i])
		{
			if ((input[0] == '"' || input[0] == 39) && !input[i + 1])
				break ;
			if (input[i] != ' ' && input[i] != '"' && input[i] != 39)
				return (0);
			i++;
		}
		if (input[i] != '"' && input[i] != 39)
			return (0);
		return (i);
	}
	return (0);
}

t_main	*main_helper2(t_cmd *cmd, t_main *main, t_main *next, char *user_input)
{
	cmd = initiate_args(user_input, main->env, cmd, main);
	add_history(user_input);
	if (cmd == NULL)
		next = main;
	else
		next = execute_function(user_input, main->env, cmd, main);
	if (cmd)
		free_cmd_args(cmd);
	return (next);
}

int	main_helper(t_cmd *cmd, t_main *main, char *user_input)
{
	if (!user_input)
	{
		free_env_and_export(main);
		free(main);
		if (cmd)
			free_cmd_args(cmd);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_main	*main;
	t_main	*next;
	char	*user_input;

	if (argc != 1)
		return (1);
	main = NULL;
	cmd = NULL;
	next = NULL;
	(void)argv;
	main = set_main(main, envp);
	while (1)
	{
		signal_main();
		user_input = readline("minishell> ");
		if (main_helper(cmd, main, user_input) == 1)
			return (1);
		if (*user_input != '\0' && check_input(user_input) == 0)
			main = main_helper2(cmd, main, next, user_input);
	}
}
