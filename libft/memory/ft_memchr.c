/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:18:38 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 02:59:04 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			return ((void *)s + i);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%p\n", ft_memchr("eraumavez", 'u', 9));
	printf("%p\n", memchr("eraumavez", 'u', 9));
}*/
