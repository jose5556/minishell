/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:19:30 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/09 10:58:18 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	void	*ptr_strjoin;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr_strjoin = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr_strjoin)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		((char *)ptr_strjoin)[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		((char *)ptr_strjoin)[i++] = s2[j++];
	}
	((char *)ptr_strjoin)[i] = '\0';
	return ((char *)ptr_strjoin);
}
