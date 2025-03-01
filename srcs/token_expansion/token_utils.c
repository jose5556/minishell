/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:54 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:20 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_until_dollar(char *str, int *i)
{
	int		start_index;
	char	*substr;

	start_index = *i;
	if (str[*i] == '\0')
		return ("");
	while (str[*i] != '\0' && str[*i] != '$')
		(*i)++;
	substr = ft_substr(str, start_index, *i - start_index);
	return (substr);
}

int	is_valid_expansion_char(char key)
{
	if (ft_isalnum(key) || key == '_' || contains_char(SPECIAL_CHARS, key))
		return (1);
	return (0);
}

char	*expand_special_parameter(t_shell *shell, char token)
{
	if (token == '0')
		return (ft_strdup("./minishell"));
	else if (token == '$')
		return (ft_itoa(shell->pid));
	else if (token == '?')
		return (ft_itoa(g_exit_status));
	return (ft_strdup(""));
}
