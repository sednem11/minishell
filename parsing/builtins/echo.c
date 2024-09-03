/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:58:47 by macampos          #+#    #+#             */
/*   Updated: 2024/09/02 18:18:09 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dolar(char *user_input)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (user_input[i])
	{
		if (user_input[i] == 39)
			flag *= -1;
		if (user_input[i] == '$' && flag == 1)
			return (2);
		i++;
	}
	return (1);
}

int	check_backward_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 3 || cmd->redirection[i] == 2)
			return (1);
		i++;
	}
	return (0);
}

void	echo_redirections3(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->redirectionoverall == 1 && check_backward_redirection(cmd) == 0)
	{
		while (cmd->realarg[i])
		{
			printf("%s", cmd->realarg[i]);
			if (cmd->realarg[i + 1])
				printf("%s", " ");
			i++;
		}
	}
	printf("\n");
}

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

void	print_args(char **args, char *user_input, int i, t_main *main)
{
	int	j;
	int	flag;

	flag = 1;
	j = 0;
	while (j < (int)ft_strlen(args[i]))
	{
		if (args[i][j] == '$' && check_dolar(user_input) == 1)
		{
			print_dolar(main, &args[i][j + 1]);
			while (args[i][j] && args[i][j] != ' ')
				j++;
			flag = 0;
		}
		else
		{
			printf("%c", args[i][j]);
			j++;
		}
	}
	if (args[i + 1] && user_input[5 + ft_strlen(args[i])] == ' ' && flag == 1)
		printf("%s", " ");
}

void	echo(t_cmd *cmd, t_main *main, int i, char *user_input)
{
	if (cmd->args[1] && cmd->redirectionoverall != 0)
		echo_redirections2(cmd);
	else if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 2) == 0
		&& ft_strlen(cmd->args[1]) == 2 && cmd->args[3] == NULL)
	{
		i = 2;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf("%s", " ");
			i++;
		}
	}
	else if (cmd->args[1] && cmd->redirectionoverall == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			print_args(cmd->args, user_input, i, main);
			i++;
		}
		printf("\n");
	}
}
