/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:06:40 by macampos          #+#    #+#             */
/*   Updated: 2023/10/25 16:17:30 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	final_length(long int n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long int	n1;
	char		*str;
	int			len;

	n1 = n;
	len = final_length(n1);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (n1 < 0)
	{
		str[0] = '-';
		n1 = -n1;
	}
	if (n1 == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (len >= 0 && n1 > 0)
	{
		str[len] = (n1 % 10) + '0';
		n1 /= 10;
		len--;
	}
	return (str);
}
