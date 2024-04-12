/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:19:40 by macampos          #+#    #+#             */
/*   Updated: 2023/10/09 17:23:32 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	count_words(char const *s, char c)
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

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr; 

	i = 0;
	j = 0;
	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (! ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
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
