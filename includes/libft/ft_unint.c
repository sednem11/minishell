/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:37:54 by macampos          #+#    #+#             */
/*   Updated: 2023/11/18 17:28:13 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unint(unsigned int c, long int *counter)
{
	if (c > 9)
	{
		ft_unint(c / 10, counter);
		ft_unint(c % 10, counter);
	}
	else
		ft_putnum(c, counter);
}
