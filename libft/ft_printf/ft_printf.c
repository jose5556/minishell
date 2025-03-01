/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:02:45 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/28 15:30:46 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		print_len;
	va_list	args;

	i = 0;
	print_len = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			print_len += write(1, &str[i], 1);
		}
		else
		{
			i++;
			print_len += ft_typefinder(str[i], args);
		}
		i++;
	}
	va_end(args);
	return (print_len);
}
