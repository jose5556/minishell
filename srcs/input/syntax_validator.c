/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:26 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:14:03 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_output_redir(int i, char *input)
{
	if (is_only_whitespace(input, i + 1) || (is_output_redir(input[i + 1])
			&& is_only_whitespace(input, i + 2)) || (is_pipe(input[i + 1])))
		return (syntax_error_handler("newline"));
	else if (is_input_redir(input [i + 1]))
		return (syntax_error_handler("<"));
	else if (((is_output_redir(input[i + 1]) && is_pipe(input [i + 2]))))
		return (syntax_error_handler("|"));
	else if (is_output_redir(input [i + 1]) && is_output_redir(input [i + 2]))
		return (syntax_error_handler(">"));
	else if (is_output_redir(input [i + 1]) || ft_iswhitespace(input [i + 1]))
	{
		i++;
		while (ft_iswhitespace(input[++i]))
			continue ;
		if (ft_strchr(OPERATOR, input[i]))
		{
			if (is_output_redir(input[i]))
				return (syntax_error_handler(">"));
			else if (is_input_redir(input[i]))
				return (syntax_error_handler("<"));
			else if (is_pipe(input[i]))
				return (syntax_error_handler("|"));
		}
	}
	return (true);
}

static bool	validate_input_redir_helper(int i, char *input)
{
	i++;
	while (ft_iswhitespace(input[++i]))
		;
	if (ft_strchr(OPERATOR, input[i]))
	{
		if (is_output_redir(input[i]))
			return (syntax_error_handler(">"));
		if (is_input_redir(input[i]))
			return (syntax_error_handler("<"));
		if (is_pipe(input[i]))
			return (syntax_error_handler("|"));
	}
	return (true);
}

static bool	validate_input_redir(int i, char *input)
{
	if (is_only_whitespace(input, i + 1)
		|| (is_input_redir(input[i + 1]) && is_only_whitespace(input, i + 2)))
		return (syntax_error_handler("newline"));
	else if (is_pipe(input[i + 1])
		|| (is_input_redir(input[i + 1]) && is_pipe(input[i + 2])))
		return (syntax_error_handler("|"));
	else if (is_input_redir(input[i + 1]) && is_input_redir(input[i + 2]))
		return (syntax_error_handler("<"));
	else if (is_output_redir(input[i + 1]))
		return (syntax_error_handler(">"));
	else if (is_input_redir(input[i + 1]) || ft_iswhitespace(input[i + 1]))
		return (validate_input_redir_helper(i, input));
	return (true);
}

bool	syntax_error_handler(char *token)
{
	g_exit_status = 2;
	if (token[0] == '\0')
		custom_error("minishell: syntax error near unexpected token `",
			"newline", "'", 2);
	else
		custom_error("minishell: syntax error near unexpected token `",
			token, "'", 2);
	return (false);
}

bool	validate_operator_syntax(char *input, int current_index)
{
	if (is_input_redir(input[current_index]))
		return (validate_input_redir(current_index, input));
	else if (is_output_redir(input[current_index]))
		return (validate_output_redir(current_index, input));
	else if (is_pipe(input[current_index]))
	{
		while (ft_iswhitespace(input[++current_index]))
			continue ;
		if (is_pipe(input[current_index]))
			return (syntax_error_handler("|"));
	}
	return (true);
}
