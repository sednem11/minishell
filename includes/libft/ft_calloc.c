/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:53:47 by macampos          #+#    #+#             */
/*   Updated: 2023/10/03 20:12:27 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	n;

	n = count * size;
	ptr = (char *)malloc(n);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n);
	return (ptr);
}
