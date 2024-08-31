/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:14:14 by macampos          #+#    #+#             */
/*   Updated: 2024/08/31 20:33:00 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_helper(t_cmd *cmd, t_main *main, int *check)
{
	int	status;

	status = 127;
	free_every_thing(cmd, main, check);
	exit(status);
}

void	not_builtin_helper(int *check, char **envp, t_cmd *cmd, t_main *main)
{
	int	status;

	if (cmd->realarg[0][0] == '/')
		execve(cmd->realarg[0], cmd->realarg, envp);
	if (!cmd->path)
		cmd->path = get_paths(cmd->realarg[0], main->env);
	if (cmd->path)
		execve(cmd->path, cmd->realarg, envp);
	if (ft_strncmp(cmd->args[0], "./", 2) == 0)
	{
		write(2, " No such file or directory\n", 28);
		status = 126;
		free_every_thing(cmd, main, check);
		exit(status);
	}
	if (ft_strncmp(cmd->args[0], "/", 1) == 0)
		write(2, " No such file or directory\n", 28);
	else if (cmd->args[0][0] == '$' && cmd->args[1]
		&& check_paired(cmd->args[0], main->env, main->export,
			ft_strlen(cmd->args[0]) - 1)[0] == -1)
		execve(cmd->path, &cmd->args[1], envp);
	else
		write(2, "command not found\n", 19);
	exit_helper(cmd, main, check);
}

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

void	free_both(t_main *main)
{
	free(main->cmd);
	main->cmd = NULL;
	free(main->pid);
	main->pid = NULL;
}
