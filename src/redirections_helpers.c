/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:48:05 by macampos          #+#    #+#             */
/*   Updated: 2024/09/03 13:02:06 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	alloc_heredoc(t_cmd *cmd, char *alocated)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), matrixlen(cmd->realarg) + 2);
	while (cmd->realarg[i])
	{
		new[i] = cmd->realarg[i];
		i++;
	}
	new[i] = ft_strdup(alocated);
	free(cmd->realarg);
	cmd->realarg = new;
}

int	check_last_redirection2(t_cmd *cmd, int i)
{
	i += 1;
	if (i < count_redirections(cmd->args))
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] && (cmd->redirection[i] == 2
					|| cmd->redirection[i] == 3))
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_last_redirection(t_cmd *cmd, int i)
{
	int	j;

	j = i + 1;
	if (j < count_redirections(cmd->args))
	{
		while (j < count_redirections(cmd->args))
		{
			if (cmd->redirection[j] == 1 || cmd->redirection[j] == 4)
				return (-1);
			j++;
		}
	}
	return (1);
}

int	last_reversed(t_cmd *cmd, int flag)
{
	int	i;
	int	j;

	j = -2;
	i = 0;
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 3 || cmd->redirection[i] == 2)
			{
				j = i;
				if (cmd->redirection[i] == 3 && i > flag)
					return (j);
			}
			i++;
		}
	}
	return (j);
}

void	aplly_redirections(t_cmd *cmd, t_main *main)
{
	int	file;
	int	i;

	i = 0;
	file = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 2)
			redirection2(cmd, i, file, main);
		else if (cmd->redirection[i] == 3)
			redirection3(cmd, i, file);
		i++;
	}
	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 1)
			redirection_1(cmd, file, i, main);
		else if (cmd->redirection[i] == 4)
			redirection4(cmd, i, file, main);
		i++;
	}
}
