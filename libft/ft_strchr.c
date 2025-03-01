/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:52:23 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/09 11:17:20 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	unsigned char	a;

	i = 0;
	a = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == a)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == a)
		return ((char *)&str[i]);
	return (0);
}
