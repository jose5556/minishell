/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:43:14 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/28 15:46:53 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_toupper_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;
		i++;
	}
	return (str);
}

int	ft_puthex(unsigned int n, int upper)
{
	char	*str;
	int		len;

	len = ft_len(n);
	str = ft_hex_array(n);
	if (upper)
		ft_putstr(ft_toupper_string(str));
	else
		ft_putstr(str);
	free(str);
	return (len);
}
