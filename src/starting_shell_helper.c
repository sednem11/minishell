/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:14:14 by macampos          #+#    #+#             */
/*   Updated: 2024/10/08 15:49:20 by macampos         ###   ########.fr       */
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
	int		status;
	char	**a;
	char	*path;

	a = NULL;
	if (!cmd->path)
		cmd->path = get_paths(cmd->realarg[0], main->env);
	if (cmd->realarg[0] && cmd->realarg[0][0] == '/')
	{
		path = get_paths(cmd->realarg[0], main->env);
		if (path == NULL)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			free_every_thing(cmd, main, check);
			free(path);
			exit(127);
		}
		free(path);
		execve(cmd->realarg[0], cmd->realarg, envp);
	}
	if (cmd->path && check_builtins3(cmd, main->env, main) == 1)
	{
		if (arg_len(cmd->args) == 1 || (get_paths(cmd->realarg[1],
					main->env) == NULL && cmd->redirectionoverall == 0))
			execve(cmd->path, cmd->args, envp);
		execve(cmd->path, cmd->realarg, envp);
	}
	if (ft_strncmp(cmd->args[0], "./", 2) == 0)
	{
		execve(cmd->args[0], a, envp);
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
	free(check);
	check = NULL;
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
		else if (cmd->next == NULL)
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
