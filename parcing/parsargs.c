/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/04/16 21:47:20 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pars_args(char **cmds)
{
	int     i;

	i = 0;
	while(cmds[i])
	{
		if (ft_strncmp(cmds[i], "|", 1) == 0)
			return(i);
		i++;
	}
	return(-1);
}

int check_builtins(char **cmd, char *path, char **envp)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		cd(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "export", 6) == 0)
		export(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "pwd", 3) == 0)
		pwd(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "env", 3) == 0)
		env(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "exit", 4) == 0)
		exitt(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "echo", 4) == 0)
		echo(cmd, path, envp);
	else if(ft_strncmp(cmd[0], "unset", 5) == 0)
		unset(cmd, path, envp);
	if (ft_strncmp(cmd[0], "cd", 2) == 0 || ft_strncmp(cmd[0], "export", 6) == 0
		|| ft_strncmp(cmd[0], "pwd", 3) == 0 || ft_strncmp(cmd[0], "env", 3) == 0
		|| ft_strncmp(cmd[0], "exit", 4) == 0 || ft_strncmp(cmd[0], "echo", 4) == 0
		|| ft_strncmp(cmd[0], "unset", 5) == 0)
		return(0);
	else
		return(1);
}

void	initiate_args(char *user_input, char **envp, t_cmd cmd)
{
	int		flag;
	int		i;
	char	*argv;

	(void)envp;
	i = 0;
	flag = 0;
	argv = NULL;
	while(user_input[i])
	{
		if ((flag == 0 && user_input[i] != ' ') || flag == 1)
			argv[i] = user_input[i];
		if (flag == 0 && user_input[i] == ' ')
			argv[i] = '\3';
		if (user_input[i] == '"')
			flag = 1;
		i++;
	}
	cmd.args = ft_split(argv, '\3');
}
