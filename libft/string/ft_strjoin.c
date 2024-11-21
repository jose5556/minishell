/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:34:14 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 02:59:39 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 && !s2)
		ft_strdup("");
	result = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (result);
	i = 0;
	j = 0;
	while (s1[j])
	{
		result[i] = ((char *)s1)[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
		result[i++] = ((char *)s2)[j++];
	result[i] = 0;
	return (result);
}

/* int	main(void)
{
	char	s1[4] = "";
	char	s2[4] = "5";

	printf("%s", ft_strjoin(s1, s2));
} */
