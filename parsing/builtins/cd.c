/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 17:36:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	(void)envp;
	if (cmd->args[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		main->status = 1;
	}
	else if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
	{
		chdir("/home");
		main->status = 0;
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			main->status = 1;
			ft_putstr_fd(" No such file or directory\n", 2);
		}
		else
			main->status = 0;
	}
}
