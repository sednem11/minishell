/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/06/22 12:49:34 by macampos         ###   ########.fr       */
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
		if (j != place[0] || find_equal(exported) == -1)
			mainn->env[j] = envp[j];
		else if (j == place[0] && find_equal(exported) > 0)
			mainn->env[j] = ft_strdup(exported);
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)	
		mainn->env[j] = ft_strdup(exported);
	j = 0;
	mainn->export = calloc(sizeof(char *), matrixlen(envp2) + 2);
	while (envp2[j])
	{
		if (j != place[1])
			mainn->export[j] = envp2[j];
		else
			mainn->export[j] = ft_strdup(exported);
		j++;
	}
	if (place[1] == -1)
		mainn->export[j] = ft_strdup(exported);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return(mainn);
}

t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported)
{
	int	j;
	int i;
	int	*place;
	t_main	*mainn;
	
	i = 0;
	j = 0;
	place = check_paired(exported, envp, envp2, ft_strlen_updated(exported));
	mainn = calloc(sizeof(t_main), sizeof(t_main));
	mainn->env = calloc(sizeof(char *), matrixlen(envp) + 1);
	while (envp[j])
	{
		if (j != place[0])
		{
			mainn->env[i] = envp[j];
			i++;
		}
		j++;
	}
	j = 0;
	i = 0;
	mainn->export = calloc(sizeof(char *), matrixlen(envp2) + 1);
	while (envp2[j])
	{
		if (j != place[1])
		{
			mainn->export[i] = envp2[j];
			i++;
		}
		j++;
	}
	if (place[0] != -1)
		free(main->env[place[0]]);
	if (place[1] != -1)
		free(main->export[place[1]]);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return(mainn);
}
