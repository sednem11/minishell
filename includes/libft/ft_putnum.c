/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:48:32 by macampos          #+#    #+#             */
/*   Updated: 2023/11/18 17:28:31 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnum(int c, long int *counter)
{
	if (c == -2147483648)
	{
		ft_putstr("-2147483648", counter);
		return ;
	}
	if (c < 0)
	{
		ft_putchar('-', counter);
		c = -c;
	}
	if (c > 9)
	{
		ft_putnum(c / 10, counter);
		ft_putnum(c % 10, counter);
	}
	else
		ft_putchar(c + '0', counter);
}
