/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/05/16 16:28:43 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_cmd *cmd, char **envp)
{
	(void)envp;
	if (ft_strncmp(cmd->args[1], "~", 1) == 0 || !cmd->args[1])
		chdir("/home");
	else
	{
		printf("%s\n", cmd->args[1]);
		chdir(cmd->args[1]);
	}
}