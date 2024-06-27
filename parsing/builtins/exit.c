/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 16:16:24 by macampos         ###   ########.fr       */
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

t_main	*exitt(t_cmd *cmd, char **envp, t_main *main)
{
	int	last;

	(void)envp;
	(void)main;
	if (!cmd->args[1] || ft_strncmp(ft_itoa(ft_atoi(cmd->args[1])),
			cmd->args[1], ft_strlen(cmd->args[1])) == 0)
	{
		if (cmd->args[2] && ft_strncmp(ft_itoa(ft_atoi(cmd->args[1])),
				cmd->args[1], ft_strlen(cmd->args[1])) == 0)
		{
			main->status = 1;
			write(2, " to many arguments\n", 20);
			return (main);
		}
		free_env_and_export(main);
		free(main);
		if (!cmd->args[1])
		{
			free_cmd(cmd);
			exit(0);
		}
		if (!cmd->args[2])
		{
			last = ft_atoi(cmd->args[1]);
			free_cmd(cmd);
			exit(last);
		}
	}
	else if (ft_strncmp(ft_itoa(ft_atoi(cmd->args[1])), cmd->args[1],
			ft_strlen(cmd->args[1])) != 0)
	{
		if (!ft_atoi(cmd->args[1]) && !cmd->args[2])
		{
			main->status = 2;
			write(2, " numeric argument required\n", 28);
		}
		else if (cmd->args[1])
		{
			main->status = 100;
			write(2, " numeric argument required\n", 28);
		}
		free_env_and_export(main);
		free(main);
		free_cmd(cmd);
		exit(main->status);
	}
	return (main);
}
