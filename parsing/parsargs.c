/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 18:54:14 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_expansion4(t_main *main, char **new, int i, int k, char *fakeargs)
{
	int		*check;
	char	**expansion;
	int		j;

	j = 0;
	check = check_paired(&fakeargs[i + 1], main->env, main->export,
			ft_strlen_updated(&fakeargs[i + 1]));
	if (check[0] != -1)
	{
		expansion = ft_split(&main->env[check[0]]
			[find_equal(main->env[check[0]])
				+ 1], ' ');
		while (expansion[j])
		{
			get_expansion3(new, expansion, k, j);
			if (!fakeargs[i + 1] || expansion[j + 1])
				k++;
			j++;
		}
		free(expansion);
	}
	free(check);
	return (k);
}

char	**get_expansion2(t_main *main, char *fakeargs, int *check)
{
	char	**new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	(void)check;
	new = calloc(sizeof(char *), 100);
	while (fakeargs[i])
	{
		if (fakeargs[i] == ' ')
			new[k] = ft_strjoin(new[k], " ");
		if (fakeargs[i] == '$')
			k = get_expansion4(main, new, i, k, fakeargs);
		i++;
	}
	return (new);
}

void	get_expansion(t_main *main, t_cmd *cmd, char *fakeargs, int i)
{
	char	**expansion;
	int		j;
	int		*check;

	check = check_paired2(&fakeargs[1], main->env, main->export,
			ft_strlen_updated(&fakeargs[1]));
	if (check[0] != -1)
	{
		expansion = get_expansion2(main, fakeargs, check);
		j = 0;
		while (expansion[j])
		{
			cmd->args[arg_len(cmd->args)] = ft_strdup(expansion[j]);
			free(expansion[j]);
			i++;
			j++;
		}
		free(expansion);
	}
	free(check);
}

void	check_for_expansion(t_cmd *cmd, char **fakeargs, t_main *main)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	cmd->valid_arg_for_redirection = ft_calloc(100, sizeof(int));
	while (fakeargs[++k])
	{
		if (ft_strncmp(fakeargs[k], "$", 1) == 0 && fakeargs[k][1] != '?'
			&& fakeargs[k][1] && check_aspas(main->user_input, k, NULL) == 0
			&& (k - 1 == -1 || cmd->args[k - 1][0] != '<') && (k - 1 == -1
				|| cmd->args[k - 1][1] != '<') && (k - 1 == -1
				|| !cmd->args[k - 1][2]))
			get_expansion(main, cmd, fakeargs[k], i);
		else
		{
			cmd->args[arg_len(cmd->args)] = ft_strdup(fakeargs[k]);
			i++;
		}
		if (check_aspas2(main->user_input, k) == 1)
			cmd->valid_arg_for_redirection[k] = -1;
		else
			cmd->valid_arg_for_redirection[k] = 1;
		free(fakeargs[k]);
	}
}

t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	t_ar	*ar;
	char	*argv;

	(void)envp;
	ar = malloc(sizeof(t_ar));
	ar->j = 0;
	ar->i = 0;
	ar->flag = -1;
	argv = ft_calloc(sizeof(char), ft_strlen(user_input) + 1);
	while (user_input[ar->i])
	{
		if (check_args2(user_input) == 1 || check_args2(user_input) == 2)
		{
			if (check_args2(user_input) == 1)
				printf(" unexpected token\n");
			else
				printf(" sintax error\n");
			free(ar);
			free(argv);
			return (NULL);
		}
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
	return (set_comands(argv, cmd, main));
}
