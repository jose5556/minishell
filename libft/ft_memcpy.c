/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:00:23 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/19 12:33:49 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*target;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)src;
	target = (unsigned char *)dest;
	if (ptr == 0 && target == 0)
		return (0);
	while (i < n)
	{
		target[i] = ptr[i];
		i++;
	}
	return (dest);
}
