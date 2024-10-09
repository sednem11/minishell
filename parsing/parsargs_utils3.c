/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:53:13 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 18:49:44 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_updated(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i] != '\0' && line[i] != '$' && line[i] != ' ')
			i++;
	}
	return (i);
}

int	arg_len(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

int	check_aspas2(char *user_input, int k)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	j = 0;
	i = 0;
	while (user_input[i])
	{
		if (j == k && user_input[i] == '"' && check == 0)
			return (1);
		if (user_input[i] == '"' && check == 0)
			check = 1;
		else if (user_input[i] == '"' && check == 1)
			check = 0;
		if ((user_input[i] == ' ' || user_input[i] == '\'') && check == 0)
			j++;
		i++;
	}
	return (0);
}

int	check_aspas(char *user_input, int k, t_aspas *asp)
{
	asp = malloc(sizeof(t_aspas));
	asp->check2 = 0;
	asp->check = 0;
	asp->j = 0;
	asp->i = 0;
	while (user_input[asp->i])
	{
		if (user_input[asp->i] == '"' && asp->check == 0 && asp->check2 == 0)
			asp->check2 = 1;
		else if (user_input[asp->i] == '"' && asp->check == 0
			&& asp->check2 == 1)
			asp->check2 = 0;
		if ((user_input[asp->i] == '"' || user_input[asp->i] == ' '
				|| user_input[asp->i] == '\'') && asp->check == 1
			&& asp->check2 == 0)
			asp->check = 0;
		else if ((user_input[asp->i] == '"' || user_input[asp->i] == ' '
				|| user_input[asp->i] == '\'') && asp->check == 0
			&& asp->check2 == 0 && aspas_help(user_input, k, asp) == 1)
			return (1);
		asp->i++;
	}
	free(asp);
	return (0);
}

t_cmd	*set_comands_help(int i, t_cmd *cmd2, t_cmd *begin, t_main *main)
{
	int			j;
	char		**fakeargs;
	t_split2	*spl2;

	spl2 = malloc(sizeof(t_split2));
	j = 0;
	cmd2->args = ft_calloc(100, sizeof(char *));
	fakeargs = ft_split3(cmd2->argv2[i], '\3');
	check_for_expansion(cmd2, fakeargs, main);
	free(fakeargs);
	cmd2->realarg = ft_split2(cmd2->argv2[i], '\3', spl2);
	free(spl2);
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
