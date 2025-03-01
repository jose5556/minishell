/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:16 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 11:42:57 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_token_list(t_shell *shell, t_list **token_list)
{
	merge_consecutive_tokens(shell, token_list);
	remove_nodes(shell, token_list);
}

static void	process_token_types(t_shell *shell, t_list **token_list)
{
	int		token_type;
	t_list	*curr;

	curr = *token_list;
	while (curr != NULL)
	{
		token_type = get_token_content(curr)->type;
		if (token_type == TOKEN_PIPE)
			shell->num_pipes++;
		else if (token_type == TOKEN_DELIMITER)
		{
			transform_nodes(curr->next, token_type);
			set_heredoc_type(curr);
		}
		else if (token_type >= 7)
			transform_nodes(curr->next, token_type);
		curr = curr->next;
	}
}

void	lexer(t_shell *shell, char *input)
{
	create_token_list(shell, input);
	update_redirection_types(shell->token_list);
	process_token_types(shell, &shell->token_list);
	expand_unquoted_variables(shell, &shell->token_list);
	expand_double_quoted_variables(shell, &shell->token_list);
	clean_token_list(shell, &shell->token_list);
	if (shell->num_pipes == 0)
		set_env_variable(shell, "_", NULL);
}
