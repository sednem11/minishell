/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/05/03 16:04:14 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_comands2(t_cmd *cmd, int i)
{
    cmd->numb = i;
	if (pipe(cmd->fd) == -1)
		return;
}

t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported)
{
	int	j;
	int	*place;
	
	place = check_paired(exported, envp, envp2, ft_strlen_updated(exported));
	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	main->env = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		main->env[j] = calloc(sizeof(char), 10000);
		if (j != place[0] || find_equal(exported) == -1)
			main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
		else if (j == place[0] && find_equal(exported) > 0)
			main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)	
	{
		main->env[j] = calloc(sizeof(char), ft_strlen(exported));
		main->env[j] = (char *)ft_memcpy((void *)main->env[j], (void *)exported, ft_strlen(exported));
	}
	j = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp2) + 2);
	while (envp2[j])
	{
		main->export[j] = calloc(sizeof(char), 10000);
		if (j != place[1])
			main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)envp2[j], ft_strlen(envp2[j]));
		else
			main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (place[1] == -1)
	{
		main->export[j] = calloc(sizeof(char), ft_strlen(exported));
		main->export[j] = (char *)ft_memcpy((void *)main->export[j], (void *)exported, ft_strlen(exported));
	}
	return(main);
}

t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported)
{
	int	j;
	int i;
	int	*place;
	
	i = 0;
	place = check_paired(exported, envp, envp2, ft_strlen_updated(exported));
	j = 0;
	main = calloc(sizeof(t_main), sizeof(t_main));
	main->env = calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		if (j != place[0])
		{
			main->env[i] = calloc(sizeof(char), 10000);
			main->env[i] = (char *)ft_memcpy((void *)main->env[j], (void *)envp[j], ft_strlen(envp[j]));
			i++;
		}
		j++;
	}
	j = 0;
	i = 0;
	main->export = calloc(sizeof(char *), matrixlen(envp2) + 1);
	while (envp2[j])
	{
		if (j != place[1])
		{
			main->export[i] = calloc(sizeof(char), 10000);
			main->export[i] = (char *)ft_memcpy((void *)main->export[j], (void *)envp2[j], ft_strlen(envp2[j]));
			i++;
		}
		j++;
	}
	return(main);
}
