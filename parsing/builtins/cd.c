/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/06/25 10:55:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	(void)envp;
	if (cmd->args[2])
	{
		printf("to many arguments\n");
		main->status = 1;
	}
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
		chdir("/home");
	else
		chdir(cmd->args[1]);
}