/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:02:33 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 16:26:52 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_heredoc3(t_cmd *cmd, int i, int file, char *input, t_main *main)
{
	while (ft_strncmp(input, &cmd->args[cmd->redirectionpos[i]][2],
			ft_strlen(&cmd->args[cmd->redirectionpos[i]][2]) != 0))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal_main3(main, cmd, file);
		if (ft_strncmp(input, &cmd->args[cmd->redirectionpos[i]][2],
				ft_strlen(&cmd->args[cmd->redirectionpos[i]][2]) != 0))
		{
			write(file, input, ft_strlen(input));
			write(file, "\n", 1);
		}
		input = readline("heredoc> ");
		check_signal_received(main, cmd, file);
	}
}

void	open_file2(t_cmd *cmd, int i, int *file, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
		*file = (open(&cmd->args[cmd->redirectionpos[i]][1], O_RDONLY, 0777));
	else
		*file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_RDONLY, 0777));
	if (*file == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		main->status = 1;
		exit(main->status);
	}
}
