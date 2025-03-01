/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:18:27 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/19 15:02:25 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (little[i] != '\0' && len > 0)
	{
		if (little[i] != big[i])
			return (0);
		i++;
		len--;
	}
	if (little[i] != '\0' && len == 0)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && len > 0)
	{
		if (little[0] == big[i] && compare(&big[i], little, len) == 1)
		{
			return ((char *)&big[i]);
		}
		i++;
		len--;
	}
	return (0);
}
