/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:38 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 12:57:38 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_char_in_set(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if ((unsigned char)set[i] == (unsigned char)c)
			return (true);
		i++;
	}
	return (false);
}

static bool	trim_indices(const char *str, const char *trim_set,
							int *start_idx, int *end_idx)
{
	int	len;

	if (!str || !trim_set)
		return (false);
	len = ft_strlen(str);
	*start_idx = 0;
	while (*start_idx < len && is_char_in_set(str[*start_idx], trim_set))
		(*start_idx)++;
	*end_idx = len - 1;
	while (*end_idx >= *start_idx && is_char_in_set(str[*end_idx], trim_set))
		(*end_idx)--;
	return (true);
}

char	*trim_str(char *str, char const *set)
{
	char	*result;
	int		start;
	int		end;

	result = NULL;
	if (!trim_indices(str, set, &start, &end))
		return (NULL);
	if (start > end)
		result = ft_strdup("");
	else
		result = ft_substr(str, start, end - start + 1);
	free(str);
	return (result);
}

bool	contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}
