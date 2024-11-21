/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:31:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 02:59:15 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*src1;

	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (!dest1 && !src1)
		return (NULL);
	if (dest < src)
	{
		return (ft_memcpy(dest1, src1, n));
	}
	else
	{
		while (n--)
			((char *)dest1)[n] = ((char *)src1)[n];
	}
	return (dest1);
}

/* int	main(void)
{
    char    dest[] = "eraumavez";

    ft_memmove(dest, dest + 2, 9);
	//memmove(dest, dest + 2, 9);
    printf("%s\n", dest);
} */