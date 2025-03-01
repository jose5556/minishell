/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:11:26 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/26 16:03:02 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_numlen(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int	len;

	len = ft_numlen(n);
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
		len++;
	}
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * (-1));
		len++;
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
	return (len);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	int	len;

	len = ft_numlen(n);
	if (n > 9)
	{
		ft_unsigned_putnbr(n / 10);
		ft_unsigned_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
	return (len);
}
