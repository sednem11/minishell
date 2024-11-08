/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_helper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:03:47 by macampos          #+#    #+#             */
/*   Updated: 2024/11/08 23:39:52 by macampos         ###   ########.fr       */
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

void	not_builtin_helper2(t_cmd *cmd, t_main *main, char **envp, int *check)
{
	int	status;

	if (cmd->path && check_builtins3(cmd, main->env, main) == 1)
	{
		if (cmd->redirectionoverall == 0 && (arg_len(cmd->args) == 1
				|| get_paths(cmd->realarg[1], main->env) == NULL))
			execve(cmd->path, cmd->args, envp);
		execve(cmd->path, cmd->realarg, envp);
	}
	if (ft_strncmp(cmd->args[0], "./", 2) == 0)
	{
		execve(cmd->args[0], cmd->args, envp);
		if (access(cmd->args[0], F_OK) == -1)
		{
			status = 127;
			ft_putstr_fd(" No such file or directory\n", 2);
		}
		else if (get_paths(&cmd->args[0][1], main->env) == NULL)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			status = 126;
		}
		free_every_thing(cmd, main, check);
		exit(status);
	}
}

void	not_builtin_helper3(t_main *main, t_cmd *cmd, char **envp, int *check)
{
	if (cmd->realarg[0] && cmd->realarg[0][0] == '$')
	{
		check = check_paired(&cmd->realarg[0][1], main->env, main->export,
				ft_strlen_updated(&cmd->realarg[0][1]));
	}
	if (cmd->realarg[0] && cmd->realarg[0][0] == '/')
		ft_putstr_fd(" No such file or directory\n", 2);
	else if (cmd->args[0][0] == '$' && cmd->args[1]
		&& check_paired(cmd->args[0], main->env, main->export,
			ft_strlen(cmd->args[0]) - 1)[0] == -1)
		execve(cmd->path, &cmd->args[1], envp);
	else if (cmd->realarg[0] && cmd->realarg[0][0] == '$' && check[0] != -1
		&& cmd->realarg[0][1])
	{
		ft_putstr_fd(" Is a directory\n", 2);
		free_every_thing(cmd, main, check);
		exit(126);
	}
	else if (cmd->realarg[0])
		ft_putstr_fd(" command not found\n", 2);
	exit_helper(cmd, main, check);
}

void	not_builtin_helper(int *check, char **envp, t_cmd *cmd, t_main *main)
{
	if (!cmd->path)
		cmd->path = get_paths(cmd->realarg[0], main->env);
	if (cmd->realarg[0] && cmd->realarg[0][0] == '/')
	{
		execve(cmd->realarg[0], cmd->realarg, envp);
		ft_putstr_fd(" No such file or directory\n", 2);
		free_every_thing(cmd, main, check);
		exit(127);
	}
	not_builtin_helper2(cmd, main, envp, check);
	free(check);
	check = NULL;
	not_builtin_helper3(main, cmd, envp, check);
}
