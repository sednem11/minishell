/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:24 by macampos          #+#    #+#             */
/*   Updated: 2024/04/24 16:01:54 by macampos         ###   ########.fr       */
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

int	*check_paired(char *exported, char **envp, char **envp2, int len)
{
	int *place;
	int	i;
	
	i = 0;
	place = calloc(sizeof(int), 3);
	place[0] = -1;
	place[1] = -1;
	while(envp[i] && envp2[i])
	{
		if (ft_strncmp(envp[i], exported, len) == 0)
			place[0] = i;
		if (ft_strncmp(envp2[i], exported, len) == 0)
			place[1] = i;
		i++;
	}
	while(envp[i])
	{
		if (ft_strncmp(envp[i], exported, len) == 0)
			place[0] = i;
		i++;
	}
	while(envp2[i])
	{
		if (ft_strncmp(envp2[i], exported, len) == 0)
			place[1] = i;
		i++;
	}
	return (place);
	
}

int		ft_strlen_updated(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return(i);
}

t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported)
{
	int	j;
	int	*place;
	
	place = check_paired(exported, envp, envp2, ft_strlen_updated(exported));
	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	main->env = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->env[j] = calloc(sizeof(char), 10000);
		if (j != place[0] || find_equal(exported) == -1)
			main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
		else if (j == place[0] && find_equal(exported) > 0)
			main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)	
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(exported));
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)exported, ft_strlen(exported));
	}
	j = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp2) + 2);
	while (envp2[j])
	{
		main->export[j] = calloc(sizeof(char), 10000);
		if (j != place[1])
			main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)envp2[j], ft_strlen(envp2[j]));
		else
			main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (place[1] == -1)
	{
		main->export[j] = calloc(sizeof(char), ft_strlen(exported));
		main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)exported, ft_strlen(exported));
	}
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
		if (i == 0)
			return(main);
		else
			next = set_main2(next, envp, main->export, cmd->args[1]);
	}
	return(next);
}
