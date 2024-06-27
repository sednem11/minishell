/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 13:03:48 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	matrixlen(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		j++;
	}
	return (j);
}

t_main	*set_main(t_main *main, char **envp)
{
	int	j;

	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	if (envp[0] == NULL)
	{
		main->env = calloc(sizeof(char *), 4);
		main->env[0] = ft_strdup("PWD=/home/macampos/minishell");
		main->env[1] = ft_strdup("SHLVL=1");
		main->env[2] = ft_strdup("_=/usr/bin/env");
		main->export = calloc(sizeof(char *), 4);
		main->export[0] = ft_strdup("PWD=/home/macampos/minishell");
		main->export[1] = ft_strdup("SHLVL=1");
		main->export[2] = ft_strdup("_=/usr/bin/env");
		return (main);
	}
	main->env = calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(envp[j]) + 1);
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j],
				ft_strlen(envp[j]));
		j++;
	}
	j = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		main->export[j] = calloc(sizeof(char), ft_strlen(envp[j]) + 1);
		main->export[j] = (char *)ft_memcpy((void *)main->export[j],
				(void *)envp[j], ft_strlen(envp[j]));
		j++;
	}
	return (main);
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
	(void)argv;
	main = set_main(main, envp);
	while (1)
	{
		signal_main();
		user_input = readline("minishell> ");
		if (!user_input)
		{
			free_env_and_export(main);
			free(main);
			if (cmd)
				free_cmd_args(cmd);
			return (1);
		}
		if (*user_input != '\0')
		{
			cmd = initiate_args(user_input, main->env, cmd, main);
			add_history(user_input);
			if (cmd == NULL)
				next = main;
			else
				next = execute_function(user_input, main->env, cmd, main);
			main = next;
		}
	}
}

// echo "hello hjvb" | cat Makefile