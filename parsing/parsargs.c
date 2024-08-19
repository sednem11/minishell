/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 15:07:43 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redirections(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if ((ft_strncmp(argv[i], ">", 1) == 0) || (ft_strncmp(argv[i], "<",
					1) == 0) || (ft_strncmp(argv[i], "<<", 2) == 0)
			|| (ft_strncmp(argv[i], ">>", 2) == 0))
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	return (j);
}

void	closeallpipes(t_cmd *cmd)
{
	while (cmd)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd = cmd->next;
	}
}

void	free_cmd_args2(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	i = 0;
	while (cmd->realarg[i])
	{
		free(cmd->realarg[i]);
		i++;
	}
	i = 0;
	while (cmd->argv2[i])
	{
		free(cmd->argv2[i]);
		i++;
	}
}

void	free_cmd_args(t_cmd *cmd)
{
	t_cmd	*temporary;

	closeallpipes(cmd->begining);
	temporary = cmd->begining;
	while (temporary)
	{
		cmd = temporary;
		free_cmd_args2(cmd);
		free(cmd->argv2);
		free(cmd->realarg);
		temporary = cmd->next;
		free(cmd->redirection);
		free(cmd->redirectionpos);
		free(cmd->path);
		free(cmd);
	}
}

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd, t_main *main)
{
	int		i;
	int		j;
	int		*place;
	char	**path2;
	t_cmd	*cmd2;
	t_cmd	*begin;

	i = 0;
	cmd2 = NULL;
	path2 = ft_calloc(sizeof(char *), 2);
	path2[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	(void)envp;
	if (cmd)
		free_cmd_args(cmd);
	cmd2 = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	cmd2->argv2 = ft_split(argv, '\4');
	while (cmd2->argv2[i])
	{
		j = 0;
		cmd2->args = ft_split3(cmd2->argv2[i], '\3');
		cmd2->realarg = ft_split2(cmd2->argv2[i], '\3');
		cmd2->redirection = ft_calloc(sizeof(int),
				count_redirections(cmd2->args));
		cmd2->redirectionpos = ft_calloc(sizeof(int),
				count_redirections(cmd2->args));
		cmd2->redirectionoverall = count_dif_redirections(cmd2->args);
		while (cmd2->args[j])
		{
			check_redirections(cmd2, cmd2->args[j], j);
			j++;
		}
		place = check_paired("PATH=", main->env, main->export, 5);
		if (place[1] == -1)
			cmd2->path = get_paths(cmd2->args[0], path2);
		else
			cmd2->path = get_paths(cmd2->args[0], envp);
		free(place);
		if (i == 0)
			begin = cmd2;
		cmd2->begining = begin;
		set_comands2(cmd2);
		if (cmd2->argv2[i + 1])
		{
			cmd2->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
			cmd2->next->argv2 = ft_split(argv, '\4');
			cmd2 = cmd2->next;
		}
		i++;
	}
	free(path2[0]);
	free(path2);
	free(argv);
	return (cmd2->begining);
}

t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	int		flag;
	int		i;
	int		j;
	char	*argv;

	j = 0;
	i = 0;
	flag = -1;
	argv = ft_calloc(sizeof(char), ft_strlen(user_input) + 1);
	while (user_input[i])
	{
		if ((user_input[i] == '"' || user_input[i] == 39) && flag == -1)
			j = i;
		if ((user_input[i] == '"' || user_input[i] == 39)
			&& user_input[i] == user_input[j])
		{
			j = i;
			flag *= -1;
		}
		if (flag == -1 && user_input[i] == '|')
			argv[i] = '\4';
		else if (flag == -1 && user_input[i] == ' ')
			argv[i] = '\3';
		else if ((flag == -1 && (user_input[i] == '"' || user_input[i] == 39))
			|| ((user_input[i] == '"' || user_input[i] == 39) && j == i))
			argv[i] = '\5';
		else if ((flag == -1 && user_input[i] != ' ') || flag == 1)
			argv[i] = user_input[i];
		i++;
	}
	if (flag == 1)
	{
		printf("unclosed argument\n");
		return (NULL);
	}
	return (set_comands(argv, envp, cmd, main));
}

// echo hello > out | cat < Makefile < infile