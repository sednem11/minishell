/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:54 by macampos         ###   ########.fr       */
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

typedef struct s_stupid
{
	int		file;
	int		i;
	char	*path;
	char	**cmd;
}		t_stupid;

void	child_process(char **argv, char **envp, int *fd, t_cmd *cmd)
{
	struct s_stupid	stupid;

	if (pars_args(argv) != -1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (check_builtins(argv, stupid.path, envp) == 1)
		execve(cmd->path , cmd->args, envp);
}

void	parent_process(char **argv, char **envp, int *fd, int i)
{
	char	*path;

	path = get_paths(argv[i + 1], envp);
	execve (path, &argv[i + 1], envp);
	close(fd[1]);
}


int	execute_function(char **argv, char **envp, t_cmd *cmd)
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
		child_process(argv, envp, fd, cmd);
	waitpid(0, NULL, 0);
	if (pars_args(argv) != -1)
		parent_process(argv, envp, fd, pars_args(argv));
	return(1);
}
