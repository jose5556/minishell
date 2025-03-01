/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:09:18 by dzinchen          #+#    #+#             */
/*   Updated: 2023/11/11 15:08:54 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_string_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_find_char(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (!c)
		return (&str[ft_strlen(str)]);
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_copy(char *new_string, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	return (new_string);
}

char	*ft_string_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_string;

	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_string)
		return (NULL);
	ft_copy(new_string, s1);
	i = ft_strlen(s1);
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	free(s1);
	return (new_string);
}

char	*ft_remove_prev_line(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	temp = malloc(ft_strlen(str) - i + 1);
	if (!temp)
		return (NULL);
	i++;
	while (str[i])
		temp[j++] = str[i++];
	temp[j] = '\0';
	free(str);
	return (temp);
}
