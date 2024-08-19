/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/08/19 22:01:31 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0],
			"export", 6) == 0 || ft_strncmp(cmd->args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->args[0], "env", 3) == 0 || ft_strncmp(cmd->args[0],
			"exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (0);
	else
		return (1);
}

int	check_last(t_main *main)
{
	int	i;
	int	n;
	int	z;

	n = 0;
	i = 0;
	while (main->export[i])
	{
		if (ft_strlen_upd(main->export[i]) > ft_strlen_upd(main->export[n]))
			z = ft_strlen_upd(main->export[n]);
		else
			z = ft_strlen_upd(main->export[i]);
		if (ft_strncmp(main->export[i], main -> export[n], z) > 0)
			n = i;
		i++;
	}
	return (n);
}

void	print_export(t_main *main)
{
	int	i;
	int	n;
	int	z;
	int	a;
	int	c;

	a = 0;
	c = 0;
	while (matrixlen(main->export) > a + 1)
	{
		n = check_last(main);
		i = 0;
		while (main->export[i])
		{
			if (ft_strlen_upd(main->export[i]) > ft_strlen_upd(main->export[n]))
				z = ft_strlen_upd(main->export[n]);
			else
				z = ft_strlen_upd(main->export[i]);
			if (ft_strncmp(main->export[i], main -> export[n], z) < 0 && a == 0)
				n = i;
			else if (a > 0 && ft_strncmp(main->export[i], main -> export[c],
					ft_strlen_upd(main->export[i])) > 0)
			{
				if (ft_strncmp(main->export[i], main -> export[n], z) < 0)
					n = i;
				else if (ft_strncmp(main->export[i], main -> export[n], z) == 0
					&& ft_strlen_upd(main->export[i])
					!= ft_strlen_upd(main->export[n]))
					n = i;
			}
			i++;
		}
		printf("declare -x %s\n", main->export[n]);
		c = n;
		a++;
	}
}

char	*word_aloc3(char const *str, char c)
{
	char	*word;
	t_split	split;
	int		i;

	i = 0;
	split.ctd = 0;
	split.ctd2 = 0;
	split.word_len = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] != '\5')
			split.word_len++;
		i++;
	}
	word = (char *)malloc(split.word_len + 1);
	while (split.ctd < split.word_len)
	{
		while (str[split.ctd2] == '\5')
			split.ctd2++;
		word[split.ctd] = str[split.ctd2];
		split.ctd2++;
		split.ctd++;
	}
	word[split.ctd] = '\0';
	return (word);
}
