/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:05:09 by macampos          #+#    #+#             */
/*   Updated: 2024/09/20 15:21:07 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_value(char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

int	check_equal(char *value)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	print_dolar_helper(t_main *main, char **value)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (ft_strncmp(value[0], main->env[i], ft_strlen(value[0])) == 0
			&& main->env[i][ft_strlen(value[0])] == '='
			&& check_equal(value[0]) == -1)
			printf("%s", &main->env[i][ft_strlen(value[0]) + 1]);
		i++;
	}
}

static int	count_words4(char const *s, char c, char c2)
{
	size_t	i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 1;
	while (s[i])
	{
		if (s[i] != c && s[i] != c2 && check == 1)
		{
			j++;
			check = 0;
		}
		else if (s[i] == c || s[i] == c2)
			check = 1;
		i++;
	}
	return (j);
}

char	*word_aloc4(char const *str, char c, char c2)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = 0;
	word_len = 0;
	while (str[word_len] && str[word_len] != c && str[word_len] != c2)
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

char	**ft_split4(char const *s, char c, char c2)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc((count_words4(s, c, c2) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c || s[i] == c2)
			i++;
		if (s[i] != '\0' && s[i] != c && s[i] != c2)
		{
			ptr[j] = word_aloc4(s + i, c, c2);
			j++;
		}
		while (s[i] && s[i] != c && s[i] != c2)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

void	print_dolar(t_main *main, char *arg)
{
	int		i;
	char	**value;

	value = ft_split4(arg, '\'', ' ');
	i = 1;
	if (!arg[0] || arg[0] == ' ')
	{
		printf("$");
		free_value(value);
		return ;
	}
	if (arg[0] == '?')
	{
		printf("%i", main->status);
		while (arg[i] && arg[i] != ' ')
		{
			printf("%c", arg[i]);
			i++;
		}
	}
	else
		print_dolar_helper(main, value);
	free_value(value);
}
