/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:31:35 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/07 17:22:43 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;
	size_t	i;

	i = 0;
	memory = malloc(nmemb * size);
	if (memory == NULL)
		return (0);
	while (i < nmemb * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
