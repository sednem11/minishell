/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:22:12 by macampos          #+#    #+#             */
/*   Updated: 2023/10/08 16:04:46 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t length)
{
	size_t	i;
	size_t	j;

	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < length)
	{
		j = 0;
		while (s1[i + j] && s2[j] && j + i < length && s1[i + j] == s2[j])
		{
			j++;
		}
		if (!s2[j])
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s", strnstr("hello how are", "how", 6));
}
*/