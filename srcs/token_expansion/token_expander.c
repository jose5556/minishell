/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:52 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 12:00:10 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*word_token_expander(t_shell *shell, t_list *token, int *i)
{
	char	*exp_val;

	exp_val = expand_var(shell, get_token_content(token->next)->value, i);
	exp_val = ft_strjoin_free(exp_val,
			&get_token_content(token->next)->value[*i], 1);
	return (exp_val);
}

static void	replace_token_value(t_list *token, char *new_token)
{
	if (new_token)
	{
		free(get_token_content(token)->value);
		get_token_content(token)->value = ft_strdup(new_token);
		free(new_token);
	}
}

static void	handle_expansion_conditions(t_shell *shell, t_list *token, int *i)
{
	char	*new_token;

	new_token = NULL;
	if (get_token_content(token->next)->quote_state != UNQUOTED)
		copy_token_content(token);
	else if (get_token_content(token)->type == TOKEN_DELIMITER)
		heredoc_type_handler(token);
	else if (get_token_content(token)->type != TOKEN_WORD)
	{
		new_token = word_token_expander(shell, token, i);
		if (!new_token || !*new_token)
		{
			if (!*new_token)
				free(new_token);
			return ;
		}
	}
	else
		new_token = word_token_expander(shell, token, i);
	replace_token_value(token, new_token);
	remove_node(&shell->token_list, token->next);
}

void	handle_token_expansion(t_shell *shell, t_list *token)
{
	int	i;

	i = 0;
	if (get_token_content(token->next)->type >= 2
		&& get_token_content(token->next)->type <= 6)
		return ;
	handle_expansion_conditions(shell, token, &i);
}

void	handle_quote_expansion(t_shell *shell, t_list *token)
{
	char	*new_token;
	char	*expanded;
	int		i;

	new_token = ft_strdup("");
	i = 0;
	while (get_token_content(token)->value[i])
	{
		expanded = process_token_value(shell, token, &i);
		new_token = ft_strjoin_free(new_token, expanded, 1);
		if (expanded)
			free(expanded);
	}
	free(get_token_content(token)->value);
	get_token_content(token)->value = new_token;
}
