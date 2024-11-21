/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:11:52 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 03:00:10 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*fill_str_ng(int n, int len, char *result);
static char	*fill_str_ps(int n, int len, char *result);
static int	count_num(int n);

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		len += count_num(n) + 1;
		result = (char *) malloc((len + 1) * sizeof(char));
		if (!result)
			return (result);
		result = fill_str_ng(n, len - 1, result);
	}
	else
	{
		len = count_num(n);
		result = (char *) malloc((len + 1) * sizeof(char));
		if (!result)
			return (result);
		result = fill_str_ps(n, len, result);
	}
	result[len] = '\0';
	return (result);
}

static int	count_num(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*fill_str_ps(int n, int len, char *result)
{
	len--;
	while (len >= 0)
	{
		result[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (result);
}

static char	*fill_str_ng(int n, int len, char *result)
{
	while (len > 0)
	{
		result[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	result[0] = '-';
	return (result);
}
/*
int		main(void)
{

	char *str;

	str = NULL;
	str = ft_itoa(-445);
	printf("%s", str);
	free(str);
}  
*/