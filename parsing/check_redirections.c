/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:29 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 12:04:38 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirections4(t_cmd *cmd, char *arg, int j, int i)
{
	if (ft_strncmp(arg, ">>", 2) == 0)
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 4;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
}
void	check_redirections3(t_cmd *cmd, char *arg, int j, int i)
{
	if (ft_strncmp(arg, "<<", 2) == 0)
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 3;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else
		check_redirections4(cmd, arg, j, i);
}

void	check_redirections2(t_cmd *cmd, char *arg, int j, int i)
{
	if (ft_strncmp(arg, "<", 1) == 0 && arg[1] != '<')
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 2;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else
		check_redirections3(cmd, arg, j, i);
}

void	check_redirections(t_cmd *cmd, char *arg, int j)
{
	int	i;

	i = 0;
	if (ft_strncmp(arg, ">", 1) == 0 && arg[1] != '>')
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 1;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else
		check_redirections2(cmd, arg, j, i);
}