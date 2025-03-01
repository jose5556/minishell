/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:41:13 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/19 13:37:59 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*s2;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (i <= len && ft_strchr(set, s1[i]))
		i++;
	if (i > len)
		return (ft_strdup(s1 + len + 1));
	while (ft_strchr(set, s1[len]) && len >= 0)
		len--;
	s2 = malloc(len - i + 2);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1[i], len - i + 2);
	return (s2);
}
