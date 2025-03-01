/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:48:04 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/09 09:12:09 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	copy(char const *s, char *d, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			d[j] = s[i];
			j++;
		}
		i++;
	}
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;
	size_t	j;

	j = 0;
	size = ft_strlen(s);
	if (start >= size)
		dest = malloc(1);
	else if (len < (size - start))
		dest = malloc(len + 1);
	else
		dest = malloc(size - start + 1);
	if (!dest)
		return (0);
	if (start < size)
		j = copy(s, dest, start, len);
	dest[j] = '\0';
	return (dest);
}
