/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/04/18 19:21:21 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_paths(char **paths, char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_paths(char *argv, char **envp)
{
	int		i;
	char	**paths;
	char	*part_path;
	char	*path;
	char	**cmd;

	if (!envp)
		return (NULL);
	cmd = ft_split(argv, ' ');
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd[0]);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_paths(paths, cmd);
	return (NULL);
}

void	parent_process(char *user_input, char **envp, int fd[2], t_cmd *cmd)
{
	(void)user_input;
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execve(cmd->path, cmd->args, envp);
}

void	child_process(char *user_input, char **envp, int fd[2], t_cmd *cmd)
{
	if (pars_args(ft_split(user_input, ' ')) != -1)
	{
		if (cmd == cmd->begining)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (cmd->next == NULL)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
	}
	if (check_builtins(cmd, envp) == 1)
		execve(cmd->path , cmd->args, envp);
	exit(0);
}

int	execute_function(char *user_input, char **envp, t_cmd *cmd)
{
	pid_t	id;
	int		fd[2];
	// int		pip[2];

	if (envp == NULL)
		return (-1);
	while(cmd)
	{
		if (cmd->numb % 2 == 0)
		{
			if (pipe(fd) == -1)
				return (-1);
		}
		id = fork();
		if (id == -1)
			return(-1);
		if (id == 0)
			child_process(user_input, envp, fd, cmd);
		close(fd[1]);
		waitpid(id, NULL, 0);
		cmd = cmd->next;
	}
	return(1);
}
	