/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/09/30 17:28:26 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	int	*place;
	
	(void)envp;
	if (cmd->args[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		main->status = 1;
	}
	else if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
	{
		place = check_paired("HOME=", main->env, main->export, 5);
		if (place[0] == -1)
		{
			free(place);
			ft_putstr_fd(" Unable to find HOME\n", 2);
			main->status = 1;
		}
		else
		{
			chdir("/home");
			main->status = 0;
		}
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
