/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:29:23 by joseoliv          #+#    #+#             */
/*   Updated: 2024/10/11 02:59:02 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

/* int		main(void)
{
	int	i;
	i = 0;

	char	*str = (char*) ft_calloc(0, sizeof(char));
	char    *strr = (char*) calloc(0, sizeof(char));
	
	while (i < 10 * sizeof(char))
	{
		str[i] = 'a';
		i++;
	}
	printf("%zu\n", ft_strlen(str));
	i = 0;
	while (i < 10 * sizeof(char))
        {
            strr[i] = 'a';
            i++;
        }
	printf("%zu\n", ft_strlen(strr));
} */