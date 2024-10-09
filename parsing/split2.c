/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/10/09 16:09:25 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	count_words3(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 1;
	while (s[i])
	{
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

void	split2_help(char const *s, char c, t_split2 *spl2)
{
	while (s[spl2->i] && (s[spl2->i] == c || s[spl2->i] == '>'
			|| s[spl2->i] == '<' || spl2->flag == 1))
	{
		if (s[spl2->i] == '>' || s[spl2->i] == '<')
			spl2->flag = 1;
		else if (s[spl2->i] == c && spl2->k == 1)
			spl2->flag = 0;
		if ((s[spl2->i] == '>' || s[spl2->i] == '<')
			&& s[spl2->i + 1] != c && s[spl2->i + 1] != '>'
			&& s[spl2->i + 1] != '<')
			spl2->k = 1;
		else if ((s[spl2->i] == '>'
				|| s[spl2->i] == '<') && s[spl2->i + 1] == c)
			spl2->k = 0;
		else if (s[spl2->i] != '>' && s[spl2->i] != '<' && s[spl2->i + 1] != c)
			spl2->k = 1;
		spl2->i++;
	}
}

char	**ft_split2(char const *s, char c, t_split2 *spl2)
{
	spl2->flag = 0;
	spl2->i = 0;
	spl2->j = 0;
	spl2->ptr = ft_calloc(100, sizeof(char *));
	if (!spl2->ptr)
		return (NULL);
	while (s[spl2->i])
	{
		spl2->k = 0;
		split2_help(s, c, spl2);
		if (s[spl2->i] != '\0' && s[spl2->i] != c)
		{
			spl2->ptr[spl2->j] = word_aloc(s + spl2->i, c);
			spl2->j++;
		}
		while (s[spl2->i] && s[spl2->i] != c)
			spl2->i++;
	}
	return (spl2->ptr);
}

char	**ft_split3(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc((count_words3(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			ptr[j] = word_aloc3(s + i, c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
