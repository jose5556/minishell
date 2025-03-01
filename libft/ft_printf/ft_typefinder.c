/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typefinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:56:10 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/26 16:41:43 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_typefinder(char c, va_list args)
{
	int	print_len;

	print_len = 0;
	if (c == 'c')
		print_len += (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		print_len += (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		print_len += (ft_putpointer(va_arg(args, unsigned long)));
	else if (c == 'i' || c == 'd')
		print_len += (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		print_len += (ft_unsigned_putnbr(va_arg(args, unsigned int)));
	else if (c == 'x')
		print_len += (ft_puthex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		print_len += (ft_puthex(va_arg(args, unsigned int), 1));
	else if (c == '%')
		print_len += (ft_putchar('%'));
	return (print_len);
}
