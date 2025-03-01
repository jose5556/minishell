/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:54:26 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:55 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	special_exit_helper(char **trimed_input, int len)
{
	int		i;

	i = 1;
	while (i < len)
	{
		if (!ft_strcmp(trimed_input[i], ">>")
			|| !ft_strcmp(trimed_input[i], "<<")
			|| !ft_strcmp(trimed_input[i], ">"))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	special_exit(char *input)
{
	char	**trimed_input;
	int		len;
	bool	result;

	len = 0;
	trimed_input = ft_split(input, ' ');
	if (!trimed_input || !trimed_input[0])
	{
		free(*trimed_input);
		free(trimed_input);
		return (false);
	}
	while (trimed_input[len])
		len++;
	if (!ft_strcmp(trimed_input[0], "exit"))
	{
		result = special_exit_helper(trimed_input, len);
		free_array(trimed_input, len);
		return (result);
	}
	free_array(trimed_input, len);
	return (false);
}
