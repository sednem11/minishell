/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/06/19 16:38:23 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	free_cmd(t_cmd *cmd)
{
		free_cmd_args(cmd);
}

void	exitt(t_cmd *cmd, char **envp, t_main *main)
{
	(void) envp;
	(void) main;
	int		last;
	
	last = ft_atoi(cmd->args[1]);
	if (!cmd->args[1] || ft_strncmp(ft_itoa(ft_atoi(cmd->args[1])), cmd->args[1], ft_strlen(cmd->args[1])) == 0)
	{
		free_env_and_export(main);
		free(main);
		if (!cmd->args[1])
		{
			free_cmd(cmd);
			exit(0);
		}
		if (!cmd->args[2])
		{
			free_cmd(cmd);
			exit(last);
		}
	}
	if (ft_strncmp(ft_itoa(ft_atoi(cmd->args[1])), cmd->args[1], ft_strlen(cmd->args[1])) != 0)
	{
		free_env_and_export(main);
		free(main);
		free_cmd(cmd);
		exit(0);
	}
	return ;
}
