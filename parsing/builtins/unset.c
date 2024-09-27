/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:31 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 17:43:38 by macampos         ###   ########.fr       */
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
	next->status = 0;
	return (next);
}
