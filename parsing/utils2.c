/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:41:30 by macampos          #+#    #+#             */
/*   Updated: 2024/11/01 19:08:40 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_1(t_cmd *cmd, int file, int i, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
		|| (cmd->args[cmd->redirectionpos[i] + 1]
			&& ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0))
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
			file = (open(&cmd->args[cmd->redirectionpos[i]][1],
						O_WRONLY | O_CREAT | O_TRUNC, 0777));
		else
			file = (open(cmd->args[cmd->redirectionpos[i] + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0777));
		if (file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			closepipes(cmd);
			free_both(main);
			free_every_thing(cmd, main, main->check);
			exit(1);
		}
		else if (check_last_redirection(cmd, i) == 1)
			dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	redirection2(t_cmd *cmd, int i, int file, t_main *main)
{
	char	*path;

	path = get_paths(cmd->args[0], main->env);
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
		|| (cmd->args[cmd->redirectionpos[i] + 1]
			&& ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0))
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1 && path != NULL)
		{
			file = (open(&cmd->args[cmd->redirectionpos[i]][1], O_RDONLY));
		}
		else if (path != NULL)
		{
			file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_RDONLY));
		}
		if (file == -1)
			free(path);
		redirection2_help(cmd, i, file, main);
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	redirection3(t_cmd *cmd, int i, int file, t_main *main)
{
	(void)main;
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2
		|| (cmd->args[cmd->redirectionpos[i] + 1]
			&& ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		file = (open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
					0644));
		signal_main3(main, cmd, file);
		redirection3_help2(cmd, i, file);
		close(file);
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	redirection4(t_cmd *cmd, int i, int file, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2
		|| (cmd->args[cmd->redirectionpos[i] + 1]
			&& ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0))
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
			file = (open(&cmd->args[cmd->redirectionpos[i]][2],
						O_CREAT | O_WRONLY | O_APPEND, 0777));
		else
			file = (open(cmd->args[cmd->redirectionpos[i] + 1],
						O_CREAT | O_WRONLY | O_APPEND, 0777));
		if (file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			closepipes(cmd);
			free_both(main);
			free_every_thing(cmd, main, main->check);
			exit(1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	free_every_thing(t_cmd *cmd, t_main *main, int *check)
{
	free_env_and_export(main);
	free(main);
	free_cmd_args(cmd);
	if (check)
		free(check);
}
