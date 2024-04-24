/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/04/23 18:10:49 by macampos         ###   ########.fr       */
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

void	closepipes(t_cmd *cmd)
{
	if (cmd->fd[1] != 1 && cmd->fd[1] != 0)
		close(cmd->fd[1]);
	if (cmd->fd[0] != 1 && cmd->fd[0] != 0)
		close(cmd->fd[0]);
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	if (pars_args(ft_split(user_input, ' ')) != -1)
	{
		if (cmd == cmd->begining)
		{
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next == NULL)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			closepipes(cmd);
		}
	}
	main = check_builtins(cmd, envp, main);
	if (check_builtins2(cmd, envp, main) == 1)
		execve(cmd->path , cmd->args, envp);
	return ;
}



t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	pid_t	id;
	t_main	*next;

	next = NULL;
	while(cmd)
	{
		if (pars_args(ft_split(user_input, ' ')) == -1 
			&& ft_strncmp(cmd->args[0], "export", 6) == 0)
		{
			next = export(cmd, envp, main);
			return(next);
		}
		id = fork();
		if (id == -1)
			return(main);
		if (id == 0 )
			child_process(user_input, envp, cmd, main);
		closepipes(cmd);
		cmd = cmd->next;
	}
	while (waitpid(-1, NULL, 0) != -1);
	return(main);
}
	