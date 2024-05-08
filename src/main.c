/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by macampos          #+#    #+#             */
/*   Updated: 2024/05/03 16:05:23 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int matrixlen(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		j++;
	}
	return(j);
}

t_main	*set_main(t_main *main, char **envp)
{
	int	j;
	
	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	main->env = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(envp[j]) + 1);
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
		j++;
	}
	j = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->export[j] = calloc(sizeof(char), ft_strlen(envp[j]) + 1);
		main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)envp[j], ft_strlen(envp[j]));
		j++;
	}
	return(main);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return(1);
	t_cmd	*cmd;
	t_main	*main;
	char	*user_input;

	main = NULL;
	cmd = NULL;
	(void)argv;
	main = set_main(main, envp);
	while (1)
	{
		user_input = readline("minishell> ");
		if(!user_input)
			return 1;
		if (*user_input != '\0')
		{
			cmd = initiate_args(user_input, main->env, cmd);
			add_history(user_input);
			main->next = execute_function(user_input, main->env, cmd, main);
			main = main->next;
		}
	}
}
