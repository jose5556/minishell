/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:58:15 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 21:20:26 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*temp;
	char	*old_ptr;
	size_t	i;

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
	old_ptr = (char *)ptr;
	i = 0;
	while (i < size)
	{
		temp[i] = old_ptr[i];
		i++;
	}
	free(ptr);
	return (temp);
}
