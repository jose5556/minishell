/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:33 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:28 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') && str[len - 1] == str[0])
	{
		new_str = ft_substr(str, 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str));
}

int	is_exit_code(char *n)
{
	long long	i;
	char		*new_n;

	i = ft_atol(n);
	new_n = ft_itoa(i);
	if ((n[0] == '+' && ft_strcmp(new_n, n + 1) == 0) || \
	ft_strcmp(new_n, n) == 0)
	{
		free(new_n);
		return (true);
	}
	free(new_n);
	return (false);
}

bool	is_valid_number(char *n, long long *exit_code)
{
	int	i;

	i = 0;
	if ((n[0] == '-' || n[0] == '+') && n[1] != '\0')
		i++;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (false);
		i++;
	}
	if (!ft_strcmp(n, "-9223372036854775808") || is_exit_code(n))
	{
		*exit_code = ft_atol(n);
		return (true);
	}
	else
	{
		*exit_code = 2;
		return (false);
	}
}
