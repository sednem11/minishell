/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:41:30 by macampos          #+#    #+#             */
/*   Updated: 2024/10/07 10:00:52 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_1(t_cmd *cmd, int file, int i, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1 || ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0)
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
		{
			file = (open(&cmd->args[cmd->redirectionpos[i]][1],
						O_WRONLY | O_CREAT | O_TRUNC, 0777));
		}
		else
		{
			file = (open(cmd->args[cmd->redirectionpos[i] + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0777));
		}
		if (file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			main->status = 1;
			close(file);
			exit(main->status);
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
	int	status;

	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1 || ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0)
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
			&& get_paths(cmd->args[0], main->env) != NULL)
		{
			file = (open(&cmd->args[cmd->redirectionpos[i]][1], O_RDONLY));
		}
		else if (get_paths(cmd->args[0], main->env) != NULL)
		{
			file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_RDONLY));
		}
		if (file == -1)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			status = 1;
			close(file);
			closepipes(cmd);
			free_both(main);
			free(main->check);
			free_every_thing(cmd, main, NULL);
			exit(status);
		}
		if (ft_strncmp(cmd->args[0], "echo", 4) != 0)
			open_file2(cmd, i, &file, main);
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
			&& check_last_redirection2(cmd, i) == 0 && check_overall_args(cmd) == 0)
		{
			if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
				alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
			alloc_heredoc(cmd, &cmd->args[cmd->redirectionpos[i]][1]);
		}
		else if (check_last_redirection2(cmd, i) == 0
			&& check_overall_args(cmd) == 0)
		{
			if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
				alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 2]);
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
		}
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	redirection3(t_cmd *cmd, int i, int file, t_main *main)
{
	char	*input;

	(void)main;
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2 || ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		file = (open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644));
		signal_main3(main, cmd, file);
		input = readline("heredoc> ");
		printf("AHHHH\n");
		if (check_signal_received(main, cmd, file) == 0)
			exit(0);
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
			process_heredoc3(cmd, i, file, input, main);
		else
			redirection3_help(cmd, i, file, input, main);
		if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
		{
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 2]);
		}
		if (check_last_redirection2(cmd, i) == 0)
			alloc_heredoc(cmd, "temporary");
		close(file);
	}
	else
		ft_putstr_fd(" No such file or directory", 2);
}

void	redirection4(t_cmd *cmd, int i, int file, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2 || ft_strlen(cmd->args[cmd->redirectionpos[i] + 1]) > 0)
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2
			&& get_paths(cmd->args[0], main->env) != NULL)
			file = (open(&cmd->args[cmd->redirectionpos[i]][2],
						O_WRONLY | O_CREAT | O_APPEND, 0777));
		else if (get_paths(cmd->args[0], main->env) != NULL)
			file = (open(cmd->args[cmd->redirectionpos[i] + 1],
						O_WRONLY | O_CREAT | O_APPEND, 0777));
		if (file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			main->status = 1;
			close(file);
			exit(main->status);
		}
		dup2(file, STDOUT_FILENO);
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
