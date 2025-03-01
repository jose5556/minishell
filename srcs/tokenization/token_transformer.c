/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_transformer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:27 by cereais           #+#    #+#             */
/*   Updated: 2025/02/01 16:29:58 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_token_type_in_range(int type)
{
	if (type >= 2 && type <= 6)
		return (true);
	return (false);
}

void	transform_nodes(t_list *start, int type)
{
	while (start && get_token_content(start)->type == TOKEN_WORD)
	{
		get_token_content(start)->type = type;
		start = start->next;
	}
}

void	set_heredoc_type(t_list *start)
{
	t_list	*current_token;
	t_list	*heredoc_start;

	current_token = start;
	while (current_token && get_token_content(current_token)->type
		!= TOKEN_WHITESPACE)
	{
		if (get_token_content(current_token)->quote_state == SINGLE_QUOTES
			|| get_token_content(current_token)->quote_state == DOUBLE_QUOTES)
		{
			heredoc_start = start;
			while (heredoc_start && get_token_content
				(heredoc_start)->type != TOKEN_WHITESPACE)
			{
				get_token_content(heredoc_start)->disable_expansion = true;
				heredoc_start = heredoc_start->next;
			}
			break ;
		}
		current_token = current_token->next;
	}
}

void	merge_consecutive_tokens(t_shell *shell, t_list **tokens)
{
	t_list	*curr;
	t_list	*next_node;

	curr = *tokens;
	while (curr && curr->next)
	{
		if (!is_token_type_in_range(get_token_content(curr)->type)
			&& !is_token_type_in_range(get_token_content(curr->next)->type)
			&& get_token_content(curr)->type != TOKEN_PIPE
			&& get_token_content(curr->next)->type != TOKEN_PIPE)
		{
			next_node = curr->next;
			get_token_content(curr)->value = ft_strjoin_free
			(get_token_content(curr)->value,
				get_token_content(curr->next)->value, 1);
			if (!get_token_content(curr)->value)
				clear_exit(shell, 1);
			remove_node(tokens, next_node);
		}
		else
			curr = curr->next;
	}
}

void	remove_nodes(t_shell *shell, t_list **tokens)
{
	t_list	*curr;
	t_list	*next_node;

	(void)shell;
	curr = *tokens;
	while (curr)
	{
		next_node = curr->next;
		if (is_token_type_in_range(get_token_content(curr)->type))
			remove_node(tokens, curr);
		curr = next_node;
	}
}
