/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/04/17 20:18:07 by macampos         ###   ########.fr       */
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

int check_builtins(t_cmd *cmd, char **envp)
{
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "export", 6) == 0)
		export(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		pwd(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "env", 3) == 0)
		env(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exitt(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "echo", 4) == 0)
		echo(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "unset", 5) == 0)
		unset(cmd, envp);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0], "export", 6) == 0
		|| ft_strncmp(cmd->args[0], "pwd", 3) == 0 || ft_strncmp(cmd->args[0], "env", 3) == 0
		|| ft_strncmp(cmd->args[0], "exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return(0);
	else
		return(1);
}

int	check_pipes(char *user_input)
{
	int	i;
	int	flag;
	int	z;

	z = 0;
	flag = 1;
	i = 0;
	while(user_input[i])
	{
		if (user_input[i] == '|' && flag == 1)
			z++;
		if (user_input[i] == '"')
			flag *= -1;
		i++;
	}
	return(z);
}

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd)
{
	int		i;
	char	**argv2;
	t_cmd	*begin;
	t_cmd	*temp;

	temp = NULL;
	begin = NULL;
	(void)envp;
	argv2 = ft_split(argv, '\4');
	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	while (argv2[i])
	{
		cmd->args = ft_split(argv2[i], '\3');
		cmd->path = get_paths(cmd->args[0], envp);
		if (begin == NULL)
			begin = cmd;
		cmd->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
		cmd = cmd->next;
		i++;
	}
	return(begin);
}

t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd)
{
	int		flag;
	int		i;
	char	*argv;

	i = 0;
	flag = -1;
	argv = ft_calloc(ft_strlen(user_input), sizeof(char *));
	while(user_input[i])
	{
		if (user_input[i] == '"')
			flag *= -1;
		if (flag == -1 && user_input[i] == '|')
			argv[i] = '\4';
		else if ((flag == -1 && user_input[i] != ' ') || flag == 1 || user_input[i] == '"')
			argv[i] = user_input[i];
		else if (flag == -1 && user_input[i] == ' ')
			argv[i] = '\3';
		i++;
	}
	return(set_comands(argv, envp, cmd));
}
