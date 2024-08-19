/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:14:14 by macampos          #+#    #+#             */
/*   Updated: 2024/08/20 00:15:01 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child2(t_cmd *cmd, t_main *main)
{
	if (cmd->argv2[1])
	{
		if (cmd == cmd->begining)
		{
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
		else if (cmd->next == NULL)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
	}
	else
		aplly_redirections(cmd, main);
}

void	check_nobuiltins_notexecutable(int *check, t_cmd *cmd, t_main *main)
{
	int	*check2;

	check2 = check_paired(&cmd->args[0][1], main->env, main->export,
			ft_strlen(&cmd->args[0][1]));
	if (cmd->args[0][0] == '$' && check2[0] != -1)
	{
		if (get_paths(&main->env[check2[0]][find_equal(main->env[check2[0]])
				+ 1], main->env))
		{
			execve(get_paths(&main->env[check2[0]]
				[find_equal(main->env[check2[0]]) + 1], main->env),
				ft_split(&main->env[check2[0]][find_equal(main->env[check2[0]])
					+ 1], ' '), main->env);
		}
		if (check2[0] != -1)
		{
			printf("command not found: %s\n",
				&main->env[check2[0]][find_equal(main->env[check2[0]]) + 1]);
			free_every_thing(cmd, main, check);
			free(check2);
			exit(-1);
		}
	}
	free(check2);
}
