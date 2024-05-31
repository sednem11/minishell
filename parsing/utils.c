/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/05/31 17:34:25 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0], "export", 6) == 0
		|| ft_strncmp(cmd->args[0], "pwd", 3) == 0 || ft_strncmp(cmd->args[0], "env", 3) == 0
		|| ft_strncmp(cmd->args[0], "exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return(0);
    else
		return(1);
}

int	check_last(t_main *main)
{
	int	i;
	int	n;
	int	z;

	n = 0;
	i = 0;
	while (main->export[i])
	{
		if (ft_strlen_updated(main->export[i]) > ft_strlen_updated(main->export[n]))
			z = ft_strlen_updated(main->export[n]);
		else
			z = ft_strlen_updated(main->export[i]);
		if (ft_strncmp(main->export[i], main->export[n], z) > 0)
			n = i;
		i++;
	}
	return(n);
}

void	print_export(t_main *main)
{
	int	i;
	int	n;
	int	z;
	int	a;
	int	c;
	
	a = 0;
	c = 0;
	while (matrixlen(main->export) > a + 1)
	{
		n = check_last(main);
		i = 0;
		while (main->export[i])
		{
			if (ft_strlen_updated(main->export[i]) > ft_strlen_updated(main->export[n]))
				z = ft_strlen_updated(main->export[n]);
			else
				z = ft_strlen_updated(main->export[i]);
			if (ft_strncmp(main->export[i], main->export[n], z) < 0 && a == 0)
				n = i;
			else if (a > 0 && ft_strncmp(main->export[i], main->export[c], ft_strlen_updated(main->export[i])) > 0)
			{
				if (ft_strncmp(main->export[i], main->export[n], z) < 0)
					n = i;
				else if(ft_strncmp(main->export[i], main->export[n], z) == 0
					&& ft_strlen_updated(main->export[i]) != ft_strlen_updated(main->export[n]))
					n = i;
			}			
			i++;
		}
		printf("declare -x %s\n", main->export[n]);
		c = n;
		a++;
	}
}
