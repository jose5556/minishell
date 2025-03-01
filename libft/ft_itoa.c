/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:21:44 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/19 15:01:09 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (2);
	if (n > 0)
		i++;
	else
		i += 2;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*fill_str(char *str, int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		if (n >= 0)
			str[i] = (n % 10) + '0';
		else if (n < 0)
			str[i] = (n % 10 * (-1)) + '0';
		n /= 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	*reverse_string(char *str)
{
	int	i;
	int	len;
	int	mid;

	i = 0;
	len = ft_strlen(str) - 1;
	mid = len / 2;
	while (i <= mid)
	{
		swap(&str[i], &str[len]);
		i++;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;

	digits = get_digits(n);
	str = malloc(digits);
	if (!str)
		return (0);
	if (n > 0)
	{
		fill_str(str, n);
		reverse_string(str);
	}
	else if (n < 0)
	{
		str[0] = '-';
		fill_str(&str[1], n);
		reverse_string(&str[1]);
	}
	else
	{
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}
