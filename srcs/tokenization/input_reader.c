/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:13 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 18:12:04 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_and_join_input(char *join, t_shell *shell, char *input)
{
	char	*new_line;

	new_line = readline("> ");
	if (!new_line)
	{
		free(join);
		free(input);
		custom_error("minishell: syntax error: unexpected "
			"end of file", NULL, NULL, 2);
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		clear_exit(shell, g_exit_status);
	}
	new_line = trim_str(new_line, " \t");
	join = ft_strjoin_free(join, " ", 1);
	join = ft_strjoin_free(join, new_line, 1);
	free(new_line);
	join = trim_str(join, " \t");
	return (join);
}

static char	*multiline_pipe_handler(t_shell *shell, char *input)
{
	char	*join;

	join = ft_strdup(input);
	while (true)
	{
		join = read_and_join_input(join, shell, input);
		if (!join)
			return (NULL);
		if (!ends_with_single_pipe(join))
			break ;
		if (!validate_input_syntax(join))
		{
			add_history(join);
			free(join);
			free(input);
			reinit_shell(shell);
			main_loop(shell);
		}
	}
	return (join);
}

static char	*handle_input_validation(t_shell *shell,
	char *input, char *clean_input)
{
	char	*ret;

	ret = NULL;
	if (!validate_input_syntax(clean_input))
	{
		add_history(input);
		free(input);
		if (clean_input)
			free(clean_input);
		main_loop(shell);
	}
	else if (clean_input && ft_strlen(clean_input) > 0
		&& ends_with_single_pipe(clean_input))
		ret = multiline_pipe_handler(shell, clean_input);
	else
		ret = ft_strdup(clean_input);
	return (ret);
}

static char	*process_shell_input(t_shell *shell, char *input)
{
	char	*ret;
	char	*clean_input;

	ret = NULL;
	clean_input = ft_strtrim(input, "\t ");
	if (!clean_input || !*clean_input)
	{
		add_history(input);
		free(input);
		if (clean_input)
		{
			free(clean_input);
		}
		main_loop(shell);
	}
	ret = handle_input_validation(shell, input, clean_input);
	free(input);
	if (clean_input)
		free(clean_input);
	return (ret);
}

char	*read_prompt_input(t_shell *shell)
{
	char	*input;

	input = readline(get_prompt(shell->prompt));
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		clear_exit(shell, g_exit_status);
	}
	free_prompt_modifier(&shell->prompt);
	special_redirect_handler(&input, shell);
	return (process_shell_input(shell, input));
}
