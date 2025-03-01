/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:12:22 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/07 11:26:40 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	return_val(char *dst, const char *src, size_t size)
{
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	else
		return (ft_strlen(src) + ft_strlen(dst));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	output;

	i = 0;
	j = 0;
	output = return_val(dst, src, size);
	while (dst[i] && size > 0)
	{
		i++;
		size--;
	}
	while (src[j] && size > 1)
	{
		dst[i] = src[j];
		i++;
		j++;
		size--;
	}
	if (size > 0)
		dst[i] = '\0';
	return (output);
}
