/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:39:32 by macampos          #+#    #+#             */
/*   Updated: 2023/10/08 19:04:18 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *str, unsigned int start, size_t length)
{
	char	*str1;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(str))
		length = 0;
	else if (start + length >= ft_strlen(str))
		length = ft_strlen(str) - start;
	str1 = (char *)malloc(sizeof(char) * (length + 1));
	if (!str1)
		return (NULL);
	while (i < length)
	{
		str1[i++] = str[start++];
	}
	str1[i] = '\0';
	return (str1);
}
