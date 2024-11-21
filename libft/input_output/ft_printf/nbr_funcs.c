/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:14:42 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 03:50:15 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_hexa(unsigned long long n, char upper)
{
	char	*hexa_nums;
	char	result;
	int		len;

	hexa_nums = ft_strdup("0123456789abcdef");
	len = count_unsigned(n);
	if (n >= 16)
		ft_putnbr_hexa(n / 16, upper);
	if (upper == 'x')
		ft_putchar(hexa_nums[n % 16]);
	else
	{
		result = hexa_nums[n % 16];
		ft_putchar(ft_toupper(result));
	}
	free(hexa_nums);
	return (len);
}

int	ft_putnbr(int n)
{
	int	len;

	if (n == -2147483648)
	{
		len = ft_putstr("-2147483648");
		return (len);
	}
	len = count(n, 10);
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + 48);
	return (len);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	int	len;

	len = count(n, 10);
	if (n > 9)
		ft_unsigned_putnbr(n / 10);
	ft_putchar(n % 10 + 48);
	return (len);
}

int	ft_putptr_hexa(unsigned long long n)
{
	int	len;

	if (n == 0)
	{
		len = ft_putstr("(nil)");
		return (len);
	}
	else
	{
		len = ft_putstr("0x");
		len += ft_putnbr_hexa(n, 'x');
	}
	return (len);
}
