/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:17:38 by macampos          #+#    #+#             */
/*   Updated: 2024/08/20 01:41:17 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_export_help2(t_main *main, int i, int n, int z)
{
	if (ft_strncmp(main->export[i], main -> export[n], z) < 0)
		n = i;
	else if (ft_strncmp(main->export[i], main -> export[n], z) == 0
		&& ft_strlen_upd(main->export[i])
		!= ft_strlen_upd(main->export[n]))
		n = i;
	return (n);
}

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
