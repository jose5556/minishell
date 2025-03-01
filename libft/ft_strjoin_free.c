/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:25:10 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 17:31:17 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	if (i == 1 && s1)
		free(s1);
	else if (i == 2 && s2)
		free(s2);
	else
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		s1 = NULL;
		s2 = NULL;
	}
	return (temp);
}
