/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:33:18 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 10:55:55 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
