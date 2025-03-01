/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:18 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:54 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	handle_special_chars(char *input, int *end)
{
	if (input[*end] && contains_char("><|$", input[*end])
		&& !contains_char("\"\'", input[*end]))
	{
		if (input[*end] == '$' || input[*end] == '|')
		{
			(*end)++;
			return ;
		}
		while (input[*end] && contains_char("><", input[*end])
			&& !contains_char("|$\"\'", input[*end]))
			(*end)++;
	}
}

void	find_token_end(char *input, int *end)
{
	if (input[*end] && contains_char("><|$", input[*end])
		&& !contains_char("\"\'", input[*end]))
	{
		handle_special_chars(input, end);
		return ;
	}
	if (input[*end] && contains_char("\"\'", input[*end]))
		skip_quoted_section(input, end, input[*end]);
	else
	{
		while (input[*end] && !contains_char("\"\'", input[*end])
			&& !contains_char("><$|", input[*end])
			&& !ft_iswhitespace(input[*end]))
			(*end)++;
	}
}
