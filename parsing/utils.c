/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/06/27 16:25:47 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
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
		if (ft_strlen_updated(main->export[i]) > ft_strlen_updated(main->export[n]))
			z = ft_strlen_updated(main->export[n]);
		else
			z = ft_strlen_updated(main->export[i]);
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
			if (ft_strlen_updated(main->export[i]) > ft_strlen_updated(main->export[n]))
				z = ft_strlen_updated(main->export[n]);
			else
				z = ft_strlen_updated(main->export[i]);
			if (ft_strncmp(main->export[i], main -> export[n], z) < 0 && a == 0)
				n = i;
			else if (a > 0 && ft_strncmp(main->export[i], main -> export[c],
					ft_strlen_updated(main->export[i])) > 0)
			{
				if (ft_strncmp(main->export[i], main -> export[n], z) < 0)
					n = i;
				else if (ft_strncmp(main->export[i], main -> export[n], z) == 0
					&& ft_strlen_updated(main->export[i]) != ft_strlen_updated(main->export[n]))
					n = i;
			}
			i++;
		}
		printf("declare -x %s\n", main->export[n]);
		c = n;
		a++;
	}
}

static char	*word_aloc(char const *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = 0;
	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	while (ctd < word_len)
	{
		word[ctd] = str[ctd];
		ctd++;
	}
	word[ctd] = '\0';
	return (word);
}

static int	count_words2(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 1;
	while (s[i])
	{
		if ((s[i] == '>' || s[i] == '<') && check == 1)
			return (j);
		if (s[i] != c && check == 1)
		{
			j++;
			check = 0;
		}
		else if (s[i] == c)
			check = 1;
		i++;
	}
	return (j);
}

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc((count_words2(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '>' || s[i] == '<')
			break ;
		if (s[i] != '\0' && s[i] != c)
		{
			ptr[j] = word_aloc(s + i, c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
