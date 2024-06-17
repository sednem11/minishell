/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/06/17 16:13:46 by macampos         ###   ########.fr       */
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

void	free_every_cmd(t_cmd *cmd)
{
	while(cmd)
	{
		free_args(cmd);
		free(cmd->path);
		cmd = cmd->next;
	}
}

void	free_every_main(t_main *main)
{
	while(main)
	{
		free_env(main);
		main = main->next;
	}

}

void	exitt(t_cmd *cmd, char **envp, t_main *main)
{
	(void) envp;
	(void) main;
	// free_every_main(main->beginning);
	// free(main);
	// free_every_cmd(cmd);
	// free(cmd);
	exit(ft_atoi(cmd->args[1]));
	return ;
}