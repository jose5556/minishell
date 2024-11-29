/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:33:18 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/29 00:07:22 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char	*temp;

	if (!s1 || !s2)
        return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
        return (NULL);
	if (i == 1)
		free(s1);
	else if (i == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (temp);
}
