/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:17:38 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 17:17:58 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_and_export(t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		free(main->env[i]);
		i++;
	}
	free(main->env);
	i = 0;
	while (main->export[i])
	{
		free(main->export[i]);
		i++;
	}
	free(main->export);
}
