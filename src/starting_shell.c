/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/04/18 01:14:42 by macampos         ###   ########.fr       */
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
	cmd = cmd->next;
	dup2(fd[0], STDIN_FILENO);
	dup2(STDOUT_FILENO, fd[1]);
	close(fd[1]);
	close(fd[0]);
	execve(cmd->path, cmd->args, envp);
}

void	child_process(char *user_input, char **envp, int fd[2], t_cmd *cmd)
{
	if (pars_args(ft_split(user_input, ' ')) != -1)
	{
		if (cmd->next->next->args == NULL)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		// else
		// {
		// 	int		fd2[2];
		// 	pid_t 	id;

		// 	if (pipe(fd2) == -1)
		// 		return;
		// 	id = fork();
		// 	if (id == 0)
		// 		child_process(user_input, envp, fd2, cmd);
		// 	waitpid(0, NULL, 0);
		// }
	}
	if (check_builtins(cmd, envp) == 1)
		execve(cmd->path , cmd->args, envp);
}

int	execute_function(char *user_input, char **envp, t_cmd *cmd)
{
	pid_t	id;
	int		fd[2];

	if (envp == NULL)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	id = fork();
	if (id == -1)
		return(-1);
	if (id == 0)
		child_process(user_input, envp, fd, cmd);
	waitpid(0, NULL, 0);
	if (pars_args(ft_split(user_input, ' ')) != -1)
		parent_process(user_input, envp, fd, cmd);
	return(1);
}
