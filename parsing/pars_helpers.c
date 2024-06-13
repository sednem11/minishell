/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/06/11 17:25:53 by macampos         ###   ########.fr       */
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
	t_main *mainn;
	
	place = check_paired(exported, envp, envp2, ft_strlen_updated(exported));
	j = 0;
	mainn = calloc(sizeof(t_main), sizeof(t_main));
	mainn->env = calloc(sizeof(char *), matrixlen(envp) + 2);
	while (envp[j])
	{
		mainn->env[j] = calloc(sizeof(char), 10000);
		if (j != place[0] || find_equal(exported) == -1)
			mainn->env[j] = (char *)ft_memcpy((void *)mainn->env[j], (void *)envp[j], ft_strlen(envp[j]));
		else if (j == place[0] && find_equal(exported) > 0)
			mainn->env[j] = (char *)ft_memcpy((void *)mainn->env[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)	
	{
		mainn->env[j] = calloc(sizeof(char), ft_strlen(exported) + 1);
		mainn->env[j] = (char *)ft_memcpy((void *)mainn->env[j], (void *)exported, ft_strlen(exported));
	}
	j = 0;
	mainn->export = calloc(sizeof(char *), matrixlen(envp2) + 2);
	while (envp2[j])
	{
		mainn->export[j] = calloc(sizeof(char), 10000);
		if (j != place[1])
			mainn->export[j] = (char *)ft_memcpy((void *)mainn->export[j], (void *)envp2[j], ft_strlen(envp2[j]));
		else
			mainn->export[j] = (char *)ft_memcpy((void *)mainn->export[j], (void *)exported, ft_strlen(exported));
		j++;
	}
	if (place[1] == -1)
	{
		mainn->export[j] = calloc(sizeof(char), ft_strlen(exported) + 1);
		mainn->export[j] = (char *)ft_memcpy((void *)mainn->export[j], (void *)exported, ft_strlen(exported));
	}
	mainn->beginning = main;
	return(mainn);
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
			main->env[i] = (char *)ft_memcpy((void *)main->env[i], (void *)envp[j], ft_strlen(envp[j]));
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
			main->export[i] = (char *)ft_memcpy((void *)main->export[i], (void *)envp2[j], ft_strlen(envp2[j]));
			i++;
		}
		j++;
	}
	return(main);
}
