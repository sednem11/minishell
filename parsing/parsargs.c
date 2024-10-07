/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/10/07 09:04:59 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_updated(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '$' && line[i] != ' ')
	{
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
			return(1);
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

int	check_aspas(char *user_input, int k)
{
	int	i;
	int	j;
	int	check;
	int	check2;

	check2 = 0;
	check = 0;
	j = 0;
	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '"' && check == 0 && check2 == 0)
			check2 = 1;
		else if (user_input[i] == '"' && check == 0 && check2 == 1)
			check2 = 0;
		if ((user_input[i] == '"' || user_input[i] == ' '
				|| user_input[i] == '\'') && check == 1 && check2 == 0)
			check = 0;
		else if ((user_input[i] == '"' || user_input[i] == ' '
				|| user_input[i] == '\'') && check == 0 && check2 == 0)
		{
			j++;
			while (user_input[i] == '"' || user_input[i] == ' '
				|| user_input[i] == '\'')
			{
				if (user_input[i] == '"')
					break ;
				if (user_input[i] == '\'' && j == k && check2 == 0)
				{
					return (1);
				}
				i++;
				check = 1;
			}
		}
		i++;
	}
	return (0);
}

char	**get_expansion2(t_main *main, char *fakeargs, int *check)
{
	char	**expansion;
	char	**new;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	new = calloc(sizeof(char *), 100);
	while (fakeargs[i])
	{
		j = 0;
		if (fakeargs[i] == ' ')
			new[k] = ft_strjoin(new[k], " ");
		if (fakeargs[i] == '$')
		{
			check = check_paired(&fakeargs[i + 1], main->env, main->export,
					ft_strlen_updated(&fakeargs[i + 1]));
			if (check[0] != -1)
			{
				expansion = ft_split(&main->env[check[0]][find_equal(main->env[check[0]])
						+ 1], ' ');
				while (expansion[j])
				{
					if (!new[k])
						new[k] = ft_strdup(expansion[j]);
					else
						new[k] = ft_strjoin(new[k], expansion[j]);
					free(expansion[j]);
					if (!fakeargs[i + 1] || expansion[j + 1])
						k++;
					j++;
				}
				free(expansion);
			}
			free(check);
		}
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
	k = 0;
	cmd->valid_arg_for_redirection = ft_calloc(100, sizeof(int));
	while (fakeargs[k])
	{
		if (ft_strncmp(fakeargs[k], "$", 1) == 0 && fakeargs[k][1] != '?'
			&& fakeargs[k][1] && check_aspas(main->user_input, k) == 0
			&& (k - 1 == -1 || cmd->args[k - 1][0] != '<')
			&& (k - 1 == -1 || cmd->args[k - 1][1] != '<')
			&& (k - 1 == -1 || !cmd->args[k - 1][2]))
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
	while(user_input[i])
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
				if (user_input[j] != ' ' && user_input[j] != '<' && user_input[j] != '>')
					break;
				j++;
			}
			if (!user_input[j])
				return(2);
		}
		if ((user_input[i] == '<' || user_input[i] == '>') && flag == 0)
		{
			if ((user_input[i] == '<' || user_input[i] == '>')
				&& (user_input[i + 1] == '<' || user_input[i + 1] == '>')
				&& (user_input[i + 2] == '<' || user_input[i + 2] == '>'))
					return(2);
			if (user_input[i + 1] != '<' && user_input[i] == '<' && user_input[i + 1] != ' ')
			{
				if (user_input[i + 1] <= 65 && user_input[i + 1] >= 91 && user_input[i + 1] <= 96 && user_input[i + 1] >= 123)
					return(1);
			}
			if (user_input[i + 1] != '>' && user_input[i] == '>' && user_input[i + 1] != ' ')
			{
				if (user_input[i + 1] <= 65 && user_input[i + 1] >= 91 && user_input[i + 1] <= 96 && user_input[i + 1] >= 123)
					return(1);
			}
		}
		i++;
	}
	return(0);
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
