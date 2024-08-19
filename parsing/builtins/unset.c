/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:31 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 15:02:04 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_main	*unset(t_cmd *cmd, t_main *main, char **envp)
{
	t_main	*next;

	if (!cmd->args[1])
	{
		main->status = 0;
		return (main);
	}
	else
		next = set_main3(main, envp, main->export, cmd->args[1]);
	return (next);
}
