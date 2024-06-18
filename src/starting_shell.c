/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/06/18 16:42:51 by macampos         ###   ########.fr       */
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
		{
			free_paths(paths, cmd);
			return (path);
		}
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

void	alloc_heredoc(t_cmd *cmd, char	*alocated)
{
	char	**new;
	int		i;

	i = 0;
	new = calloc(sizeof(char *), matrixlen(cmd->realarg) + 2);
	while(cmd->realarg[i])
	{
		new[i] = cmd->realarg[i];
		i++;
	}
	new[i] = ft_strdup(alocated);
	free(cmd->realarg);
	cmd->realarg = new;
}

void	aplly_redirections(t_cmd *cmd)
{
	int		file;
	char	*input;
	int		i;
	
	i = 0;
	input = NULL;
	if (cmd->redirection == 1)
	{
		file = (open(cmd->args[cmd->redirectionpos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777));
		dup2(file, STDOUT_FILENO);
	}
	else if (cmd->redirection == 2)
	{
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos + 1]);
	}
	else if (cmd->redirection == 3)
	{
		input = readline("heredoc> ");
		file = (open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0777));
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		while (ft_strncmp(input, cmd->args[cmd->redirectionpos + 1],
			ft_strlen(cmd->args[cmd->redirectionpos + 1]) != 0))
		{
			input = readline("heredoc> ");
			if(ft_strncmp(input, cmd->args[cmd->redirectionpos + 1],
				ft_strlen(cmd->args[cmd->redirectionpos + 1]) != 0))
			{
				write(file, input, ft_strlen(input));
				write(file, "\n", 1);
			}
		}
		alloc_heredoc(cmd, "temporary");
	}
	else if (cmd->redirection == 4)
	{
		file = (open(cmd->args[cmd->redirectionpos + 1], O_WRONLY | O_CREAT | O_APPEND, 0777));
		dup2(file, STDOUT_FILENO);
	}
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	if (pars_args(ft_split(user_input, ' ')) != -1)
	{
		if (cmd == cmd->begining)
		{
			aplly_redirections(cmd);
			if (cmd->redirection == 0)
				dup2(cmd->next->fd[1], STDOUT_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next == NULL)
		{
			aplly_redirections(cmd);
			if (cmd->redirection == 0)
				dup2(cmd->fd[0], STDIN_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			aplly_redirections(cmd);
			if (cmd->redirection == 0)
			{
				dup2(cmd->fd[0], STDIN_FILENO);
				dup2(cmd->next->fd[1], STDOUT_FILENO);
			}
			closepipes(cmd);
		}
	}
	aplly_redirections(cmd);
	if (check_builtins2(cmd, envp, main) == 1)
	{
		if (ft_strncmp(cmd->args[0], "./minishell", 11) != 0)
		{
			if (cmd->path)
				execve(cmd->path , cmd->realarg, envp);
		}
		else
		{
			char **a = NULL;
			execve("./minishell" , a, envp);
			printf("%s\n", strerror(errno));
		}
	}
	check_builtins(cmd, envp, main, user_input);
	exit(1);
}

t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	pid_t	id;
	
	if (cmd->next || check_builtins2(cmd, envp, main) == 1 || cmd->redirection != 0)
	{
		while(cmd)
		{
			if (cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
			{
				closepipes(cmd);
				return (export(cmd, envp, main));
			}
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset", 5) == 0)
			{
				closepipes(cmd);
				return (unset(cmd, main, envp));
			}
			else
			{
				id = fork();
				if (id == -1)
					return(main);
				if (id == 0)
					child_process(user_input, envp, cmd, main);
				closepipes(cmd);
			}
			cmd = cmd->next;
		}
	}
	else
		main = check_builtins(cmd, envp, main, user_input);
	while (waitpid(-1, NULL, 0) != -1);
	return(main);
}
	