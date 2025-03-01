/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_expander_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:08 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:04 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_home_directory_token(t_list *tmp)
{
	char	*value;

	value = get_token_content(tmp)->value;
	if (!ft_strcmp("~", value) || !ft_strncmp("~/", value, 2))
		return (true);
	if (!ft_strcmp("~+", value) || !ft_strncmp("~+/", value, 3))
		return (true);
	if (!ft_strcmp("~-", value) || !ft_strncmp("~-/", value, 3))
		return (true);
	return (false);
}
