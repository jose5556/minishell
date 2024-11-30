/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:58:15 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 19:20:43 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*temp;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_memcpy(temp, ptr, size);
	free(ptr);
	return (temp);
}
