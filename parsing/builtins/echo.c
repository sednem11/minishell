/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:58:47 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 17:33:26 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_$(t_main *main, char *arg)
{
	int		i;
	char	**value;

	value = ft_split(arg, ' ');
	i = 1;
	if (!arg[0] || arg[0] == ' ')
	{
		printf("$");
		return ;
	}
	if (arg[0] == '?')
	{
		printf("%i", main->status);
		while (arg[i] && arg[i] != ' ')
		{
			printf("%c", arg[i]);
			i++;
		}
	}
	else
	{
		i = 0;
		while (main->env[i])
		{
			if (ft_strncmp(value[0], main->env[i], ft_strlen(value[0])) == 0
				&& main->env[i][ft_strlen(value[0])] == '=')
				printf("%s", &main->env[i][ft_strlen(value[0]) + 1]);
			i++;
		}
	}
}

int check_$(char *user_input)
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
			return (i);
		i++;
	}
	return (1);
}

void	echo_redirections(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->realarg[i])
	{
		printf("%s", cmd->realarg[i]);
		if (cmd->realarg[i + 1])
			printf("%s", " ");
		i++;
	}
	printf("\n");
}

void	print_args(char **args, char *user_input, int i, t_main *main)
{
	int	j;
	int	flag;

	flag = 1;
	j = 0;
	while (j < (int)ft_strlen(args[i]))
	{
		if (args[i][j] == '$' && check_$(user_input) == 1)
		{
			print_$(main, &args[i][j + 1]);
			while (args[i][j] != ' ')
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
		echo_redirections(cmd);
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
