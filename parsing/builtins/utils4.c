/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:02:33 by macampos          #+#    #+#             */
/*   Updated: 2024/10/07 12:57:36 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_heredoc3(t_cmd *cmd, int i, int file, char *input)
{
	while (input && (strcmp(input, &cmd->args[cmd->redirectionpos[i]][2]) != 0
			|| ft_strlen(input) != ft_strlen(&cmd->args[cmd->redirectionpos[i]][2])))
	{
		if (strcmp(input, &cmd->args[cmd->redirectionpos[i]][2]) != 0
			&& ft_strlen(input) != ft_strlen(&cmd->args[cmd->redirectionpos[i]][2]))
		{
			write(file, input, ft_strlen(input));
			write(file, "\n", 1);
		}
		input = readline("heredoc> ");
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
		closepipes(cmd);
		free_both(main);
		free_every_thing(cmd, main, main->check);
		exit(127);
	}
}
