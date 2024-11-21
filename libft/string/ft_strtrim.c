/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:57:41 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 03:00:00 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		j;

	if (ft_strlen(set) == 0 || ft_strlen(s1) == 0 || !set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		++i;
	while (s1[j] && ft_strrchr(set, s1[j]))
		--j;
	result = ft_substr(s1, i, j - i + 1);
	if (!result)
	{
		return (ft_strdup(""));
	}
	return (result);
}

/* int	main(void)
{
	char	s1[50] = "abccba";
	printf("%s\n", ft_strtrim(s1, "abc"));
}*/