/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:05:09 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 22:05:15 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_equal(char *value)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	print_dolar(t_main *main, char *arg)
{
	int		i;
	char	**value;

	value = ft_split(arg, ' ');
	i = 1;
	if (!arg[0] || arg[0] == ' ')
	{
		printf("$");
		return ;
	}
	if (arg[0] == '?')
	{
		printf("%i", main->status);
		while (arg[i] && arg[i] != ' ')
		{
			printf("%c", arg[i]);
			i++;
		}
	}
	else
	{
		i = 0;
		while (main->env[i])
		{
			if (ft_strncmp(value[0], main->env[i], ft_strlen(value[0])) == 0
				&& main->env[i][ft_strlen(value[0])] == '='
				&& check_equal(value[0]) == -1)
				printf("%s", &main->env[i][ft_strlen(value[0]) + 1]);
			i++;
		}
	}
}
