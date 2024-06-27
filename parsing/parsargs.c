/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 14:07:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int	count_redirections(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if ((ft_strncmp(argv[i], ">", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], "<", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != ' ')
			|| (ft_strncmp(argv[i], ">>", 2) == 0 && argv[i][2] != ' '))
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	return (j);
}
void	check_redirections(t_cmd *cmd, char *arg, int j)
{
	int	i;

	i = 0;
	if (ft_strncmp(arg, ">", 1) == 0 && arg[1] != '>')
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 1;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else if (ft_strncmp(arg, "<", 1) == 0 && arg[1] != '<')
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 2;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else if (ft_strncmp(arg, "<<", 2) == 0)
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 3;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		i = 0;
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 0)
			{
				cmd->redirection[i] = 4;
				break ;
			}
			i++;
		}
		cmd->redirectionpos[i] = j;
	}
}
void	free_cmd_args(t_cmd *cmd)
{
	int		i;
	t_cmd	*temporary;

	temporary = cmd;
	closepipes(cmd);
	while (temporary)
	{
		cmd = temporary;
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
		free(cmd->argv2);
		free(cmd->realarg);
		temporary = cmd->next;
		free(cmd->redirection);
		free(cmd->redirectionpos);
		free(cmd->path);
		free(cmd);
	}
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
		if ((ft_strncmp(argv[i], ">", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], ">>", 2) == 0 && argv[i][2] != ' '))
			a = 1;
		if ((ft_strncmp(argv[i], "<", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != ' '))
			b += 1;
		i++;
	}
	if (b > 1)
		return (2);
	return (a + b);
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
	path2 = calloc(sizeof(char *), 2);
	path2[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	(void)envp;
	if (cmd)
		free_cmd_args(cmd);
	cmd2 = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	cmd2->argv2 = ft_split(argv, '\4');
	while (cmd2->argv2[i])
	{
		j = 0;
		cmd2->args = ft_split(cmd2->argv2[i], '\3');
		cmd2->realarg = ft_split2(cmd2->argv2[i], '\3');
		cmd2->redirection = calloc(sizeof(int), count_redirections(cmd2->args));
		cmd2->redirectionpos = calloc(sizeof(int),
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
		set_comands2(cmd2, i);
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
		else if ((flag == -1 && (user_input[i] == ' ' || user_input[i] == '"'
					|| user_input[i] == 39)) || ((user_input[i] == '"'
					|| user_input[i] == 39) && j == i))
			argv[i] = '\3';
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

// echo "hello hjvb"       cat < out > out2

// >>
// >
// <<
// <