/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/08/20 16:34:39 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	*main2_help(int *place, t_main *mainn, char **envp2, char *exported)
{
	int	j;

	j = 0;
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
	free(place);
	return (mainn);
}

t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported)
{
	int		j;
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, ft_strlen_upd(exported));
	j = 0;
	mainn = ft_calloc(sizeof(t_main), sizeof(t_main));
	mainn->env = ft_calloc(sizeof(char *), matrixlen(envp) + 2);
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
	mainn->export = ft_calloc(sizeof(char *), matrixlen(envp2) + 2);
	mainn = main2_help(place, mainn, envp2, exported);
	free(main->env);
	free(main->export);
	free(main);
	return (mainn);
}

t_main	*main3_helper(t_main *mainn, char **envp, int *place)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[j])
	{
		if (j != place[0])
		{
			mainn->env[i] = envp[j];
			i++;
		}
		j++;
	}
	return (mainn);
}

t_main	*main3_helper2(t_main *mainn, char **envp2, int *place)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp2[j])
	{
		if (j != place[1])
		{
			mainn->export[i] = envp2[j];
			i++;
		}
		j++;
	}
	return (mainn);
}

t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported)
{
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, ft_strlen_upd(exported));
	mainn = ft_calloc(sizeof(t_main), sizeof(t_main));
	mainn->env = ft_calloc(sizeof(char *), matrixlen(envp) + 1);
	mainn->export = ft_calloc(sizeof(char *), matrixlen(envp2) + 1);
	mainn = main3_helper(mainn, envp, place);
	mainn = main3_helper2(mainn, envp2, place);
	if (place[0] != -1)
		free(main->env[place[0]]);
	if (place[1] != -1)
		free(main->export[place[1]]);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return (mainn);
}
