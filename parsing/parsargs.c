/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/31 20:51:20 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_for_expansion(t_cmd *cmd, char **fakeargs, t_main *main)
{
	int		i;
	int		k;
	int		j;
	int		*check;
	char	**expansion;

	i = 0;
	k = 0;
	while (fakeargs[k])
	{
		if (ft_strncmp(fakeargs[k], "$", 1) == 0 && fakeargs[k][1] != '?' && fakeargs[k][1])
		{
		 	check = check_paired(&fakeargs[i][1], main->env, main->export,
				ft_strlen(&fakeargs[i][1]));
			if (check[0] != -1)
			{
				expansion = ft_split(&main->env[check[0]][find_equal(main->env[check[0]])
						+ 1], ' ');
				j = 0;
				while (expansion[j])
				{
					cmd->args[i] = ft_strdup(expansion[j]);
					i++;
					j++;
				}
			}
		}
		else
		{
			cmd->args[i] = ft_strdup(fakeargs[k]);
			i++;
		}
		free(fakeargs[k]);
		k++;
	}
}

t_cmd	*set_comands_help(int i, t_cmd *cmd2, t_cmd *begin, t_main *main)
{
	int		j;
	char	**fakeargs;

	j = 0;
	cmd2->args = ft_calloc(100, sizeof(char *));
	fakeargs = ft_split3(cmd2->argv2[i], '\3');
	check_for_expansion(cmd2, fakeargs, main);
	free(fakeargs);
	cmd2->realarg = ft_split2(cmd2->argv2[i], '\3');
	cmd2->redirection = ft_calloc(sizeof(int), count_redirections(cmd2->args));
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

	i = -1;
	begin = NULL;
	path2 = initialize_pathss(argv, &cmd2);
	while (cmd2->argv2[++i])
	{
		begin = set_comands_help(i, cmd2, begin, main);
		set_comands2(cmd2, main, path2, envp);
		cmd2 = set_comands_help2(cmd2, argv, i, begin);
	}
	cmd2->numb = 0;
	cmd = cmd2->begining;
	while (cmd)
	{
		cmd2->numb++;
		cmd = cmd->next;
	}
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
		free(argv);
		free(ar);
		return (NULL);
	}
	free(ar);
	return (set_comands(argv, envp, cmd, main));
}

// echo hello > out | cat < Makefile < infile