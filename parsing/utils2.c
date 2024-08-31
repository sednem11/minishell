/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:41:30 by macampos          #+#    #+#             */
/*   Updated: 2024/08/31 23:14:38 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_1(t_cmd *cmd, int file, int i, t_main *main)
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
		write(2, " permission denied\n", 20);
		main->status = 1;
		exit(main->status);
	}
	else if (check_last_redirection(cmd, i) == 1)
		dup2(file, STDOUT_FILENO);
	close(file);
}

void	redirection2(t_cmd *cmd, int i, int file, t_main *main)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) != 0)
		open_file2(cmd, i, &file, main);
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
		&& check_last_redirection2(cmd, i) == 0)
	{
		if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
		alloc_heredoc(cmd, &cmd->args[cmd->redirectionpos[i]][1]);
	}
	else if (check_last_redirection2(cmd, i) == 0)
	{
		if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
			alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 2]);
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
	}
}

void	redirection3(t_cmd *cmd, int i, int file)
{
	char	*input;

	input = readline("heredoc> ");
	file = (open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644));
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
		process_heredoc3(cmd, i, file, input);
	else
		redirection3_help(cmd, i, file, input);
	if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
	if (cmd->args[0] == cmd->args[cmd->redirectionpos[i]])
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 2]);
	if (check_last_redirection2(cmd, i) == 0)
		alloc_heredoc(cmd, "temporary");
}

void	redirection4(t_cmd *cmd, int i, int file, t_main *main)
{
	int	j;

	j = 2;
	redirection4_helper(cmd, i, j);
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
		file = (open(&cmd->args[cmd->redirectionpos[i]][2],
					O_WRONLY | O_CREAT | O_APPEND, 0777));
	else
		file = (open(cmd->args[cmd->redirectionpos[i] + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0777));
	if (file == -1)
	{
		write(2, " permission denied\n", 20);
		main->status = 1;
		exit(main->status);
	}
	dup2(file, STDOUT_FILENO);
}

void	free_every_thing(t_cmd *cmd, t_main *main, int *check)
{
	free_env_and_export(main);
	free(main);
	free_cmd_args(cmd);
	if (check)
		free(check);
}
