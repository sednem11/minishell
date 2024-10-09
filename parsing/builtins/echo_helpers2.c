/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:20:21 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 15:35:04 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_redirections3(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->redirectionoverall == 1 && check_backward_redirection(cmd) == 0)
	{
		while (cmd->realarg[i])
		{
			printf("%s", cmd->realarg[i]);
			if (cmd->realarg[i + 1])
				printf("%s", " ");
			i++;
		}
	}
	printf("\n");
}

void	free_value(char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

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

int	check_dolar(char *user_input)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (user_input[i])
	{
		if (user_input[i] == '\'')
			flag *= -1;
		if (user_input[i] == '$' && flag == 1)
			return (2);
		i++;
	}
	return (1);
}

int	check_backward_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 3 || cmd->redirection[i] == 2)
			return (1);
		i++;
	}
	return (0);
}
