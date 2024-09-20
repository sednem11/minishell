/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:01:16 by macampos          #+#    #+#             */
/*   Updated: 2024/09/10 12:13:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection3_help(t_cmd *cmd, int i, int file, char *input,
		t_main *main)
{
	while (ft_strncmp(input, cmd->args[cmd->redirectionpos[i] + 1],
			ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) != 0))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal_main3(main, cmd, file);
		if (ft_strncmp(input, cmd->args[cmd->redirectionpos[i] + 1],
				ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) != 0))
		{
			write(file, input, ft_strlen(input));
			write(file, "\n", 1);
		}
		input = readline("heredoc> ");
		check_signal_received(main, cmd, file);
	}
}

void	free_paths(char **paths, char **cmd)
{
	int	i;

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
	t_path	path;
	char	**cmd;

	path.i = 0;
	if (!envp || !argv || !*argv)
		return (NULL);
	cmd = ft_split(argv, ' ');
	while (ft_strnstr(envp[path.i], "PATH=", 5) == 0)
		path.i++;
	path.paths = ft_split(envp[path.i] + 5, ':');
	path.i = -1;
	while (path.paths[++path.i])
	{
		path.part_path = ft_strjoin(path.paths[path.i], "/");
		path.path = ft_strjoin(path.part_path, cmd[0]);
		free(path.part_path);
		if (access(path.path, X_OK) == 0)
		{
			free_paths(path.paths, cmd);
			return (path.path);
		}
		free(path.path);
	}
	free_paths(path.paths, cmd);
	return (NULL);
}

void	closepipes(t_cmd *cmd)
{
	close(cmd->fd[1]);
	close(cmd->fd[0]);
}
