/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:58:05 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:16 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_main2_help2(t_main *mainn, int *place, char **envp, char *exported)
{
	int		j;

	j = 0;
	while (envp[j])
	{
		if (j != place[0] || find_equal(exported) < 0)
			mainn->env[j] = envp[j];
		else if (j == place[0] && find_equal(exported) > 0)
		{
			free(envp[j]);
			mainn->env[j] = ft_strdup(exported);
		}
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)
		mainn->env[j] = ft_strdup(exported);
}

int	check_args2_help(char *user_input, int i)
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
	return (0);
}

int	check_args2_help2(char *user_input, int i, int j)
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
	return (0);
}

void	set_comands_help3(t_cmd *cmd2, char *argv, t_cmd *cmd, char **path2)
{
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
}

int	aspas_help(char *user_input, int k, t_aspas *asp)
{
	asp->j++;
	while (user_input[asp->i] == '"' || user_input[asp->i] == ' '
		|| user_input[asp->i] == '\'')
	{
		if (user_input[asp->i] == '"')
			break ;
		if (user_input[asp->i] == '\'' && asp->j == k && asp->check2 == 0)
		{
			free(asp);
			return (1);
		}
		asp->i++;
		asp->check = 1;
	}
	return (0);
}
