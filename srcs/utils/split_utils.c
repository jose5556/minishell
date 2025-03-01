/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:14:03 by joseoliv          #+#    #+#             */
/*   Updated: 2025/02/02 18:42:57 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_letters(char const *s, char *c, char **result)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c[0] || s[i] == c[1] || s[i] == c[2]))
			i++;
		while (s[i] && (s[i] != c[0] && s[i] != c[1] && s[i] != c[2]))
		{
			j++;
			i++;
		}
		if (j > 0)
		{
			result[k] = (char *) malloc((j + 1) * sizeof(char));
			ft_strlcpy(result[k++], &s[i - j], j + 1);
		}
		j = 0;
	}
	result[k] = 0;
	return (result);
}

static int	count_words(char const *s, char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c[0] || s[i] == c[1] || s[i] == c[2]))
			i++;
		if (s[i])
			j++;
		while (s[i] && (s[i] != c[0] && s[i] != c[1] && s[i] != c[2]))
			i++;
	}
	return (j);
}

char	**ft_split_special(char const *s, char *c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **) malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = fill_letters(s, c, result);
	return (result);
}

static void	special_utils(char **input, t_shell *shell)
{
	free(*input);
	ft_putstr_fd("exit\n", 1);
	clear_exit(shell, 0);
}

void	special_redirect_handler(char **input, t_shell *shell)
{
	char	**trimed_input;
	int		i;

	i = 0;
	trimed_input = ft_split_special(*input, "\t ");
	while (trimed_input[i])
		i++;
	if (i > 2)
	{
		if (!ft_strncmp(trimed_input[0], "exit", 4))
		{
			if (!ft_strncmp(trimed_input[1], ">", 1)
				|| !ft_strncmp(trimed_input[1], "<", 1))
			{
				free_array(trimed_input, i);
				special_utils(input, shell);
			}
		}
	}
	free_array(trimed_input, i);
}
