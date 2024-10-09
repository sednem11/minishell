/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:58:47 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 18:46:17 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_redirections2(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (check_backward_redirection(cmd) == 0)
		echo_redirections3(cmd);
	else
	{
		while (cmd->args[++i])
		{
			if (ft_strncmp(cmd->args[i], ">", 1) == 0
				|| (ft_strncmp(cmd->args[i - 1], ">", 1) == 0
					&& ft_strlen(cmd->args[i - 1]) <= 2)
				|| ft_strncmp(cmd->args[i], "<", 1) == 0
				|| (ft_strncmp(cmd->args[i - 1], "<", 1) == 0
					&& ft_strlen(cmd->args[i - 1]) <= 2))
				;
			else
			{
				printf("%s", cmd->args[i]);
				if (cmd->args[i + 1])
					printf("%s", " ");
			}
		}
		printf("\n");
	}
}

void	print_args(t_cmd *cmd, char *user_input, int i, t_main *main)
{
	int	j;
	int	flag;

	flag = 1;
	j = 0;
	while (j < (int)ft_strlen(cmd->args[i]))
	{
		if (cmd->args[i][j] == '$' && check_aspas(user_input, i, NULL) == 0)
		{
			print_dolar(main, &cmd->args[i][j + 1]);
			while (cmd->args[i][j] && cmd->args[i][j] != ' '
				&& cmd->args[i][j] != '\'')
				j++;
			flag = 0;
		}
		else
		{
			printf("%c", cmd->args[i][j]);
			j++;
		}
	}
	if (cmd->args[i + 1] && flag == 1)
		printf("%s", " ");
}

int	check_nonl(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (-1);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (-1);
		while (arg[i] && arg[i] == 'n')
			i++;
	}
	return (0);
}

void	echo2(t_cmd *cmd, char *user_input, int i, t_main *main)
{
	i = 1;
	while (cmd->args[i])
	{
		print_args(cmd, user_input, i, main);
		i++;
	}
	main->status = 0;
	printf("\n");
}

void	echo(t_cmd *cmd, t_main *main, int i, char *user_input)
{
	if (cmd->args[1] && cmd->redirectionoverall != 0)
		echo_redirections2(cmd);
	else if (cmd->args[1] && check_nonl(cmd->args[1]) == 0)
	{
		i = 1;
		while (cmd->args[i] && check_nonl(cmd->args[i]) != -1)
			i++;
		while (cmd->args[i])
		{
			if (cmd->args[i])
				printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf("%s", " ");
			i++;
		}
	}
	else if (cmd->args[1] && cmd->redirectionoverall == 0)
		echo2(cmd, user_input, i, main);
}
