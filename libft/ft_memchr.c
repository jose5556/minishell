/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:18:51 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/19 12:59:07 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*ptr;

	i = 0;
	a = (unsigned char)c;
	ptr = (unsigned char *)str;
	while (i < n)
	{
		if (ptr[i] == a)
			return (&ptr[i]);
		i++;
	}
	return (0);
}
