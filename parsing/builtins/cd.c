/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/06/26 10:42:22 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	(void)envp;
	if (cmd->args[2])
	{
		write(2, " to many arguments\n", 20);
		main->status = 1;
	}
	else if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
		chdir("/home");
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			main->status = 1;
			write(2, " no such file or directory\n", 28);
		}
	}
}