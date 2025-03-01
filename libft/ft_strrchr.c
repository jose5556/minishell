/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:58:03 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/18 16:06:19 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int	i;
	unsigned char	a;

	i = ft_strlen((char *)str);
	a = (unsigned char)c;
	while (i > 0)
	{
		if (str[i] == a)
			return ((char *)&str[i]);
		i--;
	}
	if (str[i] == a)
		return ((char *)&str[i]);
	return (0);
}
