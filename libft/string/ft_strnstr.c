/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:38:22 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 02:59:55 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		if (!(ft_strncmp(big, little, i)) && len >= i)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

/* int	main(void)
{
	printf("%s", ft_strnstr("dfgdfgabcddddd", "abcd", 13));
} */