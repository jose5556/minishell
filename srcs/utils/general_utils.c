/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:32 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:34 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(const char *str)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((unsigned char)*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (sign * n);
}

void	swap(char **x, char **y)
{
	char	*temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	free_key_pair(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

bool	is_only_whitespace(char *input, int curr_pos)
{
	while (input[curr_pos])
	{
		if (ft_iswhitespace(input[curr_pos]))
			curr_pos++;
		else
			return (false);
	}
	return (true);
}

int	count_command_args(t_list *token_list)
{
	int		arg_count;
	t_token	*curr_token;

	arg_count = 0;
	while (token_list)
	{
		curr_token = (t_token *)token_list->content;
		if (curr_token->type == TOKEN_WORD)
			arg_count++;
		else if (curr_token->type == TOKEN_PIPE)
			break ;
		token_list = token_list->next;
	}
	return (arg_count);
}
