/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:14:14 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 15:05:46 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child2help(t_cmd *cmd, t_main *main)
{
	if (cmd->next == NULL)
	{
		if (cmd->redirectionoverall == 2)
			aplly_redirections(cmd, main);
		dup2(cmd->fd[0], STDIN_FILENO);
		if (cmd->redirectionoverall != 2)
			aplly_redirections(cmd, main);
		closepipes(cmd);
	}
	else if (cmd->next && cmd != cmd->begining)
	{
		if (cmd->redirectionoverall == 2)
			aplly_redirections(cmd, main);
		dup2(cmd->fd[0], STDIN_FILENO);
		dup2(cmd->next->fd[1], STDOUT_FILENO);
		if (cmd->redirectionoverall != 2)
			aplly_redirections(cmd, main);
		closepipes(cmd);
		close(cmd->next->fd[1]);
	}
}

void	child2(t_cmd *cmd, t_main *main)
{
	if (cmd->argv2[1])
	{
		if (cmd == cmd->begining)
		{
			if (cmd->redirectionoverall == 2)
				aplly_redirections(cmd, main);
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			if (cmd->redirectionoverall != 2)
				aplly_redirections(cmd, main);
			closepipes(cmd);
		}
		else
			child2help(cmd, main);
	}
	else
		aplly_redirections(cmd, main);
	closepipes(cmd);
}

void	free_both(t_main *main)
{
	free(main->cmd);
	main->cmd = NULL;
	free(main->pid);
	main->pid = NULL;
}
