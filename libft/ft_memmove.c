/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:05 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/07 15:03:48 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memmove_forward(void *dest, const void *src, size_t n)
{
	unsigned char	*target;
	unsigned char	*ptr;
	size_t			i;

	target = (unsigned char *)dest;
	ptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		target[i] = ptr[i];
		i++;
	}
	return (target);
}

static void	*ft_memmove_backwards(void *dest, const void *src, size_t n)
{
	unsigned char	*target;
	unsigned char	*ptr;

	target = (unsigned char *)dest;
	ptr = (unsigned char *)src;
	if (n > 0)
		n -= 1;
	while (n > 0)
	{
		target[n] = ptr[n];
		n--;
	}
	target[n] = ptr[n];
	return (target);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == 0 && src == 0)
		return (0);
	if (n == 0)
		return (dest);
	if (src > dest && src < dest + n)
	{
		ft_memmove_forward(dest, src, n);
	}
	else
	{
		ft_memmove_backwards(dest, src, n);
	}
	return (dest);
}
