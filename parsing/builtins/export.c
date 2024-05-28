/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:24 by macampos          #+#    #+#             */
/*   Updated: 2024/05/28 18:17:26 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		free(main->env[i]);
		i++;
	}
	// free(main->env);
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

t_main	*export(t_cmd *cmd, char **envp, t_main *main)
{
	t_main	*next;
	int		i;

	i = 0;
	next = NULL;
	if (!cmd->args[1])
	{
		print_export(main);
		next = set_main4(main, main->env, main->export);
		return(next);
	}
	else if (cmd->args[2])
		return(main);
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
