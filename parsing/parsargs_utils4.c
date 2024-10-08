/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:00:05 by macampos          #+#    #+#             */
/*   Updated: 2024/10/08 17:06:07 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_expansion3(char **new, char **expansion, int k, int j)
{
	if (!new[k])
		new[k] = ft_strdup(expansion[j]);
	else
		new[k] = ft_strjoin(new[k], expansion[j]);
	free(expansion[j]);
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

t_cmd	*set_comands(char *argv, t_cmd *cmd, t_main *main)
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
		set_comands2(cmd2, main, path2, main->env);
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
	if (cmd2->begining == NULL)
	{
		free(cmd2->argv2);
		free(cmd2);
		return (NULL);
	}
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
	else if (ar->flag == -1 && (user_input[ar->i] == ' '
			|| user_input[ar->i] == '\t'))
		argv[ar->i] = '\3';
	else if ((ar->flag == -1 && (user_input[ar->i] == '"'
				|| user_input[ar->i] == 39)) || ((user_input[ar->i] == '"'
				|| user_input[ar->i] == 39) && ar->j == ar->i))
		argv[ar->i] = '\5';
	else if ((ar->flag == -1 && user_input[ar->i] != ' ') || ar->flag == 1)
		argv[ar->i] = user_input[ar->i];
}

int	check_args2(char *user_input)
{
	int	i;
	int	flag;
	int	j;

	flag = 0;
	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '\"' && flag == 0)
			flag = 1;
		else if (user_input[i] == '\"' && flag == 1)
			flag = 0;
		if ((user_input[i] == '<' || user_input[i] == '>') && flag == 0)
		{
			j = i + 1;
			while (user_input[j])
			{
				if (user_input[j] != ' ' && user_input[j] != '<'
					&& user_input[j] != '>' && user_input[j] != '\t'
					&& user_input[j] != '|')
					break ;
				j++;
			}
			if (!user_input[j])
				return (2);
		}
		if ((user_input[i] == '<' || user_input[i] == '>') && flag == 0)
		{
			if ((user_input[i] == '<' || user_input[i] == '>')
				&& (user_input[i + 1] == '<'
					|| user_input[i + 1] == '>') && (user_input[i + 2] == '<'
					|| user_input[i + 2] == '>'))
				return (2);
			if (user_input[i + 1] != '<' && user_input[i] == '<'
				&& user_input[i + 1] != ' ' && user_input[i + 1] != '\t')
			{
				if ((user_input[i + 1] <= 65 && user_input[i + 1] >= 91
						&& user_input[i + 1] <= 96 && user_input[i + 1] >= 123)
					|| user_input[i + 1] == '|')
					return (1);
			}
			if (user_input[i + 1] != '>' && user_input[i] == '>'
				&& user_input[i + 1] != ' ' && user_input[i + 1] != '\t')
			{
				if ((user_input[i + 1] <= 65 && user_input[i + 1] >= 91
						&& user_input[i + 1] <= 96 && user_input[i + 1] >= 123)
					|| user_input[i + 1] == '|')
					return (1);
			}
		}
		i++;
	}
	return (0);
}
