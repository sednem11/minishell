/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/06/19 16:11:46 by macampos         ###   ########.fr       */
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
void	free_cmd_args(t_cmd *cmd)
{
	int	i;
	t_cmd *temporary;

	temporary = cmd;
	while(temporary)
	{
		cmd = temporary;
		i = 0;
		while(cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		i = 0;
		while(cmd->realarg[i])
		{
			free(cmd->realarg[i]);
			i++;
		}
		free(cmd->realarg);
		temporary = cmd->next;
		free(cmd->path);
		free(cmd);
	}
}

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**argv2;
	t_cmd	*cmd2;
	t_cmd	*begin;

	cmd2 = NULL;
	(void)envp;
	argv2 = ft_split(argv, '\4');
	i = 0;
	cmd2 = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	while (argv2[i])
	{
		cmd2->redirection = 0;
		j = 0;
		cmd2->args = ft_split(argv2[i], '\3');
		cmd2->realarg = ft_split2(argv2[i], '\3');
		while (cmd2->args[j])
		{
			check_redirections(cmd2, cmd2->args[j], j);
			j++;
		}
		cmd2->path = get_paths(cmd2->args[0], envp);
		if (i == 0)
			begin = cmd2;
		cmd2->begining = begin;
		set_comands2(cmd2, i);
		if (argv2[i + 1])
		{
			cmd2->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
			cmd2 = cmd2->next;
		}
		free(argv2[i]);
		i++;
	}
	if(cmd)
		free_cmd_args(cmd);
	free(argv);
	free(argv2);
	return(cmd2->begining);
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
