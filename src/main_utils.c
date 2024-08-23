/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:45:13 by macampos          #+#    #+#             */
/*   Updated: 2024/08/23 16:32:17 by macampos         ###   ########.fr       */
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

int	check_cmds(t_main *main)
{
	int	i;

	i = 0;
	while (main->cmd[i])
	{
		if (ft_strncmp(main->cmd[i]->args[0], "cat", 3) != 0
			|| main->cmd[i]->args[1])
			return (1);
		i++;
	}
	return (0);
}

void	closepipes_helper(t_cmd *cmd)
{
	if ((cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
		|| (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset", 5) == 0))
		closepipes(cmd);
}
