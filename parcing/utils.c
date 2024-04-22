/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/04/22 00:12:49 by macampos         ###   ########.fr       */
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
