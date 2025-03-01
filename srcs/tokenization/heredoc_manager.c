/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:47:11 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:10 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit_condition(t_shell *shell, t_list *tmp,
	char *temp_file, char *status)
{
	if (!status)
	{
		custom_error("minishell: warning: here-document ended unexpectedly."
			"Expected delimiter: '", get_token_content(tmp)->value, "'", 2);
		ft_putstr_fd("')\n", 2);
	}
	if (status)
		free(status);
	free(temp_file);
	clear_exit(shell, 0);
}

static void	create_heredoc_process(t_shell *shell, t_list *token,
	int i, char *input_buffer)
{
	int		status;
	char	*filename;
	pid_t	pid;

	status = 0;
	filename = initialize_heredoc(shell, i);
	pid = safe_fork(shell);
	if (pid < 0)
	{
		free(filename);
		clear_exit(shell, 1);
	}
	else if (pid == 0)
		handle_heredoc_child(shell, token, filename, input_buffer);
	else
	{
		handle_heredoc_parent(shell, token, filename, status);
		waitpid(pid, &status, 0);
	}
}

void	update_token_value(t_list *token, char *new_value)
{
	if (get_token_content(token)->value)
		free(get_token_content(token)->value);
	get_token_content(token)->value = ft_strdup(new_value);
	free(new_value);
}

void	heredoc_input_handler(t_shell *shell, t_list *tmp,
	char *temp_file, char *input)
{
	char	*status;

	while (true)
	{
		status = readline("> ");
		if (!status || !ft_strcmp(status, get_token_content(tmp)->value))
		{
			free(input);
			handle_exit_condition(shell, tmp, temp_file, status);
		}
		if (!get_token_content(tmp)->disable_expansion)
			status = expand_heredoc_variable(shell, status);
		write_heredoc_line(temp_file, status);
		free(status);
	}
}

void	handle_heredoc(t_shell *shell, t_list **tokens, char *input)
{
	int		i;
	t_list	*current_token;

	current_token = *tokens;
	i = 3;
	while (current_token)
	{
		if (get_token_content(current_token)->type == TOKEN_DELIMITER)
		{
			create_heredoc_process(shell, current_token, i, input);
			i++;
		}
		current_token = current_token->next;
	}
}
