/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:39:27 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/28 15:04:16 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_hex_array(unsigned long n)
{
	char	*str;
	int		i;
	int		remainder;

	i = ft_len(n);
	str = malloc(i + 1);
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[i] = '0';
	while (n != 0)
	{
		remainder = n % 16;
		if (remainder < 10)
			str[i] = remainder + '0';
		else
			str[i] = (remainder - 10) + 'a';
		i--;
		n /= 16;
	}
	return (str);
}
