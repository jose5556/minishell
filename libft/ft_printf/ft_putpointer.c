/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:29:33 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/28 15:47:26 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putpointer(unsigned long ptr)
{
	char	*str;
	int		len;

	len = ft_len(ptr);
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putstr("0x");
	str = ft_hex_array(ptr);
	ft_putstr(str);
	free(str);
	return (len + 2);
}
