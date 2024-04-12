/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:04:43 by macampos          #+#    #+#             */
/*   Updated: 2023/11/18 17:30:00 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check(char *str, va_list args, int i, long int *char_ttl)
{
	if (str[i] == 'c')
		ft_putchar(va_arg(args, int), char_ttl);
	else if (str[i] == 'd' || str[i] == 'i')
		ft_putnum(va_arg(args, long int), char_ttl);
	else if (str[i] == 's')
		ft_putstr(va_arg(args, char *), char_ttl);
	else if (str[i] == 'x')
		ft_puthex(va_arg(args, unsigned int), char_ttl, 1, 0);
	else if (str[i] == 'X')
		ft_puthex(va_arg(args, unsigned int), char_ttl, 1, 1);
	else if (str[i] == 'u')
		ft_unint(va_arg(args, unsigned int), char_ttl);
	else if (str[i] == 'p')
		ft_puthex(va_arg(args, unsigned long int), char_ttl, 0, 0);
	else if (str[i] == '%')
		ft_putchar('%', char_ttl);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	long int	i;
	long int	char_ttl;

	i = 0;
	char_ttl = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			ft_check((char *)format, args, ++i, &char_ttl);
		else
			ft_putchar(format[i], &char_ttl);
		i++;
	}
	va_end(args);
	return (char_ttl);
}
