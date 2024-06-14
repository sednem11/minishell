/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/06/14 14:45:05 by macampos         ###   ########.fr       */
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

t_main	*check_builtins(t_cmd *cmd, char **envp, t_main *main, char *user_input)
{
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd(cmd, envp);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		main = export(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		main = unset(cmd , main, envp);
	else if(ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		pwd(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "env", 3) == 0)
		env(cmd, envp);
	else if(ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exitt(cmd, envp, main);
	else if(ft_strncmp(cmd->args[0], "echo", 4) == 0)
		echo(cmd, main, 0, user_input);
	return(main);
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

void	check_redirections(t_cmd *cmd, char *arg, int i)
{
	if (ft_strncmp(arg, ">", 1) == 0 && arg[1] == '\0')
	{
		if (cmd->redirection == 0)
			cmd->redirection = 1;
		cmd->redirectionpos = i;
	}
	else if (ft_strncmp(arg, "<", 1) == 0 && arg[1] == '\0')
	{
		if (cmd->redirection == 0)
			cmd->redirection = 2;
		cmd->redirectionpos = i;
	}
	else if (ft_strncmp(arg, "<<", 2) == 0 && arg[2] == '\0')
	{
		if (cmd->redirection == 0)
			cmd->redirection = 3;
		cmd->redirectionpos = i;
	}
	else if (ft_strncmp(arg, ">>", 2) == 0 && arg[2] == '\0')
	{
		if (cmd->redirection == 0)
			cmd->redirection = 4;
		cmd->redirectionpos = i;
	}
}

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**argv2;
	t_cmd	*begin;

	begin = NULL;
	(void)envp;
	argv2 = ft_split(argv, '\4');
	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	while (argv2[i])
	{
		cmd->redirection = 0;
		j = 0;
		cmd->args = ft_split(argv2[i], '\3');
		cmd->realarg = ft_split2(argv2[i], '\3');
		while (cmd->args[j])
		{
			check_redirections(cmd, cmd->args[j], j);
			j++;
		}
		cmd->path = get_paths(cmd->args[0], envp);
		if (begin == NULL)
			begin = cmd;
		cmd->begining = begin;
		if (argv2[i + 1])
		{
			cmd->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
			cmd = cmd->next;
		}
		set_comands2(cmd, i);
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
	argv = ft_calloc(sizeof(char), ft_strlen(user_input) + 1);
	while(user_input[i])
	{
		if (user_input[i] == '"' || user_input[i] == 39)
			flag *= -1;
		if (flag == -1 && user_input[i] == '|')
			argv[i] = '\4';
		else if ((flag == -1 && user_input[i] == ' ') || user_input[i] == '"' || user_input[i] == 39)
			argv[i] = '\3';
		else if ((flag == -1 && user_input[i] != ' ') || flag == 1)
			argv[i] = user_input[i];
		i++;
	}
	return(set_comands(argv, envp, cmd));
}
