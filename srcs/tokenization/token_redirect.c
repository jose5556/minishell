/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:25 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:45 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_type_in_range(int type, int min, int max)
{
	if (type >= min && type <= max)
		return (true);
	return (false);
}

static void	convert_redir_type(t_token *operator, t_token *target)
{
	int	new_type;

	if (operator->type == TOKEN_REDIRECT_IN)
		new_type = TOKEN_FILE_IN;
	else if (operator->type == TOKEN_REDIRECT_OUT)
		new_type = TOKEN_FILE_OUT;
	else if (operator->type == TOKEN_HEREDOC)
		new_type = TOKEN_DELIMITER;
	else if (operator->type == TOKEN_APPEND_OUT)
		new_type = TOKEN_APPEND;
	else
		return ;
	target->type = new_type;
}

static void	assign_redir_token_types(t_list *tmp)
{
	t_token	*operator;
	t_token	*target;

	operator = NULL;
	target = NULL;
	if (is_type_in_range(((t_token *)(tmp->next->content))->type,
		TOKEN_WORD, TOKEN_WORD))
	{
		operator = tmp->content;
		target = tmp->next->content;
	}
	else if (is_type_in_range(((t_token *)(tmp->next->content))->type, \
			TOKEN_WHITESPACE, TOKEN_WHITESPACE))
	{
		operator = tmp->content;
		tmp = tmp->next;
		target = tmp->next->content;
	}
	convert_redir_type(operator, target);
}

void	update_redirection_types(t_list *token_list)
{
	t_list	*curr;
	t_token	*token;

	curr = token_list;
	while (curr)
	{
		token = curr->content;
		if (is_type_in_range(token->type, TOKEN_REDIRECT_OUT, TOKEN_HEREDOC))
			assign_redir_token_types(curr);
		curr = curr->next;
	}
}
