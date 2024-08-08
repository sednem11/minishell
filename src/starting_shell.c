/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/08/08 23:49:22 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (access(path, X_OK) == 0)
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
	close(cmd->fd[1]);
	close(cmd->fd[0]);
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

void	check_nobuiltins_notexecutable(int *check, t_cmd *cmd, t_main *main)
{
	int	*check2;

	check2 = check_paired(&cmd->args[0][1], main->env, main->export,
			ft_strlen(&cmd->args[0][1]));
	if (cmd->args[0][0] == '$' && check2[0] != -1)
	{
		if (get_paths(&main->env[check2[0]][find_equal(main->env[check2[0]])
				+ 1], main->env))
		{
			execve(get_paths(&main->env[check2[0]][find_equal(main->env[check2[0]])
					+ 1], main->env),
				ft_split(&main->env[check2[0]][find_equal(main->env[check2[0]])
					+ 1], ' '), main->env);
		}
		if (check2[0] != -1)
		{
			printf("command not found: %s\n",
				&main->env[check2[0]][find_equal(main->env[check2[0]]) + 1]);
			free_every_thing(cmd, main, check);
			free(check2);
			exit(-1);
		}
	}
	free(check2);
}

void	not_builtin(int *check, char **envp, t_cmd *cmd, t_main *main)
{
	int		status;
	char	**a;

	a = NULL;
	if (check_builtins2(cmd, envp, main) == 1 && check[0] == -1)
		status = 127;
	if (ft_strncmp(cmd->args[0], "./minishell", 11) != 0)
	{
		if (cmd->realarg[0][0] == '/')
			execve(cmd->realarg[0], cmd->realarg, envp);
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
			write(2, " command not found\n", 19);
		status = 127;
		free_every_thing(cmd, main, check);
		exit(status);
	}
	else
	{
		execve("./minishell", a, envp);
		printf("%s\n", strerror(errno));
	}
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	char	*b;
	int		*check;

	check = check_paired("PATH=", main->env, main->export, 5);
	b = NULL;
	child2(cmd, main);
	check_nobuiltins_notexecutable(check, cmd, main);
	if (check_builtins2(cmd, envp, main) == 1 && check[0] == -1)
	{
		execve(b, cmd->realarg, envp);
		write(2, " No such file or directory\n", 28);
	}
	if (check_builtins2(cmd, envp, main) == 1 && check[0] != -1)
		not_builtin(check, envp, cmd, main);
	check_builtins(cmd, envp, main, user_input);
	free_every_thing(cmd, main, check);
	exit(0);
}

t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd,
		t_main *main)
{
	pid_t	id;

	if (cmd->next || check_builtins2(cmd, envp, main) == 1
		|| cmd->redirectionoverall != 0)
	{
		while (cmd)
		{
			if (cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
			{
				closepipes(cmd);
				return (export(cmd, envp, main));
			}
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset",
					5) == 0)
			{
				closepipes(cmd);
				return (unset(cmd, main, envp));
			}
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit",
					4) == 0)
			{
				closepipes(cmd);
				return (exitt(cmd, envp, main));
			}
			else
			{
				id = fork();
				if (id == -1)
					return (main);
				if (id == 0)
					child_process(user_input, envp, cmd, main);
				if (cmd->redirectionoverall == 2)
				{
					while (waitpid(id, &main->status, 0) != -1)
						;
				}
				closepipes(cmd);
			}
			cmd = cmd->next;
		}
	}
	else
		main = check_builtins(cmd, envp, main, user_input);
	while (waitpid(-1, &main->status, 0) != -1)
		;
	if (WIFEXITED(main->status))
		main->status = WEXITSTATUS(main->status);
	return (main);
}
