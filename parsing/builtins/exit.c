/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/08/20 00:41:15 by macampos         ###   ########.fr       */
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

void	exitt2(t_cmd *cmd, char *truearg, t_main *main)
{
	int	status;

	status = 0;
	free(truearg);
	if (!ft_atoi(cmd->args[1]) && !cmd->args[2])
	{
		status = 2;
		write(2, " numeric argument required\n", 28);
	}
	else if (cmd->args[1])
	{
		status = 100;
		write(2, " numeric argument required\n", 28);
	}
	free_env_and_export(main);
	free(main);
	free_cmd(cmd);
	exit(status);
}

void	exitt3(t_cmd *cmd, char *truearg, t_main *main)
{
	int	last;

	if (cmd->args[1])
		free(truearg);
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

t_main	*exitt(t_cmd *cmd, char **envp, t_main *main)
{
	char	*truearg;

	(void)envp;
	(void)main;
	if (cmd->args[1])
		truearg = ft_itoa(ft_atoi(cmd->args[1]));
	if (!cmd->args[1] || ft_strncmp(truearg, cmd->args[1],
			ft_strlen(cmd->args[1])) == 0)
	{
		if (cmd->args[1] && cmd->args[2] && ft_strncmp(truearg, cmd->args[1],
				ft_strlen(cmd->args[1])) == 0)
		{
			main->status = 1;
			write(2, " to many arguments\n", 20);
			free(truearg);
			return (main);
		}
		exitt3(cmd, truearg, main);
	}
	else if (ft_strncmp(truearg, cmd->args[1], ft_strlen(cmd->args[1])) != 0)
		exitt2(cmd, truearg, main);
	return (main);
}
