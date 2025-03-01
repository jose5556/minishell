/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:20 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:51 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_home_path(t_shell *shell, t_list *tmp)
{
	get_token_content(tmp)->value = resolve_home_directory(shell, tmp);
}

static void	expand_token_if_needed(t_shell *shell, t_list **token_list,
	t_list **current_token, t_list **expanded_token)
{
	t_list	*next_token;

	if (get_token_content(*current_token)->value[0] == '$'
		&& get_token_content(*current_token)->quote_state == UNQUOTED
		&& (*current_token)->next)
	{
		if (get_token_content((*current_token)->next)->type != TOKEN_WHITESPACE)
		{
			*expanded_token = *current_token;
			handle_token_expansion(shell, *expanded_token);
			if ((!get_token_content(*current_token)->value
					|| !*get_token_content(*current_token)->value))
			{
				next_token = (*current_token)->next;
				remove_node(token_list, *current_token);
				*current_token = next_token;
				return ;
			}
		}
	}
}

void	expand_unquoted_variables(t_shell *shell, t_list **tokens)
{
	t_list	*current_token;
	t_list	*expanded_token;

	current_token = *tokens;
	expanded_token = NULL;
	while (current_token)
	{
		if (is_home_directory_token(current_token)
			&& get_token_content(current_token)->quote_state == UNQUOTED)
			expand_home_path(shell, current_token);
		else
			expand_token_if_needed(shell, tokens,
				&current_token, &expanded_token);
		if (current_token)
			current_token = current_token->next;
	}
}

void	expand_double_quoted_variables(t_shell *shell, t_list **tokens)
{
	t_list	*current_token;
	t_list	*next_token;
	t_token	*content;

	current_token = *tokens;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		content = get_token_content(current_token);
		if (content->quote_state == DOUBLE_QUOTES
			&& content->type != TOKEN_DELIMITER
			&& content->value[0] != '\0')
		{
			handle_quote_expansion(shell, current_token);
			if (!*content->value && content->type
				!= TOKEN_FILE_IN
				&& content->type != TOKEN_FILE_OUT && content->type
				!= TOKEN_APPEND)
				remove_node(tokens, current_token);
		}
		current_token = next_token;
	}
}
