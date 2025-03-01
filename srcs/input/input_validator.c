/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:24 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:51 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_closing_quote(int start_index, char target_quote, char *input)
{
	int	i;

	i = start_index + 1;
	while (input[i] != '\0')
	{
		if (input[i] == target_quote)
			return (i);
		i++;
	}
	custom_error("minishell: ", "syntax error: ", "unclosed quote", 2);
	return (-1);
}

static bool	is_pipe_at_start(const char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace((unsigned char)input[i]))
		i++;
	return (input[i] == '|');
}

static bool	validate_special_chars(char *input, int *current_index)
{
	char	current_char;

	current_char = input[*current_index];
	if (current_char == '\'' || current_char == '"')
	{
		*current_index = find_closing_quote(*current_index,
				current_char, input);
		if (*current_index == -1)
		{
			g_exit_status = 2;
			return (false);
		}
	}
	if (is_pipe_at_start(input) || ends_with_single_pipe(input))
		return (syntax_error_handler("|"));
	if (!validate_operator_syntax(input, *current_index))
	{
		g_exit_status = 2;
		return (false);
	}
	return (true);
}

bool	validate_input_syntax(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (!validate_special_chars(input, &i))
			return (false);
		i++;
	}
	return (true);
}

void	validate_shell_args(int argc)
{
	if (argc > 1)
	{
		custom_error("ERROR: minishell can't receive inputs.", NULL, NULL, 2);
		clear_exit(NULL, 1);
	}
}
