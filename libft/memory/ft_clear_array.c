/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:11:49 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 10:14:27 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_clear_array(char ***array)
{
	int	i;

	i = 0;
	while (*(array[i]))
	{
		free(*(array[i]));
		i++;
	}
	free(*array);
	*array = NULL;
}
