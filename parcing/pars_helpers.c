/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/04/19 01:08:31 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_comands2(t_cmd *cmd, int i)
{
    cmd->numb = i;
	if (pipe(cmd->fd) == -1)
		return;
}
