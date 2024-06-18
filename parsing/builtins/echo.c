/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:58:47 by macampos          #+#    #+#             */
/*   Updated: 2024/06/17 16:16:41 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_$(t_main *main, char *arg)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (ft_strncmp(arg, main->env[i], ft_strlen(arg)) == 0 && main->env[i][ft_strlen(arg)] == '=')
			printf("%s", &main->env[i][ft_strlen(arg) + 1]);
		i++;
	}
}

int	check_$(char *user_input)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = -1;
	while (user_input[i])
	{
		if (user_input[i] == '"' || user_input[i] == 39)
			flag *= -1;
		if (user_input[i] == '$' && flag == 1)
			return(i);
		i++;
	}
	return(1);
}

void	echo_redirections(t_cmd *cmd)
{
	int	i;
	int	file;
	
	i = 1;
	if (cmd->redirection == 1)
	{
		file = (open(cmd->args[cmd->redirectionpos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777));
		dup2(file, STDOUT_FILENO);
		closepipes(cmd);
	}
	if (cmd->redirection == 3 || cmd->redirection == 2)
	{
		printf("\n");
		return ;
	}
	while (cmd->realarg[i])
	{
		printf("%s", cmd->realarg[i]);
		if (cmd->realarg[i + 1])
			printf("%s", " ");
		i++;
	}
	printf("\n");
}

void	echo(t_cmd *cmd, t_main *main, int i, char *user_input)
{
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 2) == 0
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
	else if (cmd->args[1] && cmd->redirection == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			if (cmd->args[i][0] == '$' && check_$(user_input) == 1)
				print_$(main, &cmd->args[i][1]);
			else
				printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (cmd->args[1] && cmd->redirection != 0)
		echo_redirections(cmd);
}
