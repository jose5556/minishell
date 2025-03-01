/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:23 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:47 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token_type(char *token)
{
	if (token[0] == '|')
		return (TOKEN_PIPE);
	else if (token[0] == ' ')
		return (TOKEN_WHITESPACE);
	else if (token[0] == '<' && token[1] == '<')
		return (TOKEN_HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (TOKEN_APPEND_OUT);
	else if (token[0] == '<' && !contains_char("<", token[1]))
		return (TOKEN_REDIRECT_IN);
	else if (token[0] == '>' && !contains_char(">", token[1]))
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_WORD);
}

static void	process_token_quotes(t_token *token)
{
	char	quote;
	char	*unquoted_var;

	unquoted_var = NULL;
	if (token->value[0] == '\"' || token->value[0] == '\'')
	{
		quote = token->value[0];
		if (quote == '\"')
			token->quote_state = DOUBLE_QUOTES;
		else
			token->quote_state = SINGLE_QUOTES;
		unquoted_var = ft_strtrim(token->value, &quote);
		if (unquoted_var != NULL)
		{
			free(token->value);
			token->value = unquoted_var;
		}
	}
	else
		token->quote_state = UNQUOTED;
}

static void	get_end_word(t_shell *shell, char *input)
{
	shell->index->end = shell->index->start;
	if (input[shell->index->end] == '\"' || input[shell->index->end] == '\'')
		skip_quoted_section(input, &shell->index->end,
			input[shell->index->end]);
	else
		find_token_end(input, &shell->index->end);
}

static	void	create_token_node(t_shell *shell, char *input)
{
	t_token	*node_content;

	node_content = ft_calloc(1, sizeof(t_token));
	if (!node_content)
		clear_exit(shell, 1);
	if (ft_iswhitespace(input[shell->index->start]))
	{
		node_content->value = ft_strdup(" ");
		while (ft_iswhitespace(input[shell->index->start]))
			shell->index->start++;
	}
	else
	{
		get_end_word(shell, input);
		node_content->value = ft_substr(input, shell->index->start,
				shell->index->end - shell->index->start);
		shell->index->start = shell->index->end;
	}
	node_content->type = get_token_type(node_content->value);
	process_token_quotes(node_content);
	ft_lstadd_back(&shell->token_list, ft_lstnew(node_content));
	node_content->pos = shell->index->pos++;
}

void	create_token_list(t_shell *shell, char *input)
{
	while (input[shell->index->start])
	{
		create_token_node(shell, input);
	}
}
