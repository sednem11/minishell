/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/09/23 16:04:19 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_comands2(t_cmd *cmd, t_main *main, char **path2, char **envp)
{
	int	*place;

	place = check_paired("PATH=", main->env, main->export, 5);
	if (place[1] == -1)
		cmd->path = get_paths(cmd->args[0], path2);
	else
		cmd->path = get_paths(cmd->args[0], envp);
	free(place);
	if (pipe(cmd->fd) == -1)
		return ;
}

int	count_dif_redirections(char **argv)
{
	int	i;
	int	a;
	int	b;

	b = 0;
	a = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != ' ')
			return (2);
		if ((ft_strncmp(argv[i], ">", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], ">>", 2) == 0 && argv[i][2] != ' '))
			a = 1;
		if (ft_strncmp(argv[i], "<", 1) == 0 && argv[i][1] != ' ')
			b = 1;
		i++;
	}
	return (a + b);
}

int	pars_args(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strncmp(cmds[i], "|", 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_main	*check_builtins(t_cmd *cmd, char **envp, t_main *main, char *user_input)
{
	(void)user_input;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (main);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		cd(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& ft_strlen(cmd->args[0]) == 6)
		main = export(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& ft_strlen(cmd->args[0]) == 5)
		main = unset(cmd, main, envp);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		pwd(cmd, envp);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		env(cmd, envp);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		main = exitt(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		echo(cmd, main, 0, user_input);
	return (main);
}

int	check_pipes(char *user_input)
{
	int	i;
	int	flag;
	int	z;

	z = 0;
	flag = 1;
	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '|' && flag == 1)
			z++;
		if (user_input[i] == '"')
			flag *= -1;
		i++;
	}
	return (z);
}
