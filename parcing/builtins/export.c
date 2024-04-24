/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:24 by macampos          #+#    #+#             */
/*   Updated: 2024/04/23 15:20:28 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_main	*free_env(t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		free(main->env[i]);
		i++;
	}
	free(main->env);
	return(main);
}

int	find_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if(arg[i] == '=')
			return(i);
		i++;
	}
	return(-1);
}

t_main	*set_main2(t_main *main, char **envp, char *exported)
{
	int	j;
	
	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	main->env = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(envp[j]));
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
		j++;
	}
	if (find_equal(exported) > 0)
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(exported));
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)exported, ft_strlen(exported));
	}
	j = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->export[j] = calloc(sizeof(char), ft_strlen(envp[j]));
		main->export[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
		j++;
	}
	main->export[j] = calloc(sizeof(char), ft_strlen(exported));
	main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)exported, ft_strlen(exported));
	return(main);
}

t_main	*export(t_cmd *cmd, char **envp, t_main *main)
{
	t_main	*next;
	int		i;

	i = 0;
	next = NULL;
	if (!cmd->args[1])
	{
		print_env(main->export);
		return(main);
	}
	else 
	{
		i = find_equal(cmd->args[1]);
		if (i >= 0)
		{
			if (i > 0)
				next = set_main2(next, envp, cmd->args[1]);
			else
				return(main);
		}
		else
			next = set_main2(next, envp, cmd->args[1]);
	}
	return(next);
}
