/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:06 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:07 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_child(t_shell *shell, t_list *token,
	char *filename, char *input_buffer)
{
	setup_heredoc_signals();
	heredoc_input_handler(shell, token, filename, input_buffer);
}

void	handle_heredoc_parent(t_shell *shell, t_list *token,
	char *filename, int status)
{
	update_token_value(token, filename);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status == 130)
	{
		reinit_shell(shell);
		main_loop(shell);
	}
}
