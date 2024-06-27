/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:24 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 11:12:01 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_and_export(t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		free(main->env[i]);
		i++;
	}
	free(main->env);
	i = 0;
	while(main->export[i])
	{
		free(main->export[i]);
		i++;
	}
	free(main->export);
	
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
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return(i);
		i++;
	}
	return(i);
}

int		check_invalid(char *arg)
{
	int	i;
	
	i = 0;
	while(arg[i] && arg[i] != '=')
	{
		if ((arg[i] < 48 || arg[i] > 57) && (arg[i] < 65
			|| arg[i] > 90) && (arg[i] < 97 || arg[i] > 122))
			return(i);
		i++;
	}
	return(-1);
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
		return(main);
	}
	else if (cmd->args[2] && cmd->redirection == 0)
		return(main);
	else if (check_invalid(cmd->args[1]) != -1 || cmd->args[1][0] == '='
		|| (cmd->args[1][0] > 47 && cmd->args[1][0] < 58))
	{
		write(2, " not a valid identifier", 24);
		main->status = 1;
		return(main);
	}
	else if (check_invalid(cmd->args[1]) == -1)
		next = set_main2(main, envp, main->export, cmd->args[1]);
	return(next);
}
