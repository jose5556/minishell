/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:41 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:20 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(char c)
{
	return (c == '|');
}

bool	is_output_redir(char c)
{
	return (c == '>');
}

bool	is_input_redir(char c)
{
	return (c == '<');
}

t_token	*get_token_content(t_list *token)
{
	return ((t_token *)token->content);
}
