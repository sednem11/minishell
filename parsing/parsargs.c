/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/22 14:18:23 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*set_comands_help(int i, t_cmd *cmd2, t_cmd *begin)
{
	int	j;

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
	if (i == 0)
		begin = cmd2;
	return (begin);
}

t_cmd	*set_comands_help2(t_cmd *cmd2, char *argv, int i, t_cmd *begin)
{
	cmd2->begining = begin;
	if (cmd2->argv2[i + 1])
	{
		cmd2->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
		cmd2->next->argv2 = ft_split(argv, '\4');
		cmd2 = cmd2->next;
	}
	return (cmd2);
}

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd, t_main *main)
{
	int		i;
	char	**path2;
	t_cmd	*cmd2;
	t_cmd	*begin;
	char	*temp;

	i = -1;
	(void)cmd;
	cmd2 = NULL;
	path2 = ft_calloc(sizeof(char *), 2);
	path2[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	temp = path2[0];
	path2[0] = ft_strjoin(path2[0], "/usr/sbin:/usr/bin:/sbin:/bin");
	free(temp);
	cmd2 = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	cmd2->argv2 = ft_split(argv, '\4');
	while (cmd2->argv2[++i])
	{
		begin = set_comands_help(i, cmd2, begin);
		set_comands2(cmd2, main, path2, envp);
		cmd2 = set_comands_help2(cmd2, argv, i, begin);
	}
	i = 0;
	cmd = cmd2->begining;
	while(cmd)
	{
		i++;
		cmd = cmd->next;
	}
	cmd2->numb = i;
	free(path2[0]);
	free(path2);
	free(argv);
	return (cmd2->begining);
}

void	check_args(char *user_input, t_ar *ar, char *argv)
{
	if ((user_input[ar->i] == '"' || user_input[ar->i] == 39) && ar->flag == -1)
		ar->j = ar->i;
	if ((user_input[ar->i] == '"' || user_input[ar->i] == 39)
		&& user_input[ar->i] == user_input[ar->j])
	{
		ar->j = ar->i;
		ar->flag *= -1;
	}
	if (ar->flag == -1 && user_input[ar->i] == '|')
		argv[ar->i] = '\4';
	else if (ar->flag == -1 && user_input[ar->i] == ' ')
		argv[ar->i] = '\3';
	else if ((ar->flag == -1 && (user_input[ar->i] == '"'
				|| user_input[ar->i] == 39)) || ((user_input[ar->i] == '"'
				|| user_input[ar->i] == 39) && ar->j == ar->i))
		argv[ar->i] = '\5';
	else if ((ar->flag == -1 && user_input[ar->i] != ' ') || ar->flag == 1)
		argv[ar->i] = user_input[ar->i];
}

t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	t_ar	*ar;
	char	*argv;

	ar = malloc(sizeof(t_ar));
	ar->j = 0;
	ar->i = 0;
	ar->flag = -1;
	argv = ft_calloc(sizeof(char), ft_strlen(user_input) + 1);
	while (user_input[ar->i])
	{
		check_args(user_input, ar, argv);
		ar->i++;
	}
	if (ar->flag == 1)
	{
		printf("unclosed argument\n");
		free(ar);
		return (NULL);
	}
	free(ar);
	return (set_comands(argv, envp, cmd, main));
}

// echo hello > out | cat < Makefile < infile