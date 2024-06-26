/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/06/26 10:06:20 by macampos         ###   ########.fr       */
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

int		check_last_redirection(t_cmd *cmd, int i)
{
	int j;
	
	j = i + 1;
	while(cmd->redirection[j])
	{
		if (cmd->redirection[i] == cmd->redirection[j])
			return(-1);
		j++;
	}
	return(1);
}

void	aplly_redirections(t_cmd *cmd)
{
	int		file;
	char	*input;
	int		i;
	int		flag;
	
	flag = 0;
	i = 0;
	input = NULL;
	while(i < count_redirections(cmd->args))
	{
		if (cmd->redirectionoverall == 2 && flag == 0)
		{
			while(cmd->redirection[i] != 3)
				i++;
			flag = 1;
		}
		if (cmd->redirection[i] == 1)
		{
			file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777));
			if (check_last_redirection(cmd, i) == 1)
				dup2(file, STDOUT_FILENO);
		}
		else if (cmd->redirection[i] == 2 && flag != 2)
		{
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
		}
		else if (cmd->redirection[i] == 3 && flag != 2)
		{
			input = readline("heredoc> ");
			file = (open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0777));
			write(file, input, ft_strlen(input));
			write(file, "\n", 1);
			while (ft_strncmp(input, cmd->args[cmd->redirectionpos[i] + 1],
				ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) != 0))
			{
				input = readline("heredoc> ");
				if(ft_strncmp(input, cmd->args[cmd->redirectionpos[i] + 1],
					ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) != 0))
				{
					write(file, input, ft_strlen(input));
					write(file, "\n", 1);
				}
			}
			if (cmd->redirectionoverall != 2)
				alloc_heredoc(cmd, "temporary");
		}
		else if (cmd->redirection[i] == 4)
		{
			file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_WRONLY | O_CREAT | O_APPEND, 0777));
			dup2(file, STDOUT_FILENO);
		}
		if (cmd->redirectionoverall == 2 && flag == 1)
		{
			i = 0;
			flag = 2;
		}
		else
			i++;
	}
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	char	**a;
	char	*b;

	b = NULL;
	a = NULL;
	if (cmd->argv2[1])
	{
		if (cmd == cmd->begining)
		{
			aplly_redirections(cmd);
			if (cmd->redirectionoverall == 0)
				dup2(cmd->next->fd[1], STDOUT_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next == NULL)
		{
			aplly_redirections(cmd);
			if (cmd->redirectionoverall == 0)
				dup2(cmd->fd[0], STDIN_FILENO);
			closepipes(cmd);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			aplly_redirections(cmd);
			if (cmd->redirectionoverall == 0)
			{
				dup2(cmd->fd[0], STDIN_FILENO);
				dup2(cmd->next->fd[1], STDOUT_FILENO);
			}
			closepipes(cmd);
		}
	}
	aplly_redirections(cmd);
	if (check_builtins2(cmd, envp, main) == 1 && check_paired("PATH=", main->env, main->export, 5)[0] == -1)
	{
		execve(b , cmd->realarg, envp);
		write(2, " No such file or directory\n", 28);
		main->status = 127;
		exit(main->status);
	}
	if (check_builtins2(cmd, envp, main) == 1 && check_paired("PATH=", main->env, main->export, 5)[0] != -1)
	{
		if (ft_strncmp(cmd->args[0], "./minishell", 11) != 0)
		{
			execve(cmd->path , cmd->realarg, envp);
			if (ft_strncmp(cmd->args[0], "./", 2) == 0)
			{
				write(2, " No such file or directory\n", 28);
				main->status = 126;
				exit(main->status);
			}
			if (ft_strncmp(cmd->args[0], "/", 1) == 0)
				write(2, " No such file or directory\n", 28);
			else if (cmd->args[0][0] == '$' && cmd->args[1]
				&& check_paired(cmd->args[0], main->env, main->export, ft_strlen(cmd->args[0]) - 1)[0] == -1)
				execve(cmd->path , &cmd->args[1], envp);
			else
				write(2, " command not found\n", 19);
			main->status = 127;
			exit(main->status);
		}
		else
		{
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
	
	if (cmd->next || check_builtins2(cmd, envp, main) == 1 || cmd->redirectionoverall != 0)
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
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit", 4) == 0)
			{
				closepipes(cmd);
				return (exitt(cmd, envp, main));	
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
	while (waitpid(-1, &main->status, 0) != -1);
	if (WIFEXITED(main->status))
		main->status = WEXITSTATUS(main->status);
	return(main);
}


//echo hello | exit 4 | pwd