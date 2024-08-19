/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:45:13 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 22:54:59 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	matrixlen(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		j++;
	}
	return (j);
}

t_main	*set_main_helper(t_main *main, char **envp)
{
	int	j;

	j = 0;
	main->env = ft_calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		main->env[j] = ft_strdup(envp[j]);
		j++;
	}
	j = 0;
	main->export = ft_calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		main->export[j] = ft_strdup(envp[j]);
		j++;
	}
	return (main);
}

t_main	*set_main(t_main *main, char **envp)
{
	main = ft_calloc(sizeof(t_main), sizeof(t_main));
	if (envp[0] == NULL)
	{
		main->env = ft_calloc(sizeof(char *), 4);
		main->env[0] = ft_strdup("PWD=/home/macampos/minishell");
		main->env[1] = ft_strdup("SHLVL=1");
		main->env[2] = ft_strdup("_=/usr/bin/env");
		main->export = ft_calloc(sizeof(char *), 4);
		main->export[0] = ft_strdup("PWD=/home/macampos/minishell");
		main->export[1] = ft_strdup("SHLVL=1");
		main->export[2] = ft_strdup("_=/usr/bin/env");
		return (main);
	}
	main = set_main_helper(main, envp);
	return (main);
}
