/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:17:51 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 04:12:03 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

double	ft_atoi_double(const char *nptr)
{
	long	result;
	double	sign;
	double	pow;
	double	fractional_part;

	fractional_part = 0;
	result = 0;
	sign = 1;
	pow = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		result = (result * 10) + (*nptr++ - '0');
	if (*nptr == '.')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		pow /= 10;
		fractional_part = fractional_part + (*nptr++ - '0') * pow;
	}
	return ((result + fractional_part) * sign);
}
