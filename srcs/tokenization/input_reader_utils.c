/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:37:58 by joseoliv          #+#    #+#             */
/*   Updated: 2025/02/02 12:01:53 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ends_with_single_pipe(const char *input)
{
	int	len;

	if (!input)
		return (false);
	len = ft_strlen(input) - 1;
	if (len < 0)
		return (false);
	if (len == 0 && input[len] == '|')
		return (false);
	while (len >= 0 && (input[len] == ' ' || input[len] == '\t'))
		len--;
	if (len >= 0 && input[len] == '|')
		return (true);
	return (false);
}
