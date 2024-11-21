/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:53:17 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 03:39:58 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_special(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	result = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (result);
	i = 0;
	j = 0;
	while (s1[j])
		result[i++] = ((char *)s1)[j++];
	j = 0;
	while (s2[j])
		result[i++] = ((char *)s2)[j++];
	result[i] = 0;
	return (result);
}

char	*ft_strjoin_free_special(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin_special(s1, s2);
	free(s1);
	return (temp);
}
