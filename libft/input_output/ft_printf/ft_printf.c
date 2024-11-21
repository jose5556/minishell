/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:17:03 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 03:50:07 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	call_funcs(va_list args, const char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_unsigned_putnbr(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (ft_putptr_hexa(va_arg(args, unsigned long long )));
	else if (c == 'x' || c == 'X')
		return (ft_putnbr_hexa(va_arg(args, unsigned int), c));
	else
		return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len += call_funcs(args, *str);
		}
		else
		{
			len += ft_putchar(*str);
		}
		str++;
	}
	va_end(args);
	return (len);
}
