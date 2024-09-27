/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:15 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 17:40:21 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		printf("%s\n", envp[j]);
		j++;
	}
}

void	env(t_cmd *cmd, char **envp)
{
	if (!cmd->args[1])
		print_env(envp);
}
