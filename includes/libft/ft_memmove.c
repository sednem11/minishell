/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:38:30 by macampos          #+#    #+#             */
/*   Updated: 2023/10/08 15:50:43 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!src && !dst)
		return (NULL);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	while (n-- > 0)
	{
		((char *)dst)[n] = ((char *)src)[n];
	}
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
	char *str = ft_memmove("hello world", "sup bitches", 5);
	if (str == NULL)
		printf("str is null\n");
	printf("sucessful memmove, string is %s\n", str);
}
*/
