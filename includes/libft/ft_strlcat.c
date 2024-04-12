/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:59:59 by macampos          #+#    #+#             */
/*   Updated: 2023/10/03 19:14:24 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	size_t	dest_len;

	dest_len = ft_strlen(dst);
	j = dest_len;
	i = 0;
	if (dest_len < (size - 1) && size > 0)
	{
		while (src[i] && (dest_len + i) < (size - 1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + ft_strlen(src));
}
