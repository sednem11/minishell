/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:19 by macampos          #+#    #+#             */
/*   Updated: 2024/11/11 15:16:04 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_priority_arg(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if ((cmd->args[0][0] == '<' || cmd->args[0][0] == '>')
			&& cmd->args[i][0] != '<' && cmd->args[i][0] != '>'
			&& cmd->args[i - 1][0] != '<' && cmd->args[i - 1][0] != '>'
			&& strcmp(cmd->args[i], "cat") != 0)
			return (1);
		if (cmd->args[i][0] != '<' && cmd->args[i][0] != '>'
			&& cmd->args[i - 1][0] != '<' && cmd->args[i - 1][0] != '>'
			&& strcmp(cmd->args[i - 1], "grep") != 0 && cmd->args[0][0] != '<'
			&& cmd->args[0][0] != '>')
			return (1);
		i++;
	}
	return (0);
}

void	redirection3_help2(t_cmd *cmd, int i, int file)
{
	char	*input;

	input = readline("heredoc> ");
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2 && input)
		process_heredoc3(cmd, i, file, input);
	else if (input)
		redirection3_help(cmd, i, file, input);
	if (check_last_redirection2(cmd, i) == 0 && check_priority_arg(cmd) == 0)
		alloc_heredoc(cmd, "temporary");
}

void	redirection2_help(t_cmd *cmd, int i, int file, t_main *main)
{
	if (file == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		closepipes(cmd);
		free_both(main);
		free_every_thing(cmd, main, main->check);
		exit(1);
	}
	if (strcmp(cmd->args[0], "echo") != 0 || ft_strlen(cmd->args[0]) != 4)
		open_file2(cmd, i, &file, main);
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1
		&& check_last_redirection2(cmd, i) == 0
		&& check_overall_args(cmd) == 0 && check_priority_arg(cmd) == 0)
		alloc_heredoc(cmd, &cmd->args[cmd->redirectionpos[i]][1]);
	else if (check_last_redirection2(cmd, i) == 0
		&& check_overall_args(cmd) == 0 && check_priority_arg(cmd) == 0)
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
}

t_cmd	*initiate_args2(char *argv, t_ar *ar, t_cmd *cmd, t_main *main)
{
	if (ar->flag == 1)
	{
		printf("unclosed argument\n");
		free(argv);
		free(ar);
		return (NULL);
	}
	free(ar);
	return (set_comands(argv, cmd, main));
}
