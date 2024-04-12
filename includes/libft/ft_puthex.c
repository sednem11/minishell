/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:04:54 by macampos          #+#    #+#             */
/*   Updated: 2023/11/18 17:28:43 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex(unsigned long int c, long int *counter, int p, int caps)
{
	if (!c && p == 0)
	{
		ft_putstr("(nil)", counter);
		return ;
	}
	if (p == 0)
		ft_putstr("0x", counter);
	if (c >= 16)
		ft_puthex(c / 16, counter, ++p, caps);
	if (caps)
		ft_putchar(HEX_UPP_BASE[c % 16], counter);
	else
		ft_putchar(HEX_LOW_BASE[c % 16], counter);
}
